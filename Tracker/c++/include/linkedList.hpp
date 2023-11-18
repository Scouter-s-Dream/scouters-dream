#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include "boundingBox.hpp"

typedef struct Node Node;

struct Node{
    
    vector<short> velocities;
    BoundingBox boundingBox;
    struct Node *next;

};

Node* NodeConstractor(BoundingBox boundingBox, vector<short> velocities);

Node* emptyNode();

class LinkedList{

    public: 
        Node* start;
        Node* end;
        uint16_t length = 0;

        LinkedList();

        LinkedList(Node Node);

        LinkedList(BoundingBox boundingBox, vector<short> velocities);

        Node getItem(uint16_t index);

        void append(BoundingBox boundingBox, vector<short> velocities);

        void remove(uint16_t index);

        void prepend(BoundingBox boundingBox, vector<short> velocities);

        void insert(uint16_t index, BoundingBox boundingBox, vector<short> velocities);

        // ~LinkedList(); //TODO create destructor that frees all the list.

};

#endif