#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include "rectExtention.hpp"
#include <memory>

typedef struct Node Node;

struct Node{
    
    const Rect rect;
    Velocity2D velocities;
    std::shared_ptr<struct Node> next;

    Node(Rect rect, Velocity2D velocities): rect(rect), velocities(velocities), next(nullptr) {}

    Node(Rect rect): rect(rect), next(nullptr){}

    Node(): rect(Rect()), next(nullptr) {}
    

};

class LinkedList{

    public: 
        std::shared_ptr<Node> start;
        std::shared_ptr<Node> end;
        uint16_t length = 0;

        LinkedList();

        LinkedList(Rect rect, Velocity2D velocities);

        Node getItem(uint16_t index);

        void append(std::shared_ptr<Node> n);

        void remove(uint16_t index);

        void prepend(std::shared_ptr<Node> n);

        void insert(uint16_t index, std::shared_ptr<Node> n);

};

#endif