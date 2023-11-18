#ifndef __TRACKER__HPP
#define __TRACKER_HPP

#include "boundingBox.hpp"
#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>
#include "entity.hpp"

class Tracker{
    
    public:
        const bool visualize;
        const uint rows;
        const uint cols;
        cv::Mat img;
        std::vector<Entity> lastEntities;
        std::vector<Entity> currentEntities;

        Tracker(uint* pointsWithClass, uint size, uint8_t* img, uint rows, uint cols, bool visualize);

        void setTrackPoints(uint16_t* pointsWithClass, uint size);

        void setImg(uint8_t* img);

        void drawBoundingBoxes();
        
        uint* findSimilarBoundingBoxes();

        std::vector<Entity> boundingBoxesToEntites(std::vector<BoundingBox> boundingBoxes, uint* pointsWithClass);

        void stablePoints();

        void track(uint16_t* pointsWithClasses, uint size, uint8_t* img);

};  


#endif