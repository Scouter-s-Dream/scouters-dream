from ultralytics import YOLO
import cv2
import numpy as np
from time import time, sleep
from tracker import Tracker

#TEST CODE DONT TAKE SERIOUSLY
print("loading")
cap = cv2.VideoCapture('test_videos/q1dis3.mp4')
modelBumpers = YOLO('bumper_weights/v4/best (3).pt')

success, frame = cap.read()

def prepFrame(frame):
    frame = cv2.resize(frame, (640, 640))
    frame = frame[250 : 450]
    frame = cv2.resize(frame, (1280, 500))
    return frame

def YoloToPointsAndTypes(YOLO_result):
        boxes = YOLO_result.boxes.cpu().numpy()      
        points = np.array(boxes.xyxy, dtype=np.uint16)
        types = np.array(boxes.cls, dtype=np.uint16)
        return (points, types, len(types))

if success:
    
    frame = prepFrame(frame)
    resultsB = modelBumpers(frame, verbose=False)
    print("[INFO]: Creating Tracker")
    tracker = Tracker(resultsB[0], frame, True) 
    print("[INFO]: Tracker Created")
while cap.isOpened():
    success, frame = cap.read()
    
    
    
    if success:
        frame = prepFrame(frame)
        
        resultsB = modelBumpers(frame, verbose=False)
        
        print("CALLED PYTHON --------------------------")
        t = time()
        tracker.track(resultsB[0], frame)
        
        # points, types, size = YoloToPointsAndTypes(resultsB[0])
        
        # for i in range(len(types)):
        #     color = (255, 0, 0)
        #     if types[i] == 1:
        #         color = (0, 0, 255)
                
        #     frame = cv2.rectangle(frame, points[i][:2], points[i][2:], color, 2)

        # cv2.imshow("python", frame)
        # cv2.waitKey(1)
            
        print(time() - t)