#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include "boundingBox.hpp"

typedef struct Node Node;

struct Node{
    
    BoundingBox boundingBox;
    struct Node *next;

};

Node* NodeConstractor(BoundingBox boundingBox);

class LinkedList{

    //First item
    public: 
        Node start;
        Node end;
        unsigned int length = 0;

        LinkedList();

        LinkedList(Node *heapNode);

        Node getItem(unsigned int index);

        void append(BoundingBox boundingBox);

        void remove(unsigned int index);

        void prepend(BoundingBox boundingBox);

        void insert(BoundingBox boundingBox, unsigned int index);


};

#endif