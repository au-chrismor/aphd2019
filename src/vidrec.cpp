//
//  Copyright (C) 2019 Christopher Moran and Phui Leng Chong
//  All Rights Reserved.
//
//  Name:       runthread.cpp
//  Synopsis:   This is main image-processing thread
//

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/ocl.hpp>
#ifdef _WRITE_VIDEO
#include <opencv2/videoio.hpp>
#endif
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace std;
using namespace cv;
using namespace ocl;


#define _WRITE_VIDEO


int main()
{
    VideoCapture cap;
    UMat frame;
    String inputName = "vrecIn";
    int64 ticks = 0;

    cap.open(1);

    if (cap.isOpened())
    {
        // Configure our input data
        cap.set(CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);

        int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);
#ifdef _WRITE_VIDEO        
        int ex = static_cast<int>(cap.get(CAP_PROP_FOURCC));
        char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};
        VideoWriter out;
#ifdef _DEBUG
        cout << "FOURCC = " << ex << endl;
        cout << EXT << endl;
#endif
        String videoName = "vRecOut.mjpg";

//        out.open(videoName, 0x4745504d, cap.get(CAP_PROP_FPS), Size(frame_width, frame_height), true);
        out.open(videoName, 0x4745504d, 1, Size(frame_width, frame_height), true);
#endif
        namedWindow(inputName, WINDOW_AUTOSIZE);

        for(;;)
        {
            cap.read(frame);
            if (frame.empty())
            {
                cerr << "ERROR! blank frame grabbed\n";
                break;
            }
            ticks = getTickCount() - ticks;
            ostringstream buf;
//            buf << "FPS: " << fixed << setprecision(1) << (getTickFrequency() / (double)ticks);
            buf << "FPS: " << fixed << setprecision(1) << ((double)ticks / getTickFrequency());
            putText(frame, buf.str(), Point(10, 30), FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 0, 255), 2, LINE_AA);
            imshow(inputName, frame);
#ifdef _WRITE_VIDEO
            out.write(frame);
#endif
            if (waitKey(10) >= 0)
            {
                cap.release();
#ifdef _WRITE_VIDEO
                out.release();
#endif
                destroyAllWindows();
                break;
            }
        }

    }
}