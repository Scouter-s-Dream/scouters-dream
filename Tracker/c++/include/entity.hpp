#ifndef __ENTITY__HPP__
#define __ENTITY__HPP__

#include "boundingBox.hpp"
#include "linkedList.hpp"
#include <limits>

class Entity{

    private:

        bool visualize = false;
        uint16_t id;
        char type;
        short velocityX;
        short velocityY;
        BoundingBox boundingBox;
        LinkedList trajectory;

    public:

        Entity(uint16_t id, char type, BoundingBox box);
        
        void setBox(BoundingBox boundingBox);

        BoundingBox* getBoundingBox();

        uint16_t getId();

        void setId(uint16_t id);

        void setVelocity();

        void addToTrajectory();    

        int squareDistanceTo(Entity &e);

        Entity* findClosest(std::vector<Entity>  entityVector);

};


#endif