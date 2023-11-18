import cpp_utils as cpp
import numpy as np

class Tracker():        
    
    @staticmethod
    def YoloToPointsWithClasses(YOLO_result, point_size):
        boxes = YOLO_result.boxes.cpu().numpy()
        xywhWithCls = np.concatenate((boxes.xywh, np.reshape(boxes.cls, (boxes.cls.shape[0], 1))), 1)       
        points = np.array(xywhWithCls[xywhWithCls[:, 0].argsort()], dtype=np.uint16).flatten()
        
        return (points, len(points)//point_size)
    
    @staticmethod
    def imgToArray(coloredImg: np.ndarray):
        return np.array(coloredImg.flatten(), dtype=np.uint8)
    
    
    @staticmethod
    def setFuncs():
        
        cpp.lib._Tracker.argtypes = [cpp.uint16_array, cpp.uint16, cpp.uint8_array, cpp.uint16, cpp.uint16, cpp.bool]
        cpp.lib._Tracker.restype = cpp.object
        
        cpp.lib._track.argtypes = [cpp.object, cpp.uint16_array, cpp.uint16, cpp.uint8_array]
        
        
        
    def __init__(self, YOLO_result, coloredImg: np.ndarray, visualize = False) -> None:
        """Creates a Tracker object
        """
        
        Tracker.setFuncs()
        
        points, size = Tracker.YoloToPointsWithClasses(YOLO_result, 5)

        self.obj = cpp.lib._Tracker(points, cpp.c_uint16(size), Tracker.imgToArray(coloredImg), cpp.c_uint16(coloredImg.shape[0]), cpp.c_uint16(coloredImg.shape[1]), cpp.c_bool(visualize))
    
    def track(self, YOLO_result, coloredImg: np.ndarray):
        points, size = Tracker.YoloToPointsWithClasses(YOLO_result, 5)
        cpp.lib._track(self.obj, points, cpp.c_uint16(size), Tracker.imgToArray(coloredImg))
    
    
    
        
        