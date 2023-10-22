from ultralytics import YOLO
from sd_robot import Robot
import numpy as np
from sd_utils import center, distance
from sd_globals import *

class GamePiece():
    
    
    def __init__(self,id:int, type:bool, position: tuple[np.ndarray[int, int], np.ndarray[int, int]]):
        self.id = id
        self.type = type
        self.position = position
        self.center = center(position)
        self.set_side()
        
        
    def update_position(self, position: tuple[np.ndarray[int, int], np.ndarray[int, int]]):
        self.position = position
        
    def get_position(self) -> tuple[np.ndarray[int, int], np.ndarray[int, int]]:
        return self.position   
 
    def is_red(self) -> bool:
        if self.position[0][0] < RED_COMMUNITY_POSITION[1][0] and self.position[1][0] > RED_COMMUNITY_POSITION[0][0] and self.position[0][1] < RED_COMMUNITY_POSITION[1][1] and self.position[1][1] > RED_COMMUNITY_POSITION[0][1]:
            return True

    def is_blue(self) -> bool:
        if self.position[0][0] < BLUE_COMMUNITY_POSITION[1][0] and self.position[1][0] > BLUE_COMMUNITY_POSITION[0][0] and self.position[0][1] < BLUE_COMMUNITY_POSITION[1][1] and self.position[1][1] > BLUE_COMMUNITY_POSITION[0][1]:
            return True

    def set_side(self):
        
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
        closet_robot = None
        min_dist = np.inf
        for robot in ROBOT_REDSIDE:
            dist = distance(self.center, robot.center) 
            if dist < min_dist:
                closet_robot = robot
                min_dist = dist
                
        return closet_robot
                
    def closet_blueRobot(self) -> Robot:
        closet_robot = None
        min_dist = np.inf
        for robot in ROBOT_BLUESIDE:
            dist = distance(self.center, robot.center) 
            if dist < min_dist:
                closet_robot = robot
                min_dist = dist
                
        return closet_robot            

    # def closet_blueRobot(self)
    
    
        
    