import cpp_utils as cpp
import numpy as np

class Tracker():        
    
    @staticmethod
    def YoloToPointsAndTypes(YOLO_result):
        boxes = YOLO_result.boxes.cpu().numpy()      
        points = np.array(boxes.xyxy.flatten(), dtype=np.uint16)
        types = np.array(boxes.cls.flatten(), dtype=np.uint16)
        return (points, types, len(types))
    
    @staticmethod
    def imgToArray(coloredImg: np.ndarray):
        return np.array(coloredImg.flatten(), dtype=np.uint8)
    
    
    @staticmethod
    def setFuncs():
        
        cpp.lib._Tracker.argtypes = [cpp.uint16_array, cpp.uint16_array, cpp.uint16, cpp.uint8_array, cpp.uint16, cpp.uint16, cpp.bool]
        cpp.lib._Tracker.restype = cpp.object
        
        cpp.lib._track.argtypes = [cpp.object, cpp.uint16_array, cpp.uint16_array, cpp.uint16, cpp.uint8_array]
        
        
        
    def __init__(self, YOLO_result, coloredImg: np.ndarray, visualize = False) -> None:
        """Creates a Tracker object
        """
        
        Tracker.setFuncs()
        
        points, types, size = Tracker.YoloToPointsAndTypes(YOLO_result)

        self.obj = cpp.lib._Tracker(points, types, cpp.c_uint16(size), Tracker.imgToArray(coloredImg), cpp.c_uint16(coloredImg.shape[0]), cpp.c_uint16(coloredImg.shape[1]), cpp.c_bool(visualize))
    
    def track(self, YOLO_result, coloredImg: np.ndarray):
        points, types, size = Tracker.YoloToPointsAndTypes(YOLO_result)
        cpp.lib._track(self.obj, points, types, cpp.c_uint16(size), Tracker.imgToArray(coloredImg))
    
    
    
        
        