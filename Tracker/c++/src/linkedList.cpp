#include "linkedList.hpp"

Node* NodeConstractor(BoundingBox boundingBox){

    //TODO Turn into const, sizof is just a useless clac because it's const
    Node* newNode;
    newNode = malloc(sizeof(Node));
    newNode->boundingBox = boundingBox;
    newNode->next = nullptr;
    return newNode;
}

LinkedList::LinkedList(){
    this->start = nullptr;
    this->end = nullptr;
}

LinkedList::LinkedList(Node *heapNode){
    this->start = heapNode;
    this->end = heapNode;
}

Node LinkedList::getItem(unsigned int index){

}

void LinkedList::append(BoundingBox boundingBox){
    
    Node* newNode = NodeConstractor(boundingBox);
    this->end.next = newNode;    
}

void LinkedList::remove(unsigned int index){

}

void LinkedList::prepend(BoundingBox boundingBox){

}

void LinkedList::insert(BoundingBox boundingBox, unsigned int index){

}
