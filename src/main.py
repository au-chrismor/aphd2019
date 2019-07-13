#! /usr/bin/python3

#
# Active Pedestrian Hazard Detection (APHD)
# 
# This is the main function set
#

import argparse
import json
import numpy as np
import os


# Parse the arguments.  argparse does the hard work for us.
ap = argparse.ArgumentParser()
ap.add_argument("-y", "--yolo", required=True, help="base path to YOLO directory")
ap.add_argument("-c", "--confidence", type=float, default=0.5, help="minimum probability to filter weak detections")
ap.add_argument("-t", "--threshold", type=float, default=0.3, help="threshold when applyong non-maxima suppression")
args = vars(ap.parse_args())
