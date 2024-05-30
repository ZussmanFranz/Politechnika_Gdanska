#pragma once

#include "Vertex.h"
#include <cstdio>

class Queue
{
private:
    Vertex* root;
    Vertex* last_element;
    Vertex** map;
    int len;
    int mapSize;
public:
    Queue(unsigned long long size);

    int GetSize();
    void SetSize(int new_len);

    Vertex* find(int id);

    bool remove(int id);

    Vertex* getNextVertex();

    void push(Vertex* orig);

    // void draw();

    ~Queue();
};

Queue::Queue(unsigned long long size)
{   
    map = new Vertex*[size];
    root = nullptr;
    len = 0;
    mapSize = size;
}

int Queue::GetSize()
{
    return len;
}
void Queue::SetSize(int new_len)
{
    len = new_len;
    return;
}


Vertex* Queue::find(int id)
{
    // return target;
    if ((id >= mapSize) || (id < 0)) {
        printf("invalid index!\n");
        return nullptr;
    }

    return map[id];
}


bool Queue::remove(int id)
{

    if (root == nullptr) {
        return false;
    }

    if (root->getId() == id) {
        if (len == 1) {
            len--;
            root = nullptr;
            return true;
        }

        Vertex* target = root;
        Vertex* new_root = target->getNext();
        if (new_root != nullptr) {
            root = new_root;
            root->setPrev(nullptr);
        }
        len--;
        

        return true;
    }

    
    Vertex* target = map[id];
    Vertex* prev = target->getPrev();
    Vertex* next = target->getNext();
    if (prev != nullptr) {
        prev->setNext(target->getNext());
    }
    if (next != nullptr) {
        next->setPrev(target->getPrev());
    }
    len--;


    return true;
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


    while (current != nullptr) {
        if ((current->getSaturation() > max_saturation) || ((current->getSaturation() == max_saturation) && (current->getDegree() > max_degree))) {
            max_saturation = current->getSaturation();
            max_degree = current->getDegree();
            index = current->getId();
        }
        current = current->getNext();
    }


    if (index != -1) {
        Vertex *found = find(index);
        remove(index);
        return found;
    }

    // printf("\n");
    return nullptr;
}

void Queue::push(Vertex* orig)
{
    len++;

    map[orig->getId()] = orig;

    if (len == 1) {
        root = orig;
        last_element = root;
        root->setPrev(nullptr);
        root->setNext(nullptr);
        return;
    }

    last_element->setNext(orig);
    orig->setPrev(last_element);
    last_element = orig;
    last_element->setNext(nullptr);
    return;
}

// void Queue::draw()
// {
//     if (len == 0) {
//         return;
//     }
//     else {
//         Vertex* current = root;
//         Vertex* next = current->getNext();
//         Vertex* prev = current->getPrev();

//         if (prev != nullptr) {
//             printf("<-");
//         }
//         else {
//             printf(" |");
//         }
//         printf("R(%d)", root->getId());
//         if (next != nullptr) {
//             printf("->");
//         }
//         else {
//             printf("| ");
//         }

//         while (current->getNext() != nullptr) {
//             current = current->getNext();
//             next = current->getNext();
//             prev = current->getPrev();
//             if (prev != nullptr) {
//                 printf("<-");
//             }
//             else {
//                 printf(" |");
//             }
//             printf("(%d)", current->getId());
//             if (next != nullptr) {
//                 printf("->");
//             }
//             else {
//                 printf("| ");
//             }
//         }

//         printf("\n");
//         return;
//     }
// }

Queue::~Queue()
{
    for (unsigned long long i; i < mapSize; i++) {
        map[i] = nullptr;
    }
    delete [] map;
}