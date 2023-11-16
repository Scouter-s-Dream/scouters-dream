from ultralytics import YOLO
import cv2
import numpy as np
from time import time
from tracker import Tracker

#TEST CODE DONT TAKE SERIOUSLY
print("loading")
cap = cv2.VideoCapture('test_videos/dcmp.mp4')
modelBumpers = YOLO('bumper_weights/v4/best (3).pt')

success, frame = cap.read()

print(success)

if success:
    
    frame = cv2.resize(frame, (640, 640))
    frame = frame[150:400]
    resultsB = modelBumpers(frame, verbose=False)
    tracker = Tracker(resultsB[0], frame, True) 
    print(frame)   
    
while cap.isOpened():
    success, frame = cap.read()
    
    
    
    if success:
        frame = cv2.resize(frame, (640, 640))
        frame = frame[150:400]
        t = time()
        resultsB = modelBumpers(frame, verbose=False)
        print("t", time() - t)
        t = time()
        tracker.setImg(frame)
        tracker.setTrackPoints(resultsB[0])
        tracker.track()
        print(time() - t)
        cv2.waitKey(1)
        # for r in resultsB:
        #     boxes = r.boxes.cpu().numpy()
        #     xywhWithCls = np.concatenate((boxes.xywh, np.reshape(boxes.cls, (boxes.cls.shape[0], 1))), 1)       
        #     s = np.array(xywhWithCls[xywhWithCls[:, 0].argsort()], dtype=np.int32)
        #     t = time()
        #     tracker.setTrackPoints(r)
        #     print(time() - t)
        #     for r in s:
        #         if r[4] == 0:
        #             frame = cv2.rectangle(frame, r[:2] - r[2:4]//2, r[:2] + r[2:4]//2, (0, 255 ,255), 1)    
        #         if r[4] == 1:
        #             frame = cv2.rectangle(frame, r[:2] - r[2:4]//2, r[:2] + r[2:4]//2, (255, 0 ,255), 1)    
        #     cv2.imshow('f', frame)
        #     cv2.waitKey(1)



    

