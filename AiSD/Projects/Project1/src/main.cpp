#include <iostream>
#include "list.h"
#include "kolejka.h"

#define ERROR -99999

int get_priority(T token)
{
    if (token == MULTIPLY || token == DIVIDE)
    {
        return 2;
    }
    else if (token == N || token == IF || token == MIN || token == MAX)
    {
        return 3;
    }
    else
    {
        return 1;
    }
}

int do_calculation(T token, int* ops)
{
    if (token == MIN)
    {
        //find MIN
    }
    else if (token == MAX)
    {
        //find MAX
    }
    
    return ERROR;
}

int do_calculation(T token, int op1, int op2, int op3)
{
    if (token == IF)
    {
        if (op1 > 0)
        {
            return op2;
        }
        else{
            return op3;
        }
    }
    return ERROR;
}

int do_calculation(T token, int op1, int op2)
{
    switch (token)
    {
    case ADD:
        return (op1 + op2);
        break;
    case SUBTRACT:
        return (op1 - op2);
        break;
    case MULTIPLY:
        return (op1 * op2);
        break;
    case DIVIDE:
        if (op2 != 0)
        {
            return (op1 / op2);
        }
        else
        {
            return ERROR;
        }
        break;
    default:
        return ERROR;
        break;
    }
}

int do_calculation(T token, int op)
{
    //std::cout << "encountered the N token! previous value = " << op << ", the new value = ";
    if (token == N)
    {
        op = -op;
        //std::cout << op << '\n';
        return op;
    }
    return ERROR;
}

kolejka* ONPConv(list* expression){
    list *stack = new list();
    kolejka *onp = new kolejka();
    while (!expression->isEmpty()){                
        node* current = expression->pop();
        T token = current->GetToken();        

        if (token == NUMBER){
            onp->push(current->GetValue());            
        }
        else if (token == BRACKETS_START){
            stack->push(token);            
        }
        else if (token == BRACKETS_END){
            while (!stack->isEmpty()){
                token = stack->pop()->GetToken();                
                if(token == BRACKETS_START){break;}
                else { onp->push(token); }
            }
        }
        else if (token == COMMA)
        {
            continue;
        }
        else
        {
            int priority = get_priority(token);

            while (!stack->isEmpty()){
                T top = stack->pop()->GetToken();                
                if ((top == BRACKETS_START) || (get_priority(top) < priority)) {
                    stack->push(top);                    
                    break;
                }
                onp->push(top);                
            }
            stack->push(token);
        }      
    }
    while (!stack->isEmpty()) {
        T item = (stack->pop())->GetToken();
        onp->push(item);        
    }
    return onp;
}

int ONPCalc(kolejka* onp) {
    /*Function returns the result of ONP
    expression #evaluation. Example : 3 4 * 2
    +’’’ = returned result*/

    list* stack = new list();
    while (!onp->isEmpty()){
        node* current = onp->pop();
        T token = current->GetToken();
        if (token == NUMBER)
        {
            stack->push(current->GetValue());
        }
        else{
            switch (token)
            {
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
            default:
                break;
            }

            int result;
            stack->show();

            if (token == N)
            {
                int op = stack->pop()->GetValue();
                result = do_calculation(token, op);
            }
            else if (token == IF)
            {
                int op3 = stack->pop()->GetValue();
                int op2 = stack->pop()->GetValue();
                int op1 = stack->pop()->GetValue();
                result = do_calculation(token, op1, op2, op3);
            } // add else if for MIN/MAX, creating an array of op's with malloc, length is a value
            else
            {
                int op2 = stack->pop()->GetValue();
                int op1 = stack->pop()->GetValue();
                result = do_calculation(token,op1,op2); // add options
                if (result == ERROR)
                {
                    std::cout << "ERROR\n";
                    return result;
                }
            }

            stack->push(result);
        }
    }

    int result = stack->pop()->GetValue();

    return result;
}

void HandleIf(list* expression)
{
    char c;
    T token;
    int brackets_encountered = -1;
    int brackets_closed = 0;

    do
    {
        std::cin >> c;

        switch (c)
        {
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
                if (brackets_encountered == -1)
                { 
                    brackets_encountered++;
                    continue;
                }
                else if (brackets_encountered == brackets_closed)
                {
                    brackets_encountered++;
                    token = BRACKETS_START;
                }
                break;
            case ')':
                brackets_closed++;

                if (brackets_encountered != brackets_closed)
                {
                    return;
                }

                token = BRACKETS_END;
                break;
            case 'I':
                expression->push(IF);
                HandleIf(expression);
                continue;
            case 'F':
                continue;
            case ',':
                token = COMMA;
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
    } while (true);

    return;
}

list* HandleExpression() 
{
    char c;
    T token;

    list* expression = new list();

    // Handling input:
    do
    {
        std::cin >> c;

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
            case 'I':
                expression->push(IF);
                HandleIf(expression);
                continue;
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


int main()
{
    int n_expr;
    std::cin >> n_expr;

    for (int i = 0; i < n_expr; i++)
    {
        // Handling expression number i
        list* expression = HandleExpression();

        // Converting it into ONP version
        kolejka* onp = ONPConv(expression);
        
        // ONP version:
        onp->show();

        int result = ONPCalc(onp);
        if (result == ERROR)
        {
            continue;
        }
        
        std::cout << result <<'\n';
    }
}