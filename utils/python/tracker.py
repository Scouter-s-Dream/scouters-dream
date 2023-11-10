import cpp_utils as cpp
import numpy as np

class Tracker():
    
    def __init__(self) -> None:
        """Creates a Tracker object
        """
        cpp.lib._Tracker.restype = cpp.object
        self.obj = cpp.lib._Tracker()
        
    def setTrackPoints(self, YOLO_result):
        """
        Sets the current BoundingBoxes of the tracker
        -
        Args: 
        - `YOLO_result (the output of model.predict)` -> the prediction of the model.
        """
        
        point_size = 5
        boxes = YOLO_result.boxes.cpu().numpy()
        xywhWithCls = np.concatenate((boxes.xywh, np.reshape(boxes.cls, (boxes.cls.shape[0], 1))), 1)       
        points = np.array(xywhWithCls[xywhWithCls[:, 0].argsort()], dtype=np.int32).flatten()

        cpp.lib._setTrackPoints.argtypes = [cpp.object, cpp.int_array, cpp.int]
        cpp.lib._setTrackPoints.restype = cpp.object
        cpp.lib._setTrackPoints(self.obj, points, cpp.c_int(len(points)//point_size))
        
    
        
        