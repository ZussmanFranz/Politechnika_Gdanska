#pragma once

#include "list.h"

class kolejka: public list
{
public:
    node* pop();

    node* top();
};

node* kolejka::pop()
{
    --len;

    node* popped = new node(root);
    
    root = root->GetNext();
}

node* kolejka::top()
{
    return root;
}