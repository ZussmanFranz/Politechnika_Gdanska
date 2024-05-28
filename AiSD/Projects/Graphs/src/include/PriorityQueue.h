#pragma once
#include "Queue.h"

class PriorityQueue: public Queue{
public:
    void push(Vertex* orig);
    bool modify(Vertex* target);
};

void PriorityQueue::push(Vertex* orig)
{
    Vertex* new_vertex = new Vertex(orig);

    if (root == nullptr || *root < *new_vertex) {
        new_vertex->setNext(root);
        root = new_vertex;
        if (len == 0) {
            last_added = root;
        }
    } else {
        Vertex* current = root;
        while (current->getNext() != nullptr && !(*current->getNext() < *new_vertex)) {
            current = current->getNext();
        }
        new_vertex->setNext(current->getNext());
        current->setNext(new_vertex);
        if (new_vertex->getNext() == nullptr) {
            last_added = new_vertex;
        }
    }
    ++len;
}



bool PriorityQueue::modify(Vertex* target)
{
    if (remove(target->getId()) == false)
    {
        return false;
    }

    push(target);

    return false;
}