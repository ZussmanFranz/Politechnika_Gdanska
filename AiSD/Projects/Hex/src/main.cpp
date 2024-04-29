#include <cstdio>
#include <iostream>
#include "include/board.h"

int GetSection(std::istream& input_stream, char start_c)
{
    int size = 0;

    if (start_c == ' ') {
        int size = 1;
    }
    else if (start_c == EOF){
        return 1;
    }
    

    //get size by spaces
    while (start_c == ' ') {
        size++;
        input_stream >> start_c;
    }
    size = (size + 2) / 3;

    //std::cout << size << '\n';

    board* field = new board(size, input_stream);

    field->HandleBoard(input_stream);
    //field->PrintBoard();

    field->HandleTask(input_stream, start_c);
    //field->PrintTask();


    if (field->SolveTask() == 1)
    {
        return 1;
    }

    return 0;
}

board* HandleBoard(std::istream& input_stream, char start_c)
{
    int size = 0;

    
    if (start_c == EOF){
        return nullptr;
    }
    

    //get size by spaces
    while (start_c == ' ') {
        size++;
        input_stream >> start_c;
    }
    size = (size + 2) / 3;

    //std::cout << size << '\n';

    board* field = new board(size, input_stream);

    field->HandleBoard(input_stream);

    return field;
}

int HandleTask(std::istream& input_stream, char start_c, board* field)
{
    if (field == nullptr) {
        return 1;
    }

    field->HandleTask(input_stream, start_c);
    //field->PrintTask();


    if (field->SolveTask() == 1)
    {
        return 1;
    }

    return 0;
}

int main()
{
    std::cin >> std::noskipws; // Disable skipping whitespace

    char c;
    std::cin >> c;

    board* field = nullptr;

    while (c != EOF) {
        //std::cout << "starting c:" << c << ".\n";
        if (c == ' ') {
            //std::cout << "board!\n";
            field = HandleBoard(std::cin, c);
            //field->PrintBoard();
        }
        else if ((c > 64) && (c < 91)) {
            //std::cout << "task!\n";
            if (HandleTask(std::cin, c, field)) {
                return 1;
            }
            //field->PrintTask(); 
        }

        std::cin >> c;
        if (c == '\n') {
            //std::cout << "ups!\n";
            std::cin >> c;
            if ((c == '\n') || (c == EOF)) {
                break;
            }
        }
    }

    std::cin >> std::skipws; // Re-enable skipping whitespace

    delete field;

    return 0;
}