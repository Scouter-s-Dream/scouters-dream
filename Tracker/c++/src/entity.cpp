#include "entity.hpp"

Entity::Entity(uint16_t id, char type, BoundingBox boundingBox){
    
    this->id = id;
    this-> type = type;
    this->setBox(boundingBox);
    this->trajectory = LinkedList();
    
}

void Entity::setBox(BoundingBox boundingBox){
    this->boundingBox = boundingBox;
}

void Entity::addToTrajectory(){
    this->trajectory.append(this->boundingBox, this->velocityX, this->velocityY);
}

BoundingBox* Entity::getBoundingBox(){
    return &this->boundingBox;
}

uint16_t Entity::getId(){
    return this->id;
}

void Entity::setId(uint16_t id){
    this->id = id;
}

int Entity::squareDistanceTo(Entity &e){
    return this->getBoundingBox()->squareDistanceTo(*(e.getBoundingBox()));
}

Entity* Entity::findClosest(std::vector<Entity> entityVector){
    
    int distance = std::numeric_limits<int>::max();
    uint16_t idx = entityVector.size() + 1; // not in array.

    for (uint16_t i = 0, size = entityVector.size(); i < size; i++){
        int currentDistance = this->squareDistanceTo(entityVector[i]);
        if (currentDistance < distance){
            idx = i;
            distance = currentDistance;
        }
    }

    return &entityVector[idx];
}