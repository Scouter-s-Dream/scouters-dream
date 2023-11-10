#ifndef __MATH_UTILS__HPP_
#define __MATH_UTILS_HPP_

#include <opencv4/opencv2/opencv.hpp>
#include <stdio.h>

using cv::Mat;

double max(Mat frame);

double min(Mat frame);

double squareDistance(int* pointA, int* pointB);

#endif