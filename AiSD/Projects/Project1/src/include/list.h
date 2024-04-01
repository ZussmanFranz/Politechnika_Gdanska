#pragma once

#include <iostream>
#include "node.h"

class list
{
private:
    node* root;
    int len;
    
public:
    list();

    void push(int value);
    void push(T token);
    void push(node* added);

    node* pop();

    node* top();

    int GetSize();

    bool isEmpty();

    void show();

    ~list();
};

list::list()
{
    root = nullptr;
}

void list::push(int value)
{
    len++;
    node* added = new node(value);
    this->top()->SetNext(added);
}
void list::push(T token)
{
    len++;
    node* added = new node(token);
    this->top()->SetNext(added);
}
void list::push(node* added)
{
    len++;
    added->SetNext(nullptr);
    (this->top())->SetNext(added);
}

node* list::pop()
{
    len--;
    node* new_top = root;

    for (int i = 0; i < len; i++)
    {
        new_top = new_top->GetNext();    
    }
    
    node* target = new_top->GetNext();
    new_top->SetNext(nullptr);

    return target;
}

node* list::top()
{
    node* next = root->GetNext();

    while (true)
    {
        if (next->GetNext() == nullptr)
        {
            return next;
        }
        else
        {
            next = next->GetNext();
        }
    }
}

int list::GetSize()
{
    return len;
}

bool list::isEmpty()
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

void list::show()
{
    list* temporary = new list();

    node* current = root;

    while (current->GetNext() != nullptr)
    {
        temporary->push(current);
        current = current->GetNext();
    }
    

    while (!temporary->isEmpty())
    {
        node* current = temporary->pop();

        switch (current->GetToken())
        {
        case NUMBER:
            std::cout << current->GetValue() << ' ';
            break;
        case ADD:
            std::cout << "+ ";
            break;
        case SUBTRACT:
            std::cout << "- ";
            break;
        case MULTIPLY:
            std::cout << "* ";
            break;
        case DIVIDE:
            std::cout << "/ ";
            break;
        case IF:
            std::cout << "IF ";
            break;
        case N:
            std::cout << "N ";
            break;
        case MIN:
            std::cout << "MIN ";
            break;
        case MAX:
            std::cout << "MAX ";
            break;
        case BRACKETS_START:
            std::cout << "( ";
            break;
        case BRACKETS_END:
            std::cout << ") ";
            break;
        default:
            break;
        }   
    }

    delete temporary;
}

list::~list()
{
    delete root;
    root = nullptr;
    len = 0;
}
