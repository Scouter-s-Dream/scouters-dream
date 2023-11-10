from ultralytics import YOLO
import cv2
import numpy as np
import time
from tracker import Tracker

#TEST CODE DONT TAKE SERIOUSLY

cap = cv2.VideoCapture('/home/sagi/Downloads/dcmp.mp4')
modelBumpers = YOLO('data/BumperWeights.pt')

while cap.isOpened():
    
    tracker = Tracker()
    success, frame = cap.read()
    
    if success:
        frame = cv2.resize(frame, (640, 640))
        frame = frame[150:400]
        
        resultsB = modelBumpers(frame, verbose=False)
        for r in resultsB:
            boxes = r.boxes.cpu().numpy()
            xywhWithCls = np.concatenate((boxes.xywh, np.reshape(boxes.cls, (boxes.cls.shape[0], 1))), 1)       
            s = np.array(xywhWithCls[xywhWithCls[:, 0].argsort()], dtype=np.int32)
            
            tracker.setTrackPoints(r)
            
            for r in s:
                if r[4] == 0:
                    frame = cv2.rectangle(frame, r[:2] - r[2:4]//2, r[:2] + r[2:4]//2, (0, 255 ,255), 1)    
                if r[4] == 1:
                    frame = cv2.rectangle(frame, r[:2] - r[2:4]//2, r[:2] + r[2:4]//2, (255, 0 ,255), 1)    
            cv2.imshow('f', frame)
            cv2.waitKey(1)



    

