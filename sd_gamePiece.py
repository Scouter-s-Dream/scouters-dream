from ultralytics import YOLO
from sd_robot import Robot
import numpy as np
from sd_utils import center, distance
from sd_globals import *

class GamePiece():
    
    
    def __init__(self,id:int, type:bool, position: tuple[np.ndarray[int, int], np.ndarray[int, int]]):
        """constractor for the GamePiece class

        Args:
            id (int): number to identify the game piece in tracking
            type (bool): cone = False, cube = True
            position (tuple[np.ndarray[int, int], np.ndarray[int, int]]): the position of the bounding box of the game piece
        """
        
        self.id = id
        self.type = type
        self.position = position
        self.center = center(position)
        self.set_side() 
 
    def is_red(self) -> bool:
        """checks if the game piece is in the red community

        Returns:
            bool: True if Red, False else
        """
        if self.position[0][0] < RED_COMMUNITY_POSITION[1][0] and self.position[1][0] > RED_COMMUNITY_POSITION[0][0] and self.position[0][1] < RED_COMMUNITY_POSITION[1][1] and self.position[1][1] > RED_COMMUNITY_POSITION[0][1]:
            return True
        else:
            return False

    def is_blue(self) -> bool:
        """checks if the game piece is in the Blue community

        Returns:
            bool: True if Blue, False else
        """
        if self.position[0][0] < BLUE_COMMUNITY_POSITION[1][0] and self.position[1][0] > BLUE_COMMUNITY_POSITION[0][0] and self.position[0][1] < BLUE_COMMUNITY_POSITION[1][1] and self.position[1][1] > BLUE_COMMUNITY_POSITION[0][1]:
            return True
        else:
            return False

    def set_side(self):
        """checks if a game piece is in the Blue Community or in the Red Community
        """
        if self.is_blue():
            GAMEPIECE_BLUESIDE.append(self)
            self.blue = True
            self.red = False
            return
        
        if self.is_red():
            GAMEPIECE_REDSIDE.append(self)
            self.red = True
            self.blue = False
            return
        
        self.blue = False
        self.red = False
        
    def closet_redRobot(self) -> Robot:
        """checks the closest Red Robot to the GamePiece

        Returns:
            Robot: the Robot instance Closet to the GamePiece
        """
        closet_robot = None
        min_dist = np.inf
        for robot in ROBOT_REDSIDE:
            dist = distance(self.center, robot.center) 
            if dist < min_dist:
                closet_robot = robot
                min_dist = dist
                
        return closet_robot
                
    def closet_blueRobot(self) -> Robot:
        """checks the closest Blue Robot to the GamePiece

        Returns:
            Robot: the Robot instance Closet to the GamePiece
        """
        closet_robot = None
        min_dist = np.inf
        for robot in ROBOT_BLUESIDE:
            dist = distance(self.center, robot.center) 
            if dist < min_dist:
                closet_robot = robot
                min_dist = dist
                
        return closet_robot            

    # def closet_blueRobot(self)
    
    
        
    