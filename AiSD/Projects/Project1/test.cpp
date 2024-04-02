#include <iostream>
#include "src/include/list.h"

int main()
{
    char c;
    list *stos = new list();

    std::cout << "Enter your expression:\n"; 

    do
    {
        std::cin >> c;

        T token;

        //std::cout << "switching!\n";
        switch (c)
        {
            case '.':
                //std::cout << "encountered a dot!\n"; 
                continue; 
            case '+':
                //std::cout << "added + !\n";  
                token = ADD;
                break;
            case '-':
                //std::cout << "added - !\n";
                token = SUBTRACT;
                break;
            case '*':
                //std::cout << "added * !\n";
                token = MULTIPLY;
                break;
            case '/':
                //std::cout << "added / !\n";
                token = DIVIDE;
                break;
            case 'N':
                //std::cout << "added N !\n";
                token = N;
                break;
            case '(':
                //std::cout << "added ( !\n";
                token = BRACKETS_START;
                break;
            case ')':
                //std::cout << "added ) !\n";
                token = BRACKETS_END;
                break;
            default:
                
                if (stos->top() == nullptr)
                {
                    //std::cout << "creating a root from a number " << (int) c - (int)('0') << '\n';
                    stos->push((int) c - (int)('0'));
                }
                else if (stos->top()->GetToken() == NUMBER)
                {
                    //std::cout << "overwriting a node with token " << stos->top()->GetToken() << '\n';
                    stos->top()->SetValue((stos->top()->GetValue() * 10) + (int) c - (int)('0'));
                }
                else
                {
                    //std::cout << "adding a number...";
                    stos->push((int) c - (int)('0'));
                    //std::cout << (int) c - (int)('0') << ", top value is " << stos->top()->GetValue();
                }
                
                //std::cout << " ...added a number " << stos->top()->GetValue() << " !\n";
                //std::cout << "--------------\nTop token is " << stos->top()->GetToken() << ", length is " << stos->GetSize() << "\n--------------\n";
                continue;
        }

        //std::cout << "pushing a token " << token << '\n';
        stos->push(token);
          
        //std::cout << "--------------\nTop token is " << stos->top()->GetToken() << ", length is " << stos->GetSize() << "\n--------------\n";
    } while (c != '.');
    
    //std::cout << "finished scanning!\n";

    std::cout << "You have entered this expression:\n";
    stos->show();

    return 0;
}