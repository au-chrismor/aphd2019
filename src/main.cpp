//
//  Copyright (C) 2019 Christopher Moran and Phui Leng Chong
//  All Rights Reserved.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace cv;
using namespace std;

int main(int, char**)
{
    int retCode = 0;

    Mat frame0, frame1;

    // Initialise capture
    // We will use the first device we find
    VideoCapture cap0, cap1;

    cap0.open(0);
    cap1.open(1);
    if (cap0.isOpened() && cap1.isOpened())
    {
        cout << "Got a camera!";

        // Configure our input data
        cap0.set(CAP_PROP_FRAME_WIDTH, 640);
        cap0.set(CAP_PROP_FRAME_HEIGHT, 480);
        cap1.set(CAP_PROP_FRAME_WIDTH, 640);
        cap1.set(CAP_PROP_FRAME_HEIGHT, 480);
    }
    else
    {
        cerr << "Failed to open a camera!";
        retCode = -1;
    }

    return retCode;
}