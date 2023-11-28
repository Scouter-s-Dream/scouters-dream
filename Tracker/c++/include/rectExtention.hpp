#ifndef __BOUNDING_BOX_HPP
#define __BOUNDING_BOX_HPP

#include "mathUtils.hpp"
#include "vectorFuncs.hpp"

#define POINT_SIZE  (4)
#define POINTCLASS_SIZE (5)

class Rect : public cv::Rect_<uint16_t>{
    using Base = cv::Rect_<uint16_t>;
    using Base::Base;
    
    public: 
    uint squareDistanceTo(Rect& r);
    bool isCloseTo(Rect& r, double distance);
    // bool isIntersectingTo(Rect& r);
};

std::ostream& operator<<(std::ostream& os, Rect& r);

std::vector<Rect> pointsToRects(uint16_t *pointsWithClass, uint16_t size);

#endif 