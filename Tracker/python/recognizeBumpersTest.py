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

def prepFrame(frame):
    # frame = cv2.resize(frame, (640, 640))
    frame = frame[250 : 650]
    # frame = cv2.resize(frame, (1280, 500))
    return frame

if success:
    
    frame = prepFrame(frame)
    resultsB = modelBumpers(frame, verbose=False)
    print("[INFO]: Creating Tracker")
    tracker = Tracker(resultsB[0], frame, False) 
    print("[INFO]: Tracker Created")
while cap.isOpened():
    success, frame = cap.read()
    
    
    
    if success:
        frame = prepFrame(frame)
        
        resultsB = modelBumpers(frame, verbose=False)
        
        print("CALLED PYTHON --------------------------")
        t = time()
        tracker.track(resultsB[0], frame)
        print(time() - t)