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

    // int GetSize();
    // void SetSize(int new_len);

    Vertex* find(int id);

    Vertex* pop();

    void jump_over(Vertex* vL, Vertex* vR);

    void push(Vertex* orig);

    void sort_place(Vertex* start);

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

// int Queue::GetSize()
// {
//     return len;
// }
// void Queue::SetSize(int new_len)
// {
//     len = new_len;
//     return;
// }


Vertex* Queue::find(int id)
{
    if ((id >= mapSize) || (id < 0)) {
        // printf("invalid index!\n");
        return nullptr;
    }

    return map[id];
}


// Vertex* Queue::getNextVertex()
// {

//     if (len == 0) {
//         return nullptr;
//     }

//     if (len == 1) {
//         len = 0;
//         return root;
//     }

//     int max_saturation = -1;
//     int max_degree = -1;
//     int index = -1;

//     Vertex* current = root;


//     while (current != nullptr) {
//         if ((current->getSaturation() > max_saturation) || ((current->getSaturation() == max_saturation) && (current->getDegree() > max_degree))) {
//             max_saturation = current->getSaturation();
//             max_degree = current->getDegree();
//             index = current->getId();
//         }
//         current = current->getNext();
//     }


//     if (index != -1) {
//         Vertex *found = find(index);
//         remove(index);
//         return found;
//     }

//     // printf("\n");
//     return nullptr;
// }

Vertex* Queue::pop()
{
    len--;

    if (len == -1) {
        // printf("there is nothing to pop\n");
        return nullptr;
    }
    else if (len == 0) {
        Vertex* target = root;
        root = nullptr;
        return target;
    }

    Vertex* target = root;

    root = target->getNext();
    root->setPrev(nullptr);
    
    return target;
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

// void Queue::swap(Vertex* vL, Vertex* vR)
// {
//     if (vL == vR) {
//         return;
//     }

//     Vertex* Left = vL->getPrev(); // exists?
//     Vertex* Right = vR->getNext(); // exists?

//     if (vR->getPrev() == vL || vL->getNext() == vR) { //they are neighbors        
//         if (Left != nullptr) { Left->setNext(vR); }
//         if (Right != nullptr) { Right->setPrev(vL); }

//         vR->setPrev(Left);
//         vR->setNext(vL);

//         vL->setPrev(vR);
//         vL->setNext(Right);

//         return;
//     }

//     //they are not neighbors
//     Vertex* middleLeft = vL->getNext(); // surely exists
//     Vertex* middleRight = vR->getPrev(); // surely exists

//     middleLeft->setPrev(vR);
//     middleRight->setNext(vL);

//     if (Left != nullptr) { Left->setNext(vR); }
//     if (Right != nullptr) { Right->setPrev(vL); }

//     vR->setPrev(Left);
//     vR->setNext(middleLeft);

//     vL->setPrev(middleRight);
//     vL->setNext(Right);

//     return;
// }

void Queue::jump_over(Vertex* vL, Vertex* vR)
{
    if (vL == vR) {
        return;
    }

    if (root == vL) {
        root = vR;
    }

    Vertex* vR_Right = vR->getNext();
    Vertex* vR_Left = vR->getPrev();

    if (vR_Left != nullptr) {
        vR_Left->setNext(vR_Right);
    }
    if (vR_Right != nullptr) {
        vR_Right->setPrev(vR_Left);
    }

    Vertex* vL_Left = vL->getPrev();
    if (vL_Left != nullptr) {
        vL_Left->setNext(vR);
    }

    vR->setPrev(vL_Left);
    vR->setNext(vL);

    vL->setPrev(vR);

    return;
}

void Queue::sort_place(Vertex* start)
{
    int start_saturation = start->getSaturation();
    int start_degree = start->getDegree();

    int switch_index = start->getId();

    Vertex* next_candidate = start->getPrev();
    while (next_candidate != nullptr) {
        if (start->lesser_than(next_candidate)) {
            if (switch_index == start->getId()) {
                return;
            }
            jump_over(find(switch_index), start);
            return;
        }
        else {
            switch_index = next_candidate->getId();
        }
        next_candidate = next_candidate->getPrev();
    }

    if (switch_index == start->getId()) {
        return;
    }

    jump_over(find(switch_index), start);
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
    for (unsigned long long i = 0; i < mapSize; i++) {
        map[i] = nullptr;
    }
    delete [] map;
}