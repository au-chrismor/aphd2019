//
//  Copyright (C) 2019 Christopher Moran and Phui Leng Chong
//  All Rights Reserved.
//
//  Name:       runthread.cpp
//  Synopsis:   This is main image-processing thread
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "aphd.hpp"


using namespace std;
using namespace cv;

void *runThread(void *id)
{
    long idx;

    idx = (long)id;

    Mat frame, frDeNoise;
    Rect roi;

    // Initialise capture
    // We will use the first device we find
    VideoCapture cap;

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

        cout << "Thread " << idx << ": Start grabbing.  Press any key to terminate" << endl;

        String inputName = "Input-" + std::to_string(idx);
        String denoiseName = "DeNoise-" + std::to_string(idx);

        if(idx == 0)
        {
//            namedWindow(inputName, WINDOW_AUTOSIZE);
            namedWindow(denoiseName, WINDOW_AUTOSIZE);
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


//            if(idx == 0)
//                imshow(inputName, frame);
#ifdef _HAS_STEREO_CAM
            int offset_x = frame_width / 2;
            int offset_y = frame_height;
            roi.x = 0;
            roi.y = 0;
            roi.width = offset_x;
            roi.height = offset_y;
            frDeNoise = frame(roi);
//            fastNlMeansDenoisingColored(frame(roi), frDeNoise, 3.0, 3.0, 7, 21);
#else
//            fastNlMeansDenoisingColored(frame, frDeNoise, 3.0, 3.0, 7, 21);
            frDeNoise = frame;
#endif
            if(idx == 0)
                imshow(denoiseName, frDeNoise);

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
#ifdef _DEBUG            
            cout << idx << " ";
#endif            
        }

    }
    else
    {
        cerr << "Thread " << idx << "; Failed to open a camera!" << endl;
    }
    cout << "Thread " << idx << ": Thread exit" << endl;
}
