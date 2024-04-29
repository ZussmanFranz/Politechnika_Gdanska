#include "include/board.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

board::board(int size, std::istream& input_stream)
: size(size)
{
    fields = new field*[size];

    for (int i = 0; i < size; i++)
    {
        fields[i] = new field[size];
        for (int j = 0; j < size; j++)
        {
            fields[i][j].color = ' ';
            fields[i][j].position.y = i;       
            fields[i][j].position.x = j;
        }
    }

    pawns_b = pawns_r = 0;

    return;
}

void board::HandleBoard(std::istream& input_stream)
{
    int nline_n = size * 2 + 1;

    bool downstairs = false;
    int x, y, k;
    x = 0;
    y = 0;
    k = 0;

    char c;
    while (input_stream >> c) {
        if (c == '\n') {
            nline_n--;
            //td::cout << nline_n << "\n";

            if (nline_n == 0) {
                break;
            }

            continue;
        }

        if ((c == '-') || (c == '>')) {
            continue;
        }

        if (c == '<') 
        {
            input_stream.ignore(1);
            input_stream >> c;
            input_stream.ignore(1); //changed!

            if (y == size) {
                //std::cout << "switch!\n";
                downstairs = true;
                k = 1;
                y = size - 1;
                x = k;
            }

            //std::cout << "y = " << y << " x = " << x << '\n';
            fields[y][x].color = c;
            if (c == 'b') {
                pawns_b++;
            }
            else if (c == 'r') {
                pawns_r++;
            }

            if ((!downstairs) && (y == 0)) {
                ++k;
                y = k;
                x = 0;
            }
            else if (x == size - 1) {
                ++k;
                y = size - 1;
                x = k;
            }
            else {
                y--;
                x++;
            }
        }
    }
    return;
}

void board::PrintBoard()
{
    printf("\n  ");
    for (int r = 0; r < size; r++) {
        printf("R ");
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("B ");
        for (int j = 0; j < size; j++) {
            printf("%c ", fields[i][j].color);
        }
        printf("B\n");
    }

    return;
}

