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
        const uint16_t rows;
        const uint16_t cols;
        cv::Mat img;
        std::vector<Entity> entitys;
        std::vector<Entity> currentEntities;

        Tracker(uint16_t* pointsWithClass, uint16_t size, uint8_t* img, uint16_t rows, uint16_t cols, bool visualize);

        void setTrackPoints(uint16_t* pointsWithClass, uint16_t size);

        void setImg(uint8_t* img);

        void drawBoundingBoxes();
        
        uint* findSimilarBoundingBoxes();

        std::vector<Entity> boundingBoxesToEntites(std::vector<BoundingBox> boundingBoxes, uint16_t* pointsWithClass);

        void stablePoints();

        void track(uint16_t* pointsWithClasses, uint16_t size, uint8_t* img);

};  


#endif