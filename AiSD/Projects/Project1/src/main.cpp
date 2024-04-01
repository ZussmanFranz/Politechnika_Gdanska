#include <iostream>
#include "list.h"

int get_priority(T token)
{
    int priority;

    // if (token == BRACKETS_START)
    // {
    //     priority = 0;
    // }
    if (token == MULTIPLY || token == DIVIDE)
    {
        priority = 2;
    }
    else
    {
        priority = 1;
    }

    return priority;
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
    
    return 0;
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
    return 0;
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
        return (op1 / op2);
        break;
    default:
        break;
    }
}

int do_calculation(T token, int op)
{
    if (token == N)
    {
        op = -op;
    }
    return op;
}

list* ONPConv(list* expression){
    list *stack = new list();
    list *onp = new list();
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

int ONPCalc(list* onp) {
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
            int op2 = stack->pop()->GetValue();
            int op1 = stack->pop()->GetValue();
            int result = do_calculation(token,op1,op2); // add options
            stack->push(result);
        }
    }

    int result = stack->pop()->GetValue();

    return result;
}

list* HandleExpression() //replace stos with expression and add switch instead of if...else
{
    list* expression = new list();
    //char op[10];
    //int digit = 0;

    std::cout << "Enter a string: ";

    char c;
    //int target = 0;
    bool MIN_MAX_encountered = false;

    std::cout << "Started scanning: \n";

    do
    {
        std::cin >> c;

        std::cout << '\n' << c;

        if (!MIN_MAX_encountered)
        {
            switch (c)
            {
            case '+':
                expression->push(ADD);
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
        }
        else // finish implementation
        {
            switch (c)
            {
            case 'I':
                expression->push(MIN);
                break;
            case 'N':
                continue;
                break; //nothing
            case 'A':
                expression->push(MAX);
                break;
            case 'X':
                continue;
                break; //nothing
            case '(':
                continue;
                break; //nothing
            case ')':
                MIN_MAX_encountered = false;
                break;
            case ',':
                continue;
                break; // nothing
            default:
                expression->push((int)c - (int)('0'));
                break;
            }
        }
    }
    while (c != '.');
    
    std::cout << "finished scanning\n";

    list* normalised_expression = new list();

    for (int i = 0; i < expression->GetSize(); i++)
    {
        normalised_expression->push(expression->pop());
    }

    normalised_expression->show();
    
    return normalised_expression;

    // char c;
    // while(std::cin.get(c) && c != '\n') { 
    //     if (isdigit(c)) {
    //         digit = digit * 10 + c - '0';
    //     } else if (c == '(') {
    //         expression.push(BRACKETS_START);
    //     } else if (c == ')') {
    //         while (!stos.empty()) {
    //             char top = stos.top();
    //             stos.pop_back();
    //             if (top == '(')
    //                 break;
    //             else
    //                 std::cout << top;
    //         }
    //     } else if (c == ' '){
    //         if (digit != 0) {
    //             std::cout << digit << " ";
    //             digit = 0;
    //         }
    //         if (op[1] == 'I'){
    //             std::cout << "MIN ";
    //         } else if (op[1] == 'A'){
    //             std::cout << "MAX ";
    //         } else if (op[0] == 'N'){
    //             std::cout << "N ";
    //         } else if (op[0] == 'I'){
    //             std::cout << "IF ";
    //         } else std::cout << op[0] << " ";
    //         op[0] = 0;
    //         op[1] = 0;
    //         op[2] = 0;
    //     } else {
    //         if (op[0] == 0) {
    //             op[0] = c;
    //         } else if (op[1] == 0) {
    //             op[1] = c;
    //         } else {
    //             op[2] = c;
    //         }
    //         // int priority = get_priority(c);
    //         // while (!stos.empty()) {
    //         //     char top = stos.top();
    //         //     if (top == '(' || get_priority(top) < priority)
    //         //         break;
    //         //     stos.pop_back();
    //         //     cout << top;
    //         // }
    //         // stos.push_back(c);
    //     }
    // }

    // while (!stos.empty()) {
    //     std::cout << stos.top();
    //     stos.pop_back();
    // }

    // std::cout << '\n';
}


int main()
{
    int n_expr;
    std::cin >> n_expr;

    for (int i = 0; i < n_expr; i++)
    {
        //char scope[3];

        list* expression = HandleExpression();
    }
}