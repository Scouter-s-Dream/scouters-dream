from ultralytics import YOLO
import cv2
import numpy as np
from time import time, sleep
from tracker import Tracker

#TEST CODE DONT TAKE SERIOUSLY
print("loading")
cap = cv2.VideoCapture('test_videos/dcmp.mp4')
modelBumpers = YOLO('bumper_weights/v4/best (3).pt')

for _ in range(10):
    success, frame = cap.read()

print("r")

def prepFrame(frame):
    frame = cv2.resize(frame, (640, 640))
    frame = frame[150:400]
    frame = cv2.resize(frame, (1280, 500))
    return frame

if success:
    
    frame = prepFrame(frame)
    resultsB = modelBumpers(frame, verbose=False)
    tracker = Tracker(resultsB[0], frame, True) 
    
print("l")

while cap.isOpened():
    success, frame = cap.read()
    
    
    
    if success:
        frame = prepFrame(frame)
        t = time()
        resultsB = modelBumpers(frame, verbose=False)
        print("Mode Time", time() - t)
        t = time()
        tracker.track(resultsB[0], frame)
        print("CPP time:", time() - t)
        cv2.waitKey(1)


    

