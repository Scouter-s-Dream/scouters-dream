#ifndef __ENTITY__HPP__
#define __ENTITY__HPP__

#include "linkedList.hpp"
#include <limits>
#include "vectorFuncs.hpp"
#include <opencv4/opencv2/opencv.hpp>

class Entity{

    private:

        const uint16_t id;
        const uint16_t type;
        Velocity2D velocities;
        Rect boundingRect;
        std::shared_ptr<LinkedList> trajectory;

    public:
        
        Entity(uint16_t id, uint16_t type, Rect BoundingRect);

        Entity();
        
        void setBoundingRect(Rect newBoundingRect);

        void setVelocity();

        Rect& getBoundingRect();

        const uint16_t getId();

        const uint16_t getType();

        Velocity2D getVelocities();

        std::shared_ptr<LinkedList> getTrajetctory();

        Rect getBoundingRect() const;

        const uint16_t getId() const;

        const uint16_t getType() const;

        std::shared_ptr<LinkedList> getTrajetctory() const;

        void addToTrajectory();     

        uint squareDistanceTo(Entity &e);

        Entity operator=(const Entity& e);
        
        Entity findClosest(std::vector<Entity> &entityVector);
        
};

std::ostream& operator<<(std::ostream& os, Entity& e);

#endif