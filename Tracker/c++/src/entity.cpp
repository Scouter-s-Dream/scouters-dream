#include "entity.hpp"

Entity::Entity(unsigned short id, char type, BoundingBox boundingBox){
    
    this->id = id;
    this-> type = type;
    this->setBox(boundingBox);
    this->trajectory = LinkedList();
    
}

void Entity::setBox(BoundingBox boundingBox){
    this->boundingBox = boundingBox;
}

void Entity::addToTrajectory(){
    this->trajectory.append(this->boundingBox, this->velocity);
}