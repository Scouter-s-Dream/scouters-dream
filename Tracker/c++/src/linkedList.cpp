#include "linkedList.hpp"

Node* NodeConstractor(BoundingBox boundingBox, unsigned short velocity){

    //TODO Turn into const, sizof is just a useless clac because it's const
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->velocity = velocity;
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

LinkedList::LinkedList(BoundingBox boundingBox, unsigned short velocity){
    Node* newNode = NodeConstractor(boundingBox, velocity);
    this->start = newNode;
    this->end = newNode;
}

LinkedList::LinkedList(Node node){ //node needs to be alocated on the heap!
    this->start = &node;
    this->end = &node;
}

Node LinkedList::getItem(unsigned int index){

    if (index > this->length || index < 0){
        throw "Out of Bounds";
    }

    Node* ref = this->start;

    for (unsigned int i = 0; i < index; i++){
        ref = ref->next;
    }

    return *ref;

}

void LinkedList::append(BoundingBox boundingBox, unsigned short velocity){
    Node* newNode = NodeConstractor(boundingBox, velocity); 
    this->end->next = newNode;    
    this->end = newNode;
    this->length++;
}

void LinkedList::remove(unsigned int index){
    
    if (index > this->length || index < 0){
        throw "Out of Bounds";
    }

    Node* ref = this->start;

    if (index == 0){
        this->start = ref->next;
        free(ref);
        return;
    }

    for (unsigned int i = 0; ref != nullptr && i < index - 1; i++){
        ref = ref->next;
    }

    Node* next = ref->next->next;
    free(ref->next);
    ref->next = next;
    this->length--;
    
}

void LinkedList::prepend(BoundingBox boundingBox, unsigned short velocity){
    Node* newNode = NodeConstractor(boundingBox, velocity); 
    newNode->next = this->start;    
    this->start = newNode;
    this->length++;
}

void LinkedList::insert(unsigned int index, BoundingBox boundingBox, unsigned short velocity){
    if (index > this->length || index < 0){
        throw "Out of Bounds";
    }

    Node* newNode = NodeConstractor(boundingBox, velocity); 

    Node* ref = this->start;

    if (index == 0){
        this->prepend(boundingBox, velocity);
    }
    
    if (index == this->length){
        this->append(boundingBox, velocity);
    }

    for (unsigned int i = 0; ref != nullptr && i < index - 1; i++){
        ref = ref->next;
    }

    newNode->next = ref->next;
    ref->next = newNode;
}
