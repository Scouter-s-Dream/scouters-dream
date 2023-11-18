#include "entity.hpp"

Entity::Entity(uint16_t id, uint16_t type, BoundingBox boundingBox) : id(id), type(type){
    this->setBox(boundingBox);
    this->trajectory = LinkedList();
    
}

void Entity::setBox(BoundingBox boundingBox){
    this->boundingBox = boundingBox;
}

void Entity::addToTrajectory(){
    this->trajectory.append(this->boundingBox, this->velocities);
}

BoundingBox Entity::getBoundingBox(){
    return this->boundingBox;
}

const uint16_t Entity::getId(){
    return this->id;
}

uint Entity::squareDistanceTo(Entity &e){
    return this->getBoundingBox().squareDistanceTo(e.getBoundingBox());
}

Entity Entity::findClosest(std::vector<Entity> entityVector){
    
    uint16_t distance = UINT16_MAX;
    uint16_t idx = entityVector.size() + 1; // not in array.

    for (uint16_t i = 0, size = entityVector.size(); i < size; i++){
        int currentDistance = this->squareDistanceTo(entityVector[i]);
        if (currentDistance < distance){
            idx = i;
            distance = currentDistance;
        }
    }

    return entityVector[idx];
}