void board::HandleTask(std::istream& input_stream, char start_c)
{
    if ((start_c == EOF) || (start_c == '\n')) {
        return;
    }

    char task_buffer[100];

    input_stream.getline(task_buffer, 100);

    //printf("task: %s\n", task_buffer);

    if (std::strcmp(task_buffer,"OARD_SIZE") == 0) {
        current_task = SIZE;
    }
    else if (std::strcmp(task_buffer,"AWNS_NUMBER") == 0) {
        current_task = PAWNS;
    }
    else if (std::strcmp(task_buffer,"S_BOARD_CORRECT") == 0) {
        current_task = IS_CORRECT;
    }
    else if (std::strcmp(task_buffer,"S_GAME_OVER") == 0) {
        current_task = IS_OVER;
    }
    else if (std::strcmp(task_buffer,"S_BOARD_POSSIBLE") == 0) {
        current_task = IS_POSSIBLE;
    }
    else if (std::strcmp(task_buffer,"AN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0) {
        current_task = CAN_RED_IN_1_NAIVE;
    }
    else if (std::strcmp(task_buffer,"AN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0) {
        current_task = CAN_BLUE_IN_1_NAIVE;
    }
    else if (std::strcmp(task_buffer,"AN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0) {
        current_task = CAN_RED_IN_2_NAIVE;
    }
    else if (std::strcmp(task_buffer,"AN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0) {
        current_task = CAN_BLUE_IN_2_NAIVE;
    }
    else if (std::strcmp(task_buffer,"AN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") == 0) {
        current_task = CAN_RED_IN_1_PERFECT;
    }
    else if (std::strcmp(task_buffer,"AN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") == 0) {
        current_task = CAN_BLUE_IN_1_PERFECT;
    }
    else if (std::strcmp(task_buffer,"AN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") == 0) {
        current_task = CAN_RED_IN_2_PERFECT;
    }
    else if (std::strcmp(task_buffer,"AN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") == 0) {
        current_task = CAN_BLUE_IN_2_PERFECT;
    }
    else {
        current_task = ERROR;
    }

    return;
}

void board::PrintTask()
{
    switch (current_task) {
        case SIZE:
            std::cout << "SIZE\n";
            break;
        case PAWNS:
            std::cout << "PAWNS\n";
            break;
        case IS_CORRECT:
            std::cout << "IS_CORRECT\n";
            break;
        case IS_OVER:
            std::cout << "IS_OVER\n";
            break;
        case IS_POSSIBLE:
            std::cout << "IS_POSSIBLE\n";
            break;
        case CAN_RED_IN_1_NAIVE:
            std::cout << "CAN_RED_IN_1_NAIVE\n";
            break;
        case CAN_RED_IN_2_NAIVE:
            std::cout << "CAN_RED_IN_2_NAIVE\n";
            break;
        case CAN_BLUE_IN_1_NAIVE:
            std::cout << "CAN_BLUE_IN_1_NAIVE\n";
            break;
        case CAN_BLUE_IN_2_NAIVE:
            std::cout << "CAN_BLUE_IN_2_NAIVE\n";
            break;
        case CAN_RED_IN_1_PERFECT:
            std::cout << "CAN_RED_IN_1_PERFECT\n";
            break;
        case CAN_RED_IN_2_PERFECT:
            std::cout << "CAN_RED_IN_2_PERFECT\n";
            break;
        case CAN_BLUE_IN_1_PERFECT:
            std::cout << "CAN_BLUE_IN_1_PERFECT\n";
            break;
        case CAN_BLUE_IN_2_PERFECT:
            std::cout << "CAN_BLUE_IN_2_PERFECT\n";
            break;
        case ERROR:
            std::cout << "ERROR\n";
            break;
    }

    return;
}

int board::SolveTask()
{
    switch (current_task) {
        case SIZE:
            std::cout << size << "\n\n";
            return 0;
            break;
        case PAWNS:
            std::cout << pawns_r + pawns_b << "\n\n";
            return 0;
            break;
        case IS_CORRECT:
            if ((pawns_r - 1 == pawns_b) || (pawns_r == pawns_b)) {
                std::cout << "YES\n\n";
            }
            else {
                std::cout << "NO\n\n";
            }
            return 0;
            break;
        case IS_OVER:
            std::cout << "IS_OVER\n";
            return 0;
            break;
        case IS_POSSIBLE:
            std::cout << "IS_POSSIBLE\n";
            return 0;
            break;
        case CAN_RED_IN_1_NAIVE:
            std::cout << "CAN_RED_IN_1_NAIVE\n";
            return 0;
            break;
        case CAN_RED_IN_2_NAIVE:
            std::cout << "CAN_RED_IN_2_NAIVE\n";
            return 0;
            break;
        case CAN_BLUE_IN_1_NAIVE:
            std::cout << "CAN_BLUE_IN_1_NAIVE\n";
            return 0;
            break;
        case CAN_BLUE_IN_2_NAIVE:
            std::cout << "CAN_BLUE_IN_2_NAIVE\n";
            return 0;
            break;
        case CAN_RED_IN_1_PERFECT:
            std::cout << "CAN_RED_IN_1_PERFECT\n";
            return 0;
            break;
        case CAN_RED_IN_2_PERFECT:
            std::cout << "CAN_RED_IN_2_PERFECT\n";
            return 0;
            break;
        case CAN_BLUE_IN_1_PERFECT:
            std::cout << "CAN_BLUE_IN_1_PERFECT\n";
            return 0;
            break;
        case CAN_BLUE_IN_2_PERFECT:
            std::cout << "CAN_BLUE_IN_2_PERFECT\n";
            return 0;
            break;
        case ERROR:
            std::cout << "ERROR\n";
            return 1;
            break;
    }

    return 1;
}

// void board::Convert()
// {
//     for (int i = 0; i < string_representation.size(); i++) 
//     {

//     }
// }

field* board::GetField(int y, int x)
{
    if (y > size || x > size || y < 0 || x < 0)
    {
        return &(fields[y][x]);
    }
    else{
        return nullptr;
    }
}



board::~board()
{
    for (int i = 0; i < size; i++) 
    {
        delete [] fields[i];
    }
    delete [] fields;
}