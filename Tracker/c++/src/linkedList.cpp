#include "linkedList.hpp"

Node* NodeConstractor(BoundingBox boundingBox){

    //TODO Turn into const, sizof is just a useless clac because it's const
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->boundingBox = boundingBox;
    newNode->next = nullptr;
    return newNode;
}

LinkedList::LinkedList(){
    this->start->next = nullptr;
    this->end->next = nullptr;
}

LinkedList::LinkedList(Node *node){
    this->start->next = node;
    this->end->next = node;
}

Node LinkedList::getItem(unsigned int index){

    if (index < this->length && index > 0){
        throw "Out of Bounds";
    }

    Node* ref = this->start;

    for (unsigned int i = 0; i < index; i++){
        ref = ref->next;
    }

    return *ref;

}

void LinkedList::append(BoundingBox boundingBox){
    Node* newNode = NodeConstractor(boundingBox);
    this->end->next = newNode;    
    this->end = newNode;
    this->length += 1;
}

void LinkedList::remove(unsigned int index){
    
    if (index < this->length && index > 0){
        throw "Out of Bounds";
    }

    Node* ref = this->start;

    if (index == 0){
        this->start = ref->next;
        free(ref); //TODO make delete func 
        return;
    }

    if (index == this->length){

    }

    for (unsigned int i = 0; ref != nullptr && i < index - 1; i++){
        ref = ref->next;
    }

    Node* next = ref->next->next;
    free(ref->next);
    ref->next = next;
    
}

void LinkedList::prepend(BoundingBox boundingBox){

}

void LinkedList::insert(BoundingBox boundingBox, unsigned int index){

}
