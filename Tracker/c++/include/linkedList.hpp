#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include "boundingBox.hpp"
#include <memory>

typedef struct Node Node;

struct Node{
    
    const vector<short> velocities;
    const BoundingBox boundingBox;
    std::shared_ptr<struct Node> next;

    Node(BoundingBox boundingBox, Node* next): boundingBox(boundingBox), next(nullptr) {}

    Node(BoundingBox boundingBox): boundingBox(boundingBox), next(nullptr){}

    Node(): boundingBox(BoundingBox()), next(nullptr) {}
    

};

class LinkedList{

    public: 
        std::shared_ptr<Node> start;
        std::shared_ptr<Node> end;
        uint16_t length = 0;

        LinkedList();

        LinkedList(Node Node);

        LinkedList(BoundingBox& boundingBox);

        Node getItem(uint16_t index);

        void append(BoundingBox boundingBox);

        void remove(uint16_t index);

        void prepend(BoundingBox boundingBox);

        void insert(uint16_t index, BoundingBox boundingBox);

        LinkedList operator=(const LinkedList& list);


};

#endif