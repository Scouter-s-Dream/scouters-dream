import cpp_utils as cpp
import numpy as np

class Tracker():        
    
    def __init__(self, YOLO_result, img: np.ndarray, visualize = False) -> None:
        """Creates a Tracker object
        """
        
        self.setFuncs()
        
        point_size = 5
        boxes = YOLO_result.boxes.cpu().numpy()
        xywhWithCls = np.concatenate((boxes.xywh, np.reshape(boxes.cls, (boxes.cls.shape[0], 1))), 1)       
        points = np.array(xywhWithCls[xywhWithCls[:, 0].argsort()], dtype=np.int32).flatten()

        self.obj = cpp.lib._Tracker(points, cpp.c_int(len(points)//point_size), np.array(img.flatten(), dtype=np.uint8), cpp.c_int(img.shape[0]), cpp.c_int(img.shape[1]), cpp.c_bool(visualize))
        
    def setFuncs(self):
        
        cpp.lib._Tracker.argtypes = [cpp.int_array, cpp.int, cpp.uint8_t_array, cpp.int, cpp.int, cpp.bool]
        cpp.lib._Tracker.restype = cpp.object
        
        cpp.lib._setTrackPoints.argtypes = [cpp.object, cpp.int_array, cpp.int]
        
        cpp.lib._track.argtypes = [cpp.object]
        
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
        cpp.lib._setTrackPoints(self.obj, points, cpp.c_int(len(points)//point_size))
    
    def setImg(self, coloredImg: np.ndarray):
        pass
    
    def track(self):
        cpp.lib._track(self.obj)
    
    
    
        
        