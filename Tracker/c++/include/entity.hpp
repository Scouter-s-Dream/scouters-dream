#ifndef __ENTITY__HPP__
#define __ENTITY__HPP__

#include "boundingBox.hpp"
#include "linkedList.hpp"
#include <limits>
#include "vectorFuncs.hpp"

class Entity{

    private:

        const uint16_t id;
        const uint16_t type;
        vector<short> velocities;
        BoundingBox boundingBox;

    public:
        std::shared_ptr<LinkedList> trajectory;
        
        Entity(const Entity& e);

        Entity(uint16_t id, uint16_t type, BoundingBox box);

        Entity();
        
        void setBox(BoundingBox boundingBox);

        BoundingBox getBoundingBox();

        const uint16_t getId();

        const uint16_t getType();

        std::shared_ptr<LinkedList> getTrajetctory();

        std::shared_ptr<LinkedList> getTrajetctory() const;

        BoundingBox getBoundingBox() const;

        const uint16_t getId() const;

        const uint16_t getType() const;

        void setVelocity();

        vector<short> getVelocities();

        void addToTrajectory();     

        uint squareDistanceTo(Entity &e);

        Entity operator=(const Entity& e);
        
        Entity findClosest(std::vector<Entity> &entityVector);

};


#endif