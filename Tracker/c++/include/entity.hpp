#ifndef __ENTITY__HPP__
#define __ENTITY__HPP__

#include "boundingBox.hpp"
#include "linkedList.hpp"
#include <limits>

class Entity{

    private:

        const uint16_t id;
        const uint16_t type;
        vector<short> velocities;
        BoundingBox boundingBox;
        LinkedList trajectory;

    public:

        Entity(uint16_t id, uint16_t type, BoundingBox box);
        
        void setBox(BoundingBox boundingBox);

        BoundingBox getBoundingBox();

        const uint16_t getId();

        void setVelocity();

        vector<short> getVelocities();

        void addToTrajectory();    

        uint squareDistanceTo(Entity &e);

        Entity findClosest(std::vector<Entity>  entityVector);

};


#endif