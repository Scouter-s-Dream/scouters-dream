#include "linkedList.hpp"

LinkedList::LinkedList(){
    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    this->start = newNode;
    this->end = newNode;
}

LinkedList::LinkedList(Rect& boundingBox){
    std::shared_ptr<Node> newNode = std::make_shared<Node>(boundingBox);
    this->start = newNode;
    this->end = newNode;
}

Node LinkedList::getItem(uint16_t index){

    if (index > this->length || index < 0){
        throw "Out of Bounds";
    }

    std::shared_ptr<Node> ref = this->start;

    for (uint16_t i = 0; i < index; i++){
        ref = ref->next;
    }

    return *ref;

}

void LinkedList::append(Rect boundingBox){
    std::shared_ptr<Node> newNode = std::make_shared<Node>(boundingBox); 
    this->end->next = newNode;
    this->end = newNode;
    this->length++;
}

void LinkedList::remove(uint16_t index){
    
    if (index > this->length || index < 0){
        throw "Out of Bounds";
    }

    std::shared_ptr<Node> ref = this->start;

    if (index == 0){
        this->start = ref->next;
        return;
    }

    for (uint16_t i = 0; ref != nullptr && i < index - 1; i++){
        ref = ref->next;
    }

    std::shared_ptr<Node> next = ref->next->next;
    ref->next = next;
    this->length--;
    
}

void LinkedList::prepend(Rect boundingBox){
    std::shared_ptr<Node> newNode = std::make_shared<Node>(boundingBox);
    newNode->next = this->start;    
    this->start = newNode;
    this->length++;
}

void LinkedList::insert(uint16_t index, Rect boundingBox){
    if (index > this->length || index < 0){
        throw "Out of Bounds";
    }

    std::shared_ptr<Node> newNode = std::make_shared<Node>(boundingBox);

    std::shared_ptr<Node> ref = this->start;

    if (index == 0){
        this->prepend(boundingBox);
    }
    
    if (index == this->length){
        this->append(boundingBox);
    }

    for (uint16_t i = 0; ref != nullptr && i < index - 1; i++){
        ref = ref->next;
    }

    newNode->next = ref->next;
    ref->next = newNode;
}
