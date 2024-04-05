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
    kolejka* kolej = new kolejka();

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
                if (kolej->last() == nullptr)
                {
                    kolej->push((int) c - (int)('0'));
                }
                else if (kolej->last()->GetToken() == NUMBER)
                {
                    kolej->last()->SetValue((kolej->last()->GetValue() * 10) + (int) c - (int)('0'));
                }
                else
                {
                    kolej->push((int) c - (int)('0'));
                }

                std::cout << "(N)last token is " << kolej->last()->GetToken() << '\n';
                continue;
        }

        kolej->push(token);
        std::cout << "last token is " << kolej->last()->GetToken() << '\n';
    } while (c != '.');

    return kolej;
}

int main()
{
    //list* expression = HandleExpression();

    //std::cout << "you've entered this:\n";
    //expression->show();

    kolejka* kolej = HandleKolejka();

    std::cout << "\nFinished handling kolejka\n";
    char choice = '0';

    do
    {
        if (choice == '1')
        {
            kolej->pop();
        }
        
        kolej->show();

        std::cout << "\n1 = pop\n2 = exit\nEnter your choice: \n";
        std::cin >> choice;
    }while (choice != '2');
    
}