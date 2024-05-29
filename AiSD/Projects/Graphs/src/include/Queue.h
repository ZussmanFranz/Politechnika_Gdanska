#pragma once

#include "List.h"
#include "Vertex.h"
#include <cstdio>

class Queue: public List
{
public:
    Queue(unsigned long long size);

    Vertex* pop();

    Vertex* top();

    Vertex* find(int id);

    bool remove(int id);

    Vertex* getNextVertex();

    void push(Vertex* orig);

    void draw();

    ~Queue();
};

Queue::Queue(unsigned long long size)
{   
    map = new Vertex*[size];
    root = nullptr;
    len = 0;
    mapSize = size;
}

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

Vertex* Queue::find(int id)
{
    // // printf("looking for a %d element!\nneed to make %d steps from", id);

    // Vertex* target = root;

    // while (target->getId() != id) {
    //     if (target->getNext() == nullptr) {
    //         return nullptr;
    //     }
    //     target = target->getNext();
    // }

    // return target;
    if ((id >= mapSize) || (id < 0)) {
        printf("invalid index!\n");
        return nullptr;
    }

    if (root->getId() == id) {
        // printf("it is root.");
    }

    return map[id];
}


bool Queue::remove(int id)
{
    // printf("started removing %d\n", id);

    if (root == nullptr) {
        // printf("queue is empty\n");
        return false;
    }

    if (root->getId() == id) {
        if (len == 1) {
            // printf("removing last element!\n");
            len--;
            root = nullptr;
            return true;
        }
        // printf("removing root... ");

        Vertex* target = root;
        Vertex* new_root = target->getNext();
        if (new_root != nullptr) {
            root = new_root;
            root->setPrev(nullptr);
        }
        else {
            // printf("there is no new root\n");
        }
        len--;
        

        // printf("successfully removed root!\n");
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

    // printf("successfully removed element!\n");

    return true;
}

Vertex* Queue::getNextVertex()
{
    // printf("(len: %d)searching for the next element...",len);

    if (len == 0) {
        // printf("there are no elements!\n");
        return nullptr;
    }

    if (len == 1) {
        len = 0;
        // printf("one last element!");
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
        // Vertex* found = new Vertex(*find(index));
        // printf("(len: %d)searching for the %d...\n",len, index);
        Vertex *found = find(index);
        // printf("found %d!\n", index);
        remove(index);
        return found;
    }

    // printf("\n");
    return nullptr;
}

void Queue::push(Vertex* orig)
{
    len++;

    // printf("writing %d to the map...\n", orig->getId());
    map[orig->getId()] = orig;

    if (len == 1) {
        root = orig;
        last_element = root;
        root->setPrev(nullptr);
        root->setNext(nullptr);
        // printf("pushing root at index %d\n", orig->getId());
        return;
    }

    last_element->setNext(orig);
    orig->setPrev(last_element);
    last_element = orig;
    last_element->setNext(nullptr);
    // printf("pushing element at index %d\n", orig->getId());
    return;
}

void Queue::draw()
{
    if (len == 0) {
        return;
    }
    else {
        Vertex* current = root;
        Vertex* next = current->getNext();
        Vertex* prev = current->getPrev();

        if (prev != nullptr) {
            printf("<-");
        }
        else {
            printf(" |");
        }
        printf("R(%d)", root->getId());
        if (next != nullptr) {
            printf("->");
        }
        else {
            printf("| ");
        }

        while (current->getNext() != nullptr) {
            current = current->getNext();
            next = current->getNext();
            prev = current->getPrev();
            if (prev != nullptr) {
                printf("<-");
            }
            else {
                printf(" |");
            }
            printf("(%d)", current->getId());
            if (next != nullptr) {
                printf("->");
            }
            else {
                printf("| ");
            }
        }

        printf("\n");
        return;
    }
}

Queue::~Queue()
{
    delete [] map;
}