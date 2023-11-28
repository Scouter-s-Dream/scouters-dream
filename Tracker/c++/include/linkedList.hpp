#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include "rectExtention.hpp"
#include <memory>

typedef struct Node Node;
typedef cv::Size2i Velocity2D;

struct Node{
    
    const vector<short> velocities;
    const Rect rect;
    std::shared_ptr<struct Node> next;

    Node(Rect rect, Node* next): rect(rect), next(nullptr) {}

    Node(Rect rect): rect(rect), next(nullptr){}

    Node(): rect(Rect()), next(nullptr) {}
    

};

class LinkedList{

    public: 
        std::shared_ptr<Node> start;
        std::shared_ptr<Node> end;
        uint16_t length = 0;

        LinkedList();

        LinkedList(Rect& rect);

        Node getItem(uint16_t index);

        void append(Rect rect);

        void remove(uint16_t index);

        void prepend(Rect rect);

        void insert(uint16_t index, Rect rect);

};

#endif