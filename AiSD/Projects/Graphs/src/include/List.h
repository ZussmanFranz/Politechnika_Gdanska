#pragma once

#include <iostream>
#include "Vertex.h"

class List
{
protected:
    Vertex* root;
    Vertex* last_added;
    int len;
public:
    List();

    void push(Vertex* orig);

    Vertex* pop();

    Vertex* top();

    int GetSize();
    void SetSize(int new_len);

    bool empty();

    Vertex* GetRoot();
    void SetRoot(Vertex* new_root);

    void show();

    Vertex* find(int id);

    bool modify(Vertex* target);

    bool remove(int id);

    ~List();
};

List::List()
{
    root = nullptr;
    len = 0;
}


void List::push(Vertex* orig)
{
    if ((root == nullptr) || (len == 0)) {
        root = new Vertex(*orig);
        last_added = root;
        ++len;
        return;
    }

    Vertex* added = new Vertex(*orig);

    top()->setNext(added);
    last_added = added;
    ++len;

    return;
}
Vertex* List::pop()
{
    len--;    

    if (len == 0)
    {        
        return root;
    }
    

    Vertex* new_top = root;

    for (int i = 0; i < len - 1; i++)
    {        
        new_top = new_top->getNext();
    }
          
    Vertex* target = new_top->getNext();
    new_top->setNext(nullptr);
    last_added = new_top;
    
    return target;
}

Vertex* List::top()
{
    if (root == nullptr)
    {
        return nullptr;
    }

    return last_added;
}

int List::GetSize()
{
    return len;
}
void List::SetSize(int new_len)
{
    len = new_len;
    return;
}

bool List::empty()
{
    if (len == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Vertex* List::GetRoot()
{
    return root;
}
void List::SetRoot(Vertex* new_root)
{
    new_root->setNext(root->getNext());
    root = new_root;
    return;
}

Vertex* List::find(int id)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    
    Vertex* current = root;

    for (int i = 0; i < len - 1; i++)
    {
        if (current->getId() == id)
        {
            return current;
        }
        
        current = current->getNext();
    }

    return nullptr;
}

bool List::modify(Vertex* target)
{
    Vertex* inner_target = find(target->getId());

    if (inner_target == nullptr) {
        return false;
    }

    inner_target->setDegree(target->getDegree());
    inner_target->setSaturation(target->getSaturation());

    return true;
}

bool List::remove(int id)
{
    if (root == nullptr) {
        return false;
    }

    if (root->getId() == id) {
        Vertex* to_delete = root;
        root = root->getNext();

        to_delete->setNext(nullptr);
        delete to_delete;

        len--;
        if (len == 0) {
            last_added = nullptr;
        }

        return true;
    }

    
    Vertex* current = root;
    while (current->getNext() != nullptr && current->getNext()->getId() != id) {
        current = current->getNext();
    }

    if (current->getNext() == nullptr) {
        return false;
    }

    Vertex* to_delete = current->getNext();
    current->setNext(to_delete->getNext());

    to_delete->setNext(nullptr);
    delete to_delete;

    len--;
    if (current->getNext() == nullptr) {
        last_added = current;
    }
    return true;
}


List::~List()
{
    delete root;
    root = nullptr;
    len = 0;
}
