#ifndef __MATH_UTILS__HPP_
#define __MATH_UTILS__HPP_

#include <cmath>
#include <opencv4/opencv2/opencv.hpp>


using std::vector;
typedef cv::Point_<uint16_t> Point;

uint squareDistance(Point A, Point B);

#endif