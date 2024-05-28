#pragma once

#include "List.h"
#include "Vertex.h"

class Queue: public List
{
public:
    Vertex* pop();

    Vertex* top();

    Vertex* last();

    Vertex* getNextVertex();

    void push(Vertex* orig);
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

Vertex* Queue::last()
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        return last_added;
    }
}
