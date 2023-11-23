#include "entity.hpp"

Entity::Entity(uint16_t id, uint16_t type, BoundingBox boundingBox) : id(id), type(type){
    this->setBox(boundingBox);
    // this->trajectory = new LinkedList(boundingBox);
    
}

Entity::Entity() : id(UINT16_MAX), type(UINT16_MAX){
    //generates empty enitity
    this->boundingBox = BoundingBox();
    
}

void Entity::setBox(BoundingBox boundingBox){
    this->boundingBox = boundingBox;
}

void Entity::addToTrajectory(){
    this->trajectory->append(this->boundingBox);
}

BoundingBox Entity::getBoundingBox(){
    return this->boundingBox;
}

const uint16_t Entity::getId(){
    return this->id;
}

const uint16_t Entity::getType(){
    return this->type;
}

BoundingBox Entity::getBoundingBox() const{
    return this->boundingBox;
}

const uint16_t Entity::getId() const{
    return this->id;
}

const uint16_t Entity::getType() const{
    return this->type;
}

uint Entity::squareDistanceTo(Entity &e){
    return this->getBoundingBox().squareDistanceTo(e.getBoundingBox());
}

std::ostream& operator<<(std::ostream& os, const Entity t){
    // Printing all the elements
    // using <<
    os << "id: " << t.getId() << "\n";
    os << "type: " << t.getType() << "\n";
    os << "box: " << t.getBoundingBox() << "\n";
    return os;
}

Entity Entity::findClosest(std::vector<Entity> &entityVector){
    // uint16_t maxDistance = this->getBoundingBox().getWidth();
    vector<Entity> newEntityVector;
    uint16_t distance = UINT16_MAX;
    uint16_t idx = entityVector.size(); // not in array.
    for (uint16_t i = 0, size = entityVector.size(); i < size; i++){
        uint currentDistance = this->squareDistanceTo(entityVector[i]);
        if (currentDistance < distance){
            idx = i;
            distance = currentDistance;
        }
    }
    std::cout << "idx " << idx << "\n\n";
    Entity closet = entityVector[idx];
    entityVector[idx] = Entity();

    return closet;
}
