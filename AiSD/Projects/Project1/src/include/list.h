#pragma once

#include <iostream>
#include "node.h"

class list
{
protected:
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
    void SetSize(int new_len);

    bool isEmpty();

    node* GetRoot();
    void SetRoot(node* new_root);

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
    
    if ((root == nullptr) || (len == 0)) {
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

    if ((root == nullptr) || (len == 0)) {        
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

    if ((root == nullptr) || (len == 0)) {
    
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
    

    node* new_top = root;

    for (int i = 0; i < len - 1; i++)
    {        
        new_top = new_top->GetNext();    
    }
          
    node* target = new_top->GetNext();
    new_top->SetNext(nullptr);
    
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
void list::SetSize(int new_len)
{
    len = new_len;
    return;
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
void list::SetRoot(node* new_root)
{
    new_root->SetNext(root->GetNext());
    root = new_root;
    return;
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
