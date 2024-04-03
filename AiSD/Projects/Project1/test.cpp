#include <iostream>
#include "src/include/list.h"
#include "src/include/kolejka.h"


list* HandleExpression() 
{
    char c;
    list* expression = new list();

    std::cout << "Enter your expression:\n"; 

    do
    {
        std::cin >> c;

        T token;

        switch (c)
        {
            case '.':
                continue; 
            case '+':
                token = ADD;
                break;
            case '-':
                token = SUBTRACT;
                break;
            case '*':
                token = MULTIPLY;
                break;
            case '/':
                token = DIVIDE;
                break;
            case 'N':
                token = N;
                break;
            case '(':
                token = BRACKETS_START;
                break;
            case ')':
                token = BRACKETS_END;
                break;
            default:
                if (expression->top() == nullptr)
                {
                    expression->push((int) c - (int)('0'));
                }
                else if (expression->top()->GetToken() == NUMBER)
                {
                    expression->top()->SetValue((expression->top()->GetValue() * 10) + (int) c - (int)('0'));
                }
                else
                {
                    expression->push((int) c - (int)('0'));
                }
                continue;
        }

        expression->push(token);
    } while (c != '.');


    list* norm_expression = new list();

    int length = expression->GetSize();
    
    //std::cout<<"The length is " << length <<"\nNormalisation:\n";
    for (int i = 0; i < length; i++)
    {
        //std::cout<<"normalising token number " << i + 1 << "...\n";
        node* moved = expression->pop();        
        //std::cout<<"done\n";
        norm_expression->push(moved);
    }

    //std::cout<<"Normalisation finished!\n";
    return norm_expression;
}

kolejka* HandleKolejka()
{
    char c;
    kolejka* expression = new kolejka();

    std::cout << "Enter your kolejka:\n"; 

    do
    {
        std::cin >> c;

        T token;

        switch (c)
        {
            case '.':
                continue; 
            case '+':
                token = ADD;
                break;
            case '-':
                token = SUBTRACT;
                break;
            case '*':
                token = MULTIPLY;
                break;
            case '/':
                token = DIVIDE;
                break;
            case 'N':
                token = N;
                break;
            case '(':
                token = BRACKETS_START;
                break;
            case ')':
                token = BRACKETS_END;
                break;
            default:
                if (expression->top() == nullptr)
                {
                    expression->push((int) c - (int)('0'));
                }
                else if (expression->top()->GetToken() == NUMBER)
                {
                    expression->top()->SetValue((expression->top()->GetValue() * 10) + (int) c - (int)('0'));
                }
                else
                {
                    expression->push((int) c - (int)('0'));
                }
                continue;
        }

        expression->push(token);
    } while (c != '.');
}

int main()
{
    //list* expression = HandleExpression();

    //std::cout << "you've entered this:\n";
    //expression->show();

    kolejka* kolej = HandleKolejka();

    int choice = 0;

    while (choice != 2);
    {
        if (choice = 1)
        {
            kolej->pop();
        }
        
        kolej->show();
        std::cout << "1 = pop\n2 = exit\nEnter your choice: ";
        std::cin >> choice;
    }
    
}