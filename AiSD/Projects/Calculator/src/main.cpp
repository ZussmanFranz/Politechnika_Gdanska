#include <iostream>
#include "list.h"
#include "kolejka.h"


#define ERROR -99999

void HandleMinMax(list* expression);
void HandleIf(list* expression);

int get_priority(T token)
{
    if (token == MULTIPLY || token == DIVIDE)
    {
        return 2;
    }
    else if (token == N)
    {
        return 3;
    }
    else if (token == IF || token == MIN || token == MAX)
    {
        return 4;
    }
    else
    {
        return 1;
    }
}

int do_calculation(T token, int* ops, int length)
{
    if (token == MIN)
    {
        //find MIN
        int min = ops[0];

        for (int i = 0; i < length; i++)
        {
            if (ops[i] < min)
            {
                min = ops[i];
            }
        }

        return min;
    }
    else if (token == MAX)
    {
        //find MAX
        int max = ops[0];

        for (int i = 0; i < length; i++)
        {
            if (ops[i] > max)
            {
                max = ops[i];
            }
        }
        
        return max;
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
    if (token == N)
    {
        op = -op;
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
                node* item = stack->pop();
                token = item->GetToken();             
                if(token == BRACKETS_START){break;}
                else if (token == COMMA){continue;}
                else { 
                    if ((token == MIN )|| (token == MAX)){ onp->push(item); }
                    else{ onp->push(token); }
                }
            }
        }
        else if (token == COMMA)
        {
            while (!stack->isEmpty()){
                node* item = stack->pop();
                token = item->GetToken();                
                if(token == COMMA){break;}
                else if(token == BRACKETS_START){stack->push(token); break;}
                else { 
                    if ((token == MIN )|| (token == MAX)){ onp->push(item); }
                    else{ onp->push(token); }
                }
            }
            stack->push(COMMA);
        }
        else
        {
            int priority = get_priority(token);

            while (!stack->isEmpty()){
                T top;
                node* current = nullptr;

                if (stack->top()->GetToken() == MIN || stack->top()->GetToken() == MAX)
                {
                    current = stack->pop();
                    top = current->GetToken();
                }
                else
                {
                    top = stack->pop()->GetToken(); 
                }

                if (top == COMMA){continue;}

                if (((top == BRACKETS_START) || (get_priority(top) < priority)) || ((top == N) && (token == N))) {
                    if ((top == MIN )|| (top == MAX)){ stack->push(current); }
                    else{ stack->push(top); }                   
                    break;
                }
                
                if ((top == MIN )|| (top == MAX)){ onp->push(current); }
                else{ onp->push(top); }                
            }

            if ((token == MIN )|| (token == MAX)){ stack->push(current); }
            else{ stack->push(token); }
        }

        // std::cout << "\n---------\nCurrent state of expression:\n";
        // expression->show();
        // std::cout << "Current state of stack:\n";
        // stack->show();
        // std::cout << "Current state of kolej:\n";
        // onp->show();
        // std::cout << "---------\n\n";
    }
    while (!stack->isEmpty()) {
        node* item = stack->pop();
        T token = item->GetToken();

        if (token == MIN || token == MAX)
        {
            onp->push(item);
        }
        else
        {
            onp->push(token); 
        }       
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
            }
            else if (token == MIN || token == MAX)
            {
                int n_arguments = current->GetValue();
                int* arguments = new int[n_arguments];

                for (int i = 0; i < n_arguments; i++)
                {
                    arguments[i] = stack->pop()->GetValue();
                }
                
                result = do_calculation(token, arguments, n_arguments);
                delete[] arguments;
            }
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

void HandleMinMax(list* expression)
{
    node* added = new node();
    added->SetKey((long)added);

    //std::cout << "encountered a MIN/MAX token and given it a key " << added->GetKey()  << '\n';

    char c;
    std::cin >> c;

    if (c == 'I')
    {
        added->SetToken(MIN);
    }
    else if (c == 'A')
    {
        added->SetToken(MAX);
    }

    expression->push(added);

    std::cin.ignore(1);

    T token;
    int brackets_encountered = -1;
    int brackets_closed = 0;
    int arguments = 1;

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
                brackets_encountered++;
                token = BRACKETS_START;
                break;
            case ')':
                brackets_closed++;

                if ((brackets_closed - brackets_encountered) == 1)
                {
                    expression->push(BRACKETS_END);
                    //std::cout << "looking for a MIN/MAX token with the key " << added->GetKey() << " and trying to set the value " << arguments << '\n';
                    expression->find(added->GetToken(), added->GetKey())->SetValue(arguments); 
                    delete added;
                    return;
                }

                token = BRACKETS_END;
                break;
            case 'I':
                expression->push(IF);
                HandleIf(expression);
                continue;
            case 'M':
                HandleMinMax(expression);
                continue;
            case ',':
                token = COMMA;
                arguments++;
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

    delete added;
    return;
}

void HandleIf(list* expression)
{
    std::cin.ignore(1); //Ignoring F letter

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
                brackets_encountered++;
                token = BRACKETS_START;
                break;
            case ')':
                brackets_closed++;

                if ((brackets_closed - brackets_encountered) == 1)
                {
                    expression->push(BRACKETS_END);
                    return;
                }

                token = BRACKETS_END;
                break;
            case 'I':
                expression->push(IF);
                HandleIf(expression);
                continue;
            case 'M':
                HandleMinMax(expression);
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
            case 'M':
                HandleMinMax(expression);
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
    
    for (int i = 0; i < length; i++)
    {
        node* moved = expression->pop();        
        norm_expression->push(moved);
    }

    delete expression;
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

        //std::cout << "You have entered this: ";
        //expression->show();

        // Converting it into ONP version
        kolejka* onp = ONPConv(expression);
        
        // ONP version:
        onp->show();

        int result = ONPCalc(onp);
        if (result == ERROR)
        {
            std::cout << '\n';
            continue;
        }
        
        std::cout << result <<"\n\n";

        delete expression;
        delete onp;
    }

    return 0;
}