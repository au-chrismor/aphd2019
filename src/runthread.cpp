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

    Mat frame;

    // Initialise capture
    // We will use the first device we find
    VideoCapture cap;

#ifdef _DEBUG
    cout << "Thread " << idx << " starting a camera" << endl;
#endif    
    cap.open(idx);
    if (cap.isOpened())
    {
#ifdef _DEBUG
        cout << "Got a camera!";
#endif
        // Configure our input data
        cap.set(CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);

        int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

        cout << "Start grabbing" << endl << "Press any key to terminate" << endl;

        // This is the main capture loop
        for(;;)
        {
            // Wait for a frame and buffer it
            cap.read(frame);

            // Make sure we actually got something
            if (frame.empty())
            {
                cerr << "ERROR! blank frame grabbed\n";
                break;
            }

            if (waitKey(5) >= 0)
                break;
        }

    }
    else
    {
        cerr << "Failed to open a camera!" << endl;
    }
}
