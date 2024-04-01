#include <iostream>
#include "src/include/list.h"

int main()
{
    char c;
    list *stos = new list();

    do
    {
        std::cin >> c;

        switch (c)
            {
            case '+':
                stos->push(ADD);
                break;
            case '-':
                expression->push(SUBTRACT);
                break;
            case '*':
                expression->push(MULTIPLY);
                break;
            case '/':
                expression->push(DIVIDE);
                break;
            case 'N':
                expression->push(N);
                break;
            case '(':
                expression->push(BRACKETS_START);
                break;
            case ')':
                expression->push(BRACKETS_END);
                break;
            default:
                int prev = 0;
                if (expression->top()->GetToken() == NUMBER)
                {
                    prev = expression->pop()->GetValue();
                }
                expression->push(10*prev + (int) c - (int)('0'));
                break;
            }   
    } while (c != '.');
    

    return 0;
}