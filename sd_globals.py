import numpy as np
from sd_robot import Robot
from sd_gamePiece import GamePiece

GRID_POSITION_HIGH:tuple[np.ndarray[int, int], np.ndarray[int, int]] = (np.array([0, 0]), np.array(0, 0))

GRID_POSITION_MID:tuple[np.ndarray[int, int], np.ndarray[int, int]] = (np.array([0, 0]), np.array(0, 0))

GRID_POSITION_LOW:tuple[np.ndarray[int, int], np.ndarray[int, int]] = (np.array([0, 0]), np.array(0, 0))    

RED_COMMUNITY_POSITION:tuple[np.ndarray[int, int], np.ndarray[int, int]] = ()

BLUE_COMMUNITY_POSITION:tuple[np.ndarray[int, int], np.ndarray[int, int]] = ()

GAMEPIECE_REDSIDE:list[GamePiece] = []

GAMEPIECE_BLUESIDE:list[GamePiece] = []

ROBOT_REDSIDE:list[Robot] = []

ROBOT_BLUESIDE:list[Robot] = []