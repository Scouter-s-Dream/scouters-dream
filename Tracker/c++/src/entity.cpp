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

    uint maxDistanceSquared = 300*300; //TODO MAKE A SOMEHOW CALCULATED ONE
    uint distanceSquared = UINT32_MAX;
    uint16_t idx; 

    for (uint16_t i = 0, size = entityVector.size(); i < size; i++){
        Entity& checkedEntity = entityVector[i];

        if (this->getType() == checkedEntity.getType()) { 
            uint currentDistanceSquared = this->squareDistanceTo(checkedEntity);

            if (currentDistanceSquared < distanceSquared && currentDistanceSquared <= maxDistanceSquared){
                idx = i;
                distanceSquared = currentDistanceSquared;
            }
        }       
    }
    return idx;
}

void Entity::clacVelocities(uint numOfFrames){
    //units are pixels per frame   
    if (this->trajectory->length >= numOfFrames){
        const Rect& startRect = this->trajectory->getItem(numOfFrames - 1).rect;
        const Rect& endRect = this->trajectory->getItem(0).rect;

        int velX = (int) ((startRect.x - endRect.x) / numOfFrames);
        int velY = (int) ((startRect.y - endRect.y) / numOfFrames);

        cout << "velX: " << velX << " velY: " << velY << "\n"; 
        //velocites is a cv Size height and width correspond to VelX and velY 
        this->velocities = Velocity2D(velX, velY);
        cout << this->velocities << "\n";
    } 
}

void Entity::clacVelocities(){
    this->clacVelocities(3); //TODO make this number with logic
}

Rect Entity::predictNextBoundingRect(){
    Rect prediction = this->boundingRect;
    prediction.x += this->velocities.height;
    prediction.y += this->velocities.width;
    return prediction;
}

void Entity::draw(cv::Mat& frame, cv::Scalar color){
		cv::rectangle(frame, this->boundingRect, color, 2);
		cv::putText(frame, std::to_string(this->id), this->boundingRect.tl(), cv::FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 255, 0), 2);
}


std::ostream& operator<<(std::ostream& os, const Entity& t){
    os << "id: " << t.getId() << "\n";
    os << "type: " << t.getType() << "\n";
    os << "box: " << t.getBoundingRect() << "\n";
    return os;
}
