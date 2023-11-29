#include "entity.hpp"

Entity::Entity(uint16_t id, uint16_t type, Rect boundingRect) 
    : id(id), type(type){
    this->setBoundingRect(boundingRect);
    this->trajectory = std::make_shared<LinkedList>(boundingRect);
}

Entity::Entity() 
    : id(UINT16_MAX), type(UINT16_MAX){
    this->boundingRect = Rect();
    this->trajectory = std::make_shared<LinkedList>();
}

std::shared_ptr<LinkedList> Entity::getTrajetctory(){
    return this->trajectory;
}

void Entity::setBoundingRect(Rect boundningRect){
    this->boundingRect = boundningRect;
}

void Entity::addToTrajectory(){
    this->trajectory->prepend(this->boundingRect);
}

Rect& Entity::getBoundingRect(){
    return this->boundingRect;
}

const uint16_t Entity::getId(){
    return this->id;
}

const uint16_t Entity::getType(){
    return this->type;
}

std::shared_ptr<LinkedList> Entity::getTrajetctory() const{
    return this->trajectory;
}

Rect Entity::getBoundingRect() const{
    return this->boundingRect;
}

const uint16_t Entity::getId() const{
    return this->id;
}

const uint16_t Entity::getType() const{
    return this->type;
}

uint Entity::squareDistanceTo(Entity& e){
    return this->getBoundingRect().squareDistanceTo(e.getBoundingRect());
}

std::ostream& operator<<(std::ostream& os, Entity& e){
    os << "id: " << e.getId() << "\n";
    os << "type: " << e.getType() << "\n";
    os << "box: " << e.getBoundingRect() << "\n";
    return os;
}

void Entity::emptyBoundingRect(){
    this->setBoundingRect(Rect());
}

uint16_t Entity::findClosestEntityIndex(std::vector<Entity> &entityVector){

    uint16_t maxDistance = UINT16_MAX; //TODO MAKE A SOMEHOW CALCULATED ONE
    uint16_t distance = UINT16_MAX;
    uint16_t idx = entityVector.size() - 1; 

    for (uint16_t i = 0, size = entityVector.size(); i < size; i++){
        Entity& checkedEntity = entityVector[i];
        if (!entityVector[i].getBoundingRect().empty() && this->getType() == checkedEntity.getType()) {
            uint currentDistance = this->squareDistanceTo(checkedEntity);
            if (currentDistance < distance && currentDistance <= maxDistance){
                idx = i;
                distance = currentDistance;
            }
        }       
    }

    return idx;
}

std::ostream& operator<<(std::ostream& os, const Entity& t){
    os << "id: " << t.getId() << "\n";
    os << "type: " << t.getType() << "\n";
    os << "box: " << t.getBoundingRect() << "\n";
    return os;
}
