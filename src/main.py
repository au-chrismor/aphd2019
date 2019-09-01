from imutils.object_detection import non_max_suppression
from imutils import paths
import numpy as np
import argparse
import imutils
import cv2
import cv2.ocl


cv2.ocl.setUseOpenCL(False) # Insert this line as the first executed line

# initialize the HOG descriptor/person detector
hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

cap = cv2.VideoCapture(0)
print(cv2.__version__)
print(cap.getBackendName())
print('Width: {}'.format(cap.get(cv2.CAP_PROP_FRAME_WIDTH)))
print('Height: {}'.format(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

while cap.isOpened():
	cap.grab()
	frame = cap.retrieve()
	if frame != None:
		img = cv2.UMat(frame)
#		gray = cv2.cvtColor(cv2.UMat(frame), cv2.COLOR_BGR2GRAY)
		cv2.imshow('frame', frame)
		if cv2.waitKey(1) & 0xFF == ord('q'):
			break
