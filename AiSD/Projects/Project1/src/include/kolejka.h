#pragma once

#include "list.h"

class kolejka: public list
{
public:
    node* pop();

    node* top();

    node* last();

    void show();
};

node* kolejka::pop()
{
    len--;

    node* popped = new node(root);
    
    root = root->GetNext();

    return popped;
}

node* kolejka::top()
{
    return root;
}

node* kolejka::last()
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        node* last = root;
    
        //while(top->GetNext() != nullptr)
        for (int i = 0; i < len - 1; i++)
        {
            last = last->GetNext();
        }
        
        return last;
    }
}

void kolejka::show()
{
    //std::cout << "Writing a kolejka with the length of " << len << '\n';

    if (root == nullptr)
    {
        return;
    }
    else
    {
        node* current = root;

        while (current != nullptr)
        {
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
                std::cout << "MIN" << current->GetValue() << ' ';
                break;
            case MAX:
                std::cout << "MAX" << current->GetValue() << ' ';
                break;
            case BRACKETS_START:
                std::cout << "( ";
                break;
            case BRACKETS_END:
                std::cout << ") ";
                break;
            case COMMA:
                std::cout << ", ";
                break;
            default:
                break;
            }

            current = current->GetNext();   
        }

        std::cout << '\n';
        return;
    }
}