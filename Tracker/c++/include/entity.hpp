#ifndef __ENTITY__HPP__
#define __ENTITY__HPP__

#include "boundingBox.hpp"
#include "linkedList.hpp"


class Entity{

    private:

        bool visualize = false;
        unsigned short id;
        char type;
        short velocityX;
        short velocityY;
        BoundingBox boundingBox;
        LinkedList trajectory;

    public:

        Entity(unsigned short id, char type, BoundingBox box);
        
        void setBox(BoundingBox boundingBox);

        BoundingBox* getBoundingBox();

        unsigned short getId();

        void setVelocity();

        void addToTrajectory();    

};


#endif