#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include "boundingBox.hpp"

typedef struct Node Node;

struct Node{
    
    short velocityX;
    short velocityY;
    BoundingBox boundingBox;
    struct Node *next;

};

Node* NodeConstractor(BoundingBox boundingBox, short velocityX, short velocityY);

Node* emptyNode();

class LinkedList{

    public: 
        Node* start;
        Node* end;
        unsigned int length = 0;

        LinkedList();

        LinkedList(Node Node);

        LinkedList(BoundingBox boundingBox, short velocityX, short velocityY);

        Node getItem(unsigned int index);

        void append(BoundingBox boundingBox, short velocityX, short velocityY);

        void remove(unsigned int index);

        void prepend(BoundingBox boundingBox, short velocityX, short velocityY);

        void insert(unsigned int index, BoundingBox boundingBox, short velocityX, short velocityY);

        // ~LinkedList(); //TODO create destructor that frees all the list.

};

#endif