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
template<typename T>
T squareDistance(vector<T> pointA, vector<T> pointB){
    return pow(pointA[0] - pointB[0], 2) + pow(pointA[1] - pointB[1], 2);
}
