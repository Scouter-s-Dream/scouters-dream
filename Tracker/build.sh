#!/bin/sh
cmake -B ./build
cd build 
make -j4
mv libTracker.so ../libTracker.so