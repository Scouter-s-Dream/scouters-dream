"""
cpp_utils
===

In this module are useful types and functions 
that help communicate with the cpp program
"""

import numpy as np
import ctypes

lib = ctypes.CDLL('./Tracker/libTracker.so')

def c_int16(int: int):
    return ctypes.c_int16(int)

def c_uint16(int: int):
    return ctypes.c_uint16(int)
 
def c_int32(int: int):
    return ctypes.c_int32(int)

def c_uint32(int: int):
    return ctypes.c_uint32(int)

def c_int64(int: int):
    return ctypes.c_int64(int)

def c_string(string: str):
    return ctypes.create_string_buffer(string.encode())

def c_char(char):
    return ctypes.c_char(char)

def c_double(float: float):
    return ctypes.c_double(float)

def c_float(float: float):
    return ctypes.c_float(float)

def c_bool(bool: bool):
    return ctypes.c_bool(bool)

object = ctypes.POINTER(ctypes.c_char)
    
int16 = ctypes.c_int16

uint16 = ctypes.c_uint16

int32 = ctypes.c_int32

int64 = ctypes.c_int64

bool = ctypes.c_bool

uint8_array = np.ctypeslib.ndpointer(dtype=np.uint8, ndim=1, flags='C_CONTIGUOUS') 

uint16_array = np.ctypeslib.ndpointer(dtype=np.uint16, ndim=1, flags='C_CONTIGUOUS') 

int16_array = np.ctypeslib.ndpointer(dtype=np.int16, ndim=1, flags='C_CONTIGUOUS') 

int32_array = np.ctypeslib.ndpointer(dtype=np.int32, ndim=1, flags='C_CONTIGUOUS')

int64_array = np.ctypeslib.ndpointer(dtype=np.int64, ndim=1, flags='C_CONTIGUOUS')

double_array = np.ctypeslib.ndpointer(dtype=np.double, ndim=1, flags='C_CONTIGUOUS')

float_array = np.ctypeslib.ndpointer(dtype=np.float32, ndim=1, flags='C_CONTIGUOUS')