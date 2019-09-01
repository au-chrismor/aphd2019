//
//  Copyright (C) 2019 Christopher Moran and Phui Leng Chong
//  All Rights Reserved.
//
//  Name:       runthread.cpp
//  Synopsis:   This is main image-processing thread
//

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "aphd.hpp"


using namespace std;
using namespace cv;
#ifdef _HAS_YOLO3
using namespace dnn;
#endif

#ifdef _HAS_YOLO3
// Get the names of the output layers
vector<String> getOutputsNames(const Net& net)
{
    static vector<String> names;
    if (names.empty())
    {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        vector<int> outLayers = net.getUnconnectedOutLayers();
        
        //get the names of all the layers in the network
        vector<String> layersNames = net.getLayerNames();
        
        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
        names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}
#endif

void *runThread(void *id)
{
    long idx;

    idx = (long)id;

    int64 ticks = 0;

    Mat frame, blob;
#ifdef _HAS_STEREO_CAM
    Rect roi;
#endif    
    HOGDescriptor hog;
    vector<Rect> found;
    VideoCapture cap;

#ifdef _HAS_YOLO3
    // Set up DNN Config
    String modelConfiguration = "yolov3.cfg";
    String modelWeights = "yolov3.weights";  
    Net net = readNetFromDarknet(modelConfiguration, modelWeights);
    net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
    net.setPreferableTarget(DNN_TARGET_CPU);
//  net.setPreferableTarget(DNN_TARGET_FPGA);
#endif    

#ifdef _DEBUG
    cout << "Thread " << idx << ": starting a camera" << endl;
#endif
    
    cap.open(idx);
    if (cap.isOpened())
    {
        // Configure our input data
        cap.set(CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);

        int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

        hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

        cout << "Thread " << idx << ": Start grabbing.  Press any key to terminate" << endl;

        String inputName = "Input-" + std::to_string(idx);
        String denoiseName = "DeNoise-" + std::to_string(idx);

        if(idx == 0)
        {
            namedWindow(inputName, WINDOW_AUTOSIZE);
//            namedWindow(denoiseName, WINDOW_AUTOSIZE);
        }

        // This is the main capture loop
        for(;;)
        {
            // Wait for a frame and buffer it
            cap.read(frame);

            // Make sure we actually got something
            if (frame.empty())
            {
                cerr << "Thread " << idx << ": ERROR! blank frame grabbed\n";
                break;
            }


#ifdef _HAS_STEREO_CAM
            int offset_x = frame_width / 2;
            int offset_y = frame_height;
            roi.x = 0;
            roi.y = 0;
            roi.width = offset_x;
            roi.height = offset_y;
            frDeNoise = frame(roi);
#else
#ifdef _HAS_YOLO3
            blobFromImage(frame, blob, 1/255.0, Size(640, 480), Scalar(0,0,0), true, false);
            net.setInput(blob);
            vector<Mat> outs;
            net.forward(outs, getOutputsNames(net));
#endif
            hog.detectMultiScale(frame, found, 0, Size(4,4), Size(8,8), 1.05, 2, false);
            for (vector<Rect>::iterator i = found.begin(); i != found.end(); ++i)
            {
                Rect &r = *i;
                // Tweak the rectange to closer approximation
                r.x += cvRound(r.width*0.1);
                r.width = cvRound(r.width*0.8);
                r.y += cvRound(r.height*0.07);
                r.height = cvRound(r.height*0.8);
                cv::rectangle(frame, r.tl() * 0.81, r.br(), cv::Scalar(0, 255, 0), 2);
            }
            ticks = getTickCount() - ticks;
            
            if(idx == 0)
            {
                ostringstream buf;
                buf << "FPS: " << fixed << setprecision(1) << (getTickFrequency() / (double)ticks);
                putText(frame, buf.str(), Point(10, 30), FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 0, 255), 2, LINE_AA);
            }
//            if(idx == 0)
                imshow(inputName, frame);
#endif

            if (waitKey(10) >= 0)
            {
                if(idx == 0)
                {
                    try
                    {
                        destroyAllWindows();
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << endl;
                    }
                }
                break;
            }
//#ifdef _DEBUG            
//            cout << idx << " ";
//#endif            
        }

    }
    else
    {
        cerr << "Thread " << idx << "; Failed to open a camera!" << endl;
    }
    cout << "Thread " << idx << ": Thread exit" << endl;
}
