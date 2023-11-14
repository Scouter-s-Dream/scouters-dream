#!/bin/sh
cmake -DCMAKE_CXX_COMPILER=/usr/bin/gcc-11 -B ./build
cd build 
make -j4