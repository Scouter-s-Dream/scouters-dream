#ifndef __MATH_UTILS__HPP_
#define __MATH_UTILS_HPP_

#include <opencv4/opencv2/opencv.hpp>
#include <stdio.h>

using cv::Mat;

double max(Mat frame);

double min(Mat frame);

template<typename T1, typename T2>
double squareDistance(T1 *pointA, T2 *pointB);

#endif