#ifndef __ENTITY__HPP__
#define __ENTITY__HPP__

#include "boundingBox.hpp"
#include "linkedList.hpp"

class Entity{

    private:
        unsigned short id;
        char type;
        short velocityX;
        short velocityY;
        BoundingBox boundingBox;
        LinkedList trajectory;

    Entity(unsigned short id, char type, BoundingBox box);
    
    void setBox(BoundingBox boundingBox);

    void setVelocity();

    void addToTrajectory();    

};


#endif