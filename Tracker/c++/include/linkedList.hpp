#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include "boundingBox.hpp"

using std::unique_ptr;
//May be added more stuff 
typedef struct Node{
    
    BoundingBox boundingBox;
    struct Node *next;

};

class LinkedList{

    //First item
    public: 
        unique_ptr<Node> start;
        unique_ptr<Node> end;
        unsigned int length = 0;

        LinkedList();

        LinkedList(Node node);

        Node getItem(unsigned int index);

        void append(BoundingBox boundingBox);

        void remove(unsigned int index);

        void prepend(BoundingBox boundingBox);

        void insert(BoundingBox boundingBox, unsigned int index);


};

#endif