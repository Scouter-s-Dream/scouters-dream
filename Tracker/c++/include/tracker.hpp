#ifndef __TRACKER__HPP
#define __TRACKER_HPP

#include "boundingBox.hpp"
#include <memory>

class Tracker{
    
    public:

        std::unique_ptr<BoundingBox[]> stableBoundingBoxes;
        std::unique_ptr<BoundingBox[]> lastStableBoundingBoxes;
        std::shared_ptr<BoundingBox[]> currentBoundingBoxes;
        int numOfStableBoundingBoxes = 0;
        int numOfLastStableBoundingBoxes = 0;
        int numOfCurrentBoundingBoxes = 0;

        Tracker();

        void setTrackPoints(int *pointsWithClass, int size);


        int* findSimilarBoundingBoxes();

        void stablePoints();

};


#endif