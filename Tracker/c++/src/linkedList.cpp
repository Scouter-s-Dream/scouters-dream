#include "linkedList.hpp"

Node* NodeConstractor(BoundingBox boundingBox, short velocityX, short velocityY){

    //TODO Turn into const, sizof is just a useless clac because it's const
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->velocityX = velocityX;
    newNode->velocityY = velocityY;
    newNode->boundingBox = boundingBox;
    newNode->next = nullptr;
    return newNode;
}

Node* emptyNode(){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->next = nullptr;
    return newNode;
}

LinkedList::LinkedList(){
    Node* newNode = emptyNode();
    this->start = newNode;
    this->end = newNode;
}

LinkedList::LinkedList(BoundingBox boundingBox, short velocityX, short velocityY){
    Node* newNode = NodeConstractor(boundingBox, velocityX, velocityY);
    this->start = newNode;
    this->end = newNode;
}

LinkedList::LinkedList(Node node){ //node needs to be alocated on the heap!
    this->start = &node;
    this->end = &node;
}

Node LinkedList::getItem(uint16_t index){

    if (index > this->length || index < 0){
        throw "Out of Bounds";
    }

    Node* ref = this->start;

    for (uint16_t i = 0; i < index; i++){
        ref = ref->next;
    }

    return *ref;

}

void LinkedList::append(BoundingBox boundingBox, short velocityX, short velocityY){
    Node* newNode = NodeConstractor(boundingBox, velocityX, velocityY); 
    this->end->next = newNode;    
    this->end = newNode;
    this->length++;
}

void LinkedList::remove(uint16_t index){
    
    if (index > this->length || index < 0){
        throw "Out of Bounds";
    }

    Node* ref = this->start;

    if (index == 0){
        this->start = ref->next;
        free(ref);
        return;
    }

    for (uint16_t i = 0; ref != nullptr && i < index - 1; i++){
        ref = ref->next;
    }

    Node* next = ref->next->next;
    free(ref->next);
    ref->next = next;
    this->length--;
    
}

void LinkedList::prepend(BoundingBox boundingBox, short velocityX, short velocityY){
    Node* newNode = NodeConstractor(boundingBox, velocityX, velocityY); 
    newNode->next = this->start;    
    this->start = newNode;
    this->length++;
}

void LinkedList::insert(uint16_t index, BoundingBox boundingBox, short velocityX, short velocityY){
    if (index > this->length || index < 0){
        throw "Out of Bounds";
    }

    Node* newNode = NodeConstractor(boundingBox, velocityX, velocityY); 

    Node* ref = this->start;

    if (index == 0){
        this->prepend(boundingBox, velocityX, velocityY);
    }
    
    if (index == this->length){
        this->append(boundingBox, velocityX, velocityY);
    }

    for (uint16_t i = 0; ref != nullptr && i < index - 1; i++){
        ref = ref->next;
    }

    newNode->next = ref->next;
    ref->next = newNode;
}
