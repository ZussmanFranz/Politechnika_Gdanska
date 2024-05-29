#pragma once

#include "List.h"
#include "Vertex.h"
#include <cstddef>
#include <cstdio>

class Queue: public List
{
public:
    Vertex* pop();

    Vertex* top();

    Vertex* at(int index);

    Vertex* find(int id);

    Vertex* getNextVertex();

    void push(Vertex* orig);

    // ~Queue();
};

Vertex* Queue::pop()
{
    len--;

    // node* popped = new node(root);
    Vertex* popped = root;//added
    
    root = popped->getNext();//changed
    popped->setNext(nullptr);//added

    return popped;
}

Vertex* Queue::top()
{
    return root;
}

Vertex* Queue::at(int index)
{
    printf("taking element at %d, steps to make: %d\n", index, (len - index) - 1);
    if (index > len - 1) {return nullptr;}

    Vertex* target = root;

    for (int i = 0; i < (len - index) - 1; i++) 
    {
        target = target->getNext();
    }

    return target;
}

Vertex* Queue::find(int id)
{
    // printf("looking for a %d element!\nneed to make %d steps from", id);

    Vertex* target = root;

    while (target->getId() != id) {
        if (target->getNext() == nullptr) {
            return nullptr;
        }
        target = target->getNext();
    }

    return target;
}

Vertex* Queue::getNextVertex()
{
    if (len == 0) {
        return nullptr;
    }

    if (len == 1) {
        len = 0;
        return root;
    }

    int max_saturation = -1;
    int max_degree = -1;
    int index = -1;

    Vertex* current = root;

    // printf("started searching!\n");

    while (current != nullptr) {
        if ((current->getSaturation() > max_saturation) || ((current->getSaturation() == max_saturation) && (current->getDegree() > max_degree))) {
            max_saturation = current->getSaturation();
            max_degree = current->getDegree();
            index = current->getId();
        }
        current = current->getNext();
        // printf("next!\n");
    }

    // printf("search was...");

    if (index != -1) {
        // printf("successful!\n");
        Vertex* found = new Vertex(*find(index));
        remove(index);
        return found;
    }

    // printf("bad.\n");
    return nullptr;
}

void Queue::push(Vertex* orig)
{
    len++;

    if (len == 1) {
        root = orig;
        last_element = root;
        return;
    }

    last_element->setNext(orig);
    last_element = orig;
    return;
}

// Queue::~Queue()
// {
//     len = 0;

//     if (root != nullptr) {
//         delete root; 
//     }
// }