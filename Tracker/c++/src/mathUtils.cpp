#include "mathUtils.hpp"

/*
Returns The square distance between two points.
-
Args: 
 - `pointA (number[])` -> the first point.
 - `pointB (number[])` -> the second point
Returns:
 - `squareDistance (uint)` -> the distance between the points.
*/
uint squareDistance(Point A, Point B){
    return pow(A.x - B.x, 2) + pow(A.y - B.y, 2);
}
