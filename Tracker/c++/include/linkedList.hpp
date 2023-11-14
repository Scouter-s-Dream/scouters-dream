#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include "boundingBox.hpp"

typedef struct Node Node;

struct Node{
    
    unsigned short velocity;
    BoundingBox boundingBox;
    struct Node *next;

};

Node* NodeConstractor(BoundingBox boundingBox, unsigned short velocity);

Node* emptyNode();

class LinkedList{

    public: 
        Node* start;
        Node* end;
        unsigned int length = 0;

        LinkedList();

        LinkedList(Node Node);

        LinkedList(BoundingBox boundingBox, unsigned short velocity);

        Node getItem(unsigned int index);

        void append(BoundingBox boundingBox, unsigned short velocity);

        void remove(unsigned int index);

        void prepend(BoundingBox boundingBox, unsigned short velocity);

        void insert(unsigned int index, BoundingBox boundingBox, unsigned short velocity);

        ~LinkedList(); //TODO create destructor that frees all the list.

};

#endif