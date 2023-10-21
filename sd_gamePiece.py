from ultralytics import YOLO
import platform

class GamePiece():
    
    @staticmethod
    def setup_model(path: str):
        """
        ## Set up the YOLO model with pre-trained weights.
        
        Args:
        ----
            - path (str): the path to the model .pt file
        ----
        Returns:
        ---
           - YOLO: The YOLO model configured with pre-trained weights.
        """
        return YOLO(path)
    