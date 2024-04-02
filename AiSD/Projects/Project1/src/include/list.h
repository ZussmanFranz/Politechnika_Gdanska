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
    void push(node* orig);

    node* pop();

    node* top();

    int GetSize();

    bool isEmpty();

    node* GetRoot();

    void show();

    ~list();
};

list::list()
{
    root = nullptr;
    len = 0;
}

void list::push(int value)
{
    node* added = new node(value);
    
    if (root == nullptr) {
        root = added;
        ++len;
    
        return;
    }

    top()->SetNext(added);
    ++len;

    return;
}
void list::push(T token)
{
    node* added = new node(token);

    if (root == nullptr) {
    
        root = added;
        ++len;
    
        return;
    }

    top()->SetNext(added);
    ++len;

    return;
}
void list::push(node* orig)
{
    node* added = new node(orig);

    if (root == nullptr) {
    
        root = added;
        ++len;
    
        return;
    }

    top()->SetNext(added);
    ++len;

    return;
}

node* list::pop()
{
    len--;

    if (len == 0)
    {
        return root;
    }
    

    //std::cout << "new length is " << len <<",\n";
    node* new_top = root;

    for (int i = 0; i < len - 1; i++)
    {
        //std::cout << "new top token is " << new_top->GetToken() << " and i = " << i << '\n';
        new_top = new_top->GetNext();    
    }
    
    //std::cout << "new top token is " << new_top->GetToken() << '\n';

    node* target = new node(new_top->GetNext());
    new_top->SetNext(nullptr);

    //std::cout << "pop is finished. Top token is " << top()->GetToken() << '\n';
    return target;
}

node* list::top()
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        node* top = root;
    
        //while(top->GetNext() != nullptr)
        for (int i = 0; i < len - 1; i++)
        {
            top = top->GetNext();
        }
        
        return top;
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

node* list::GetRoot()
{
    return root;
}

void list::show()
{
    int starting_length = len;

    while (len > 0)
    {
        node* current = top();

        switch (current->GetToken())
        {
        case NUMBER:
            std::cout << current->GetValue() << " ";
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

        len--;  
    }

    len = starting_length;
    
    std::cout << '\n';
}

list::~list()
{
    delete root;
    root = nullptr;
    len = 0;
}
