#include "include/board.h"
#include <cstring>
#include <iostream>

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
    won_b = won_r = false;

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

            if (y == size) {
                downstairs = true;
                k = 1;
                y = size - 1;
                x = k;
            }

            fields[y][x].color = c;
            fields[y][x].position = {y, x};
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

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fields[i][j].SetNeighbours(fields, size);
        }
    }

    return;
}

void board::PrintBoard()
{
    printf("\n  ");
    for (int r = 0; r < size; r++) {
        printf("B ");
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("R ");
        for (int j = 0; j < size; j++) {
            printf("%c ", fields[i][j].color);
        }
        printf("R\n");
    }
    
    printf("  ");
    for (int r = 0; r < size; r++) {
        printf("B ");
    }
    printf("\n");

    return;
}

void board::PrintBoard(char search_color)
{
    printf("\n  ");
    for (int r = 0; r < size; r++) {
        printf("B ");
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("R ");
        for (int j = 0; j < size; j++) {

            if ((fields[i][j].color != search_color)) {
                printf("  ");
            }
            else {
                printf("%d ", fields[i][j].neighbours_count);
            }
        }
        printf("R\n");
    }
    
    printf("  ");
    for (int r = 0; r < size; r++) {
        printf("B ");
    }
    printf("\n");

    return;
}

void board::HandleTask(std::istream& input_stream, char start_c)
{
    if ((start_c == EOF) || (start_c == '\n')) {
        return;
    }

    char task_buffer[100];

    input_stream.getline(task_buffer, 100);

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
            if (IsCorrect()) {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }
            Uncheck();
            return 0;
            break;
        case IS_OVER:
            if (!IsCorrect()) {
                printf("NO\n");
                return 0;
                break;
            }

            if (IsOver()) {
                printf("YES");
                if (won_r) {
                    printf(" RED\n");
                }
                else if (won_b) {
                    printf(" BLUE\n");
                }
            }
            else {
                printf("NO\n");
            }

            //Uncheck();
            return 0;
            break;
        case IS_POSSIBLE:
            if (!IsCorrect()) {
                printf("NO\n");
                return 0;
                break;
            }

            if (IsOver()) {
                //Uncheck();

                if (IsPossible()) {
                    printf("YES\n");
                }
                else {
                    printf("NO\n");
                }
            }
            else {
                printf("YES\n");
            }

            return 0;
            break;
        case CAN_RED_IN_1_NAIVE:
            // printf("CAN_RED_IN_1_NAIVE");
            // PrintBoard();
            
            if (!IsCorrect()) {
                printf("NO\n");
                // printf("(incorrect)\n");
                return 0;
                break;
            }
            else if (IsOver()) {
                printf("NO\n");
                // printf("(is over)\n");
                return 0;
                break;
            }
            
            if (Naive('r', 1))
            {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }

            // PrintBoard();
            // PrintBoard('r');
            // PrintBoard('b');
            RefreshConnections();
            // PrintBoard('r');
            return 0;
            break;
        case CAN_RED_IN_2_NAIVE:
            // printf("CAN_RED_IN_2_NAIVE");
            // PrintBoard();
            
            if (!IsCorrect()) {
                printf("NO\n");
                // printf("(incorrect)\n");
                return 0;
                break;
            }
            else if (IsOver()) {
                printf("NO\n");
                // printf("(is over)\n");
                return 0;
                break;
            }

            if (!TwoTurnsPossible('r')) {
                printf("NO\n");
                // printf("(two turns are not possible)\n");
                return 0;
                break;
            }

            if (Naive('r', 2))
            {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }

            // PrintBoard();
            // PrintBoard('r');
            // PrintBoard('b');
            RefreshConnections();
            // PrintBoard('r');
            return 0;
            break;
        case CAN_BLUE_IN_1_NAIVE:
            // printf("CAN_BLUE_IN_1_NAIVE");
            // PrintBoard();
            
            if (!IsCorrect()) {
                printf("NO\n");
                // printf("(incorrect)\n");
                return 0;
                break;
            }
            else if (IsOver()) {
                printf("NO\n");
                // printf("(is over)\n");
                return 0;
                break;
            }

            if (Naive('b', 1))
            {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }

            // PrintBoard();
            // PrintBoard('r');
            // PrintBoard('b');
            RefreshConnections();
            // PrintBoard('r');
            return 0;
            break;
        case CAN_BLUE_IN_2_NAIVE:
            // printf("CAN_BLUE_IN_2_NAIVE");
            // PrintBoard();

            if (!IsCorrect()) {
                printf("NO\n");
                // printf("(incorrect)\n");
                return 0;
                break;
            }
            else if (IsOver()) {
                printf("NO\n");
                // printf("(is over)\n");
                return 0;
                break;
            }

            if (!TwoTurnsPossible('b')) {
                printf("NO\n");
                // printf("(two turns are not possible)\n");
                return 0;
                break;
            }

            if (Naive('b', 2))
            {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }

            // PrintBoard();
            // PrintBoard('r');
            // PrintBoard('b');
            RefreshConnections();
            // PrintBoard('r');
            return 0;
            break;
        case CAN_RED_IN_1_PERFECT:
            if (!IsCorrect()) {
                printf("NO\n");
                return 0;
                break;
            }
            else if (IsOver()) {
                printf("NO\n");
                return 0;
                break;
            }

            if (Naive('r', 1)) // CHANGE TO PERFECT!!
            {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }

            return 0;
            break;
        case CAN_RED_IN_2_PERFECT:
            if (!IsCorrect()) {
                printf("NO\n");
                return 0;
                break;
            }
            else if (IsOver()) {
                printf("NO\n");
                return 0;
                break;
            }

            if (Naive('r', 2)) // CHANGE TO PERFECT!!
            {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }

            return 0;
            break;
        case CAN_BLUE_IN_1_PERFECT:
            if (!IsCorrect()) {
                printf("NO\n");
                return 0;
                break;
            }
            else if (IsOver()) {
                printf("NO\n");
                return 0;
                break;
            }

            if (Naive('b', 1)) // CHANGE TO PERFECT!!
            {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }

            return 0;
            break;
        case CAN_BLUE_IN_2_PERFECT:
            if (!IsCorrect()) {
                printf("NO\n");
                return 0;
                break;
            }
            else if (IsOver()) {
                printf("NO\n");
                return 0;
                break;
            }

            if (Naive('b', 2)) // CHANGE TO PERFECT!!
            {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }

            return 0;
            break;
        // case ERROR:
        //     std::cout << "ERROR\n";
        //     return 1;
        //     break;
        default:
            return 1;
            break;
    }

    return 1;
}

bool board::IsOver()
{
    // printf("checking if the game is over..");
    // PrintBoard();

    bool bottom_b, top_b, left_r, right_r;
    bottom_b = top_b = left_r = right_r = false;

    for (int i = 0; i < size; i++) {
        if (fields[0][i].color == 'b') {
            top_b = true;
        }
        if (fields[size - 1][i].color == 'b') {
            bottom_b = true;
        }
        if (fields[i][0].color == 'r') {
            left_r = true;
        }
        if (fields[i][size - 1].color == 'r') {
            right_r = true;
        }
    }

    if ((top_b == true) && (bottom_b == true)) {
        // printf("starting to check player blue\n");
        if (CheckPlayer('b')) 
        { 
            Uncheck();
            // PrintBoard();
            // PrintBoard('r');
            // PrintBoard('b');
            return true;
        }
    }
    if ((left_r == true) && (right_r== true)) {
        // printf("starting to check player red\n");
        if (CheckPlayer('r')) 
        {
            Uncheck();
            // PrintBoard();
            // PrintBoard('r');
            // PrintBoard('b');
            return true; 
        }
    }

    Uncheck();
    return false;
}

bool board::IsOver(char color)
{
    if (CheckPlayer(color)) 
        { 
            Uncheck();
            // PrintBoard();
            // PrintBoard('r');
            // PrintBoard('b');
            return true;
        }
    Uncheck();
    return false;
}

void board::Uncheck()
{
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++)
        {
            fields[i][j].checked = false;
        }
    }

    return;
}

void board::RefreshConnections()
{
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++)
        {
            fields[i][j].SetNeighbours(fields, size);
        }
    }

    return;
}

bool board::IsPossible()
{
    char color;

    if (pawns_r == pawns_b + 1) {
        //red won
        color = 'r';
    }
    else if (pawns_b == pawns_r) {
        //blue won
        color = 'b';
    }
    else {
        return false;
    }

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if (fields[i][j].color == color)
            {

                fields[i][j].color = ' '; //putting the pawn out

                RefreshConnections();
                
                if (IsOver() == false) {
                    fields[i][j].color = color; //the return of the pawn
                    return true;
                }

                fields[i][j].color = color; //the return of the pawn
            }
        }
    }

    return false;
}

bool board::CheckPlayer(char color)
{
    if ((color != 'r') && (color != 'b')) {
        return false;
    }

    bool* won = (color == 'r') ? &won_r : &won_b;
    *won = false;

    // PrintBoard(color);
    // printf("starting recursive check (%c)...", color);
    //recursive check
    if (color == 'r') 
    {
        for (int i = 0; i < size; i++) 
        {
            if (fields[i][0].color == color) {
                // printf("for {%d, 0} (%d)...", i, fields[i][0].neighbours_count);
                if (RecursiveCheck(color, &fields[i][0])) 
                {
                    *won = true;
                    // printf("OK\n");
                    return *won;
                }
                // printf("\n");
            }
        }
    }
    else if (color == 'b') 
    {
        for (int i = 0; i < size; i++) 
        {
            if (fields[0][i].color == color) {
                // printf("for {0, %d} (%d)...", i, fields[i][0].neighbours_count);
                if (RecursiveCheck(color, &fields[0][i])) 
                {
                    *won = true;
                    // printf("OK\n");
                    return *won; 
                }
                // printf("\n");
            }
        }
    }

    // printf("NOT OK\n");
    return *won;
}
bool board::RecursiveCheck(char color, field* current_field)
{
    current_field->checked = true;

    if ((((color == 'r') && (current_field->position.x == size - 1)) || ((color == 'b') && (current_field->position.y == size - 1)))) 
    {
        return true;
    }
    else {
        for (int i = 0; i < 6; i++) {
            if ((current_field->neighbours[i] != nullptr) && (current_field->neighbours[i]->checked == false) && ((current_field->neighbours[i]->color == current_field->color))) {
                // printf("{%d, %d}...", current_field->neighbours[i]->position.y, current_field->neighbours[i]->position.x);
                if (RecursiveCheck(color, current_field->neighbours[i]))
                {
                    return true;
                }
            }
        }
        return false;
    }
}

int board::FreeFieldsCount()
{
    int count = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fields[i][j].color == ' ') {
                count++;
            }
        }
    }

    return count;
}

bool board::TwoTurnsPossible(char color)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fields[i][j].color == ' ') {
                fields[i][j].color = color;
                RefreshConnections();

                if (!IsOver(color)) {
                    //diagnistics:
                    // printf("This turn will not finish the game:");
                    // PrintBoard();
                    fields[i][j].color = ' ';
                    RefreshConnections();
                    Uncheck();

                    return true;
                }

                fields[i][j].color = ' ';
                RefreshConnections();
                Uncheck();
            }
        }
    }

    // printf("not possible for %c\n", color);
    return false;
}

bool board::Naive(char color, int turns)
{
    int free_space = 0;
    char current_turn;

    if (pawns_r == pawns_b) {
        //red turn
        current_turn = 'r';
    }
    else if (pawns_r == pawns_b + 1) {
        //blue turn
        current_turn = 'b';
    }

    if (current_turn == color) {
        free_space = 1 + (turns - 1) * 2;
    }
    else {
        free_space = turns * 2;
    }

    //printf("free space: %d\n", FreeFieldsCount());
    if (FreeFieldsCount() < free_space) {
        //printf("there is no free space!\n");
        return false;
    }

    //diagnistics:
    // printf("n turns: %d, color: %c", turns, color);
    // PrintBoard();

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if (fields[i][j].color == ' ') {
                fields[i][j].color = color;
                RefreshConnections();
                // PrintBoard();
                // printf("put %c {i = %d, j = %d} ",color, i, j);

                if (IsOver(color)) {
                    //diagnistics:
                    // printf("Is over:");
                    // PrintBoard();
                    fields[i][j].color = ' ';

                    return true;
                }

                if (turns == 2) {
                    for (int a = 0; a < size; a++) 
                    {
                        for (int b = 0; b < size; b++) 
                        {
                            if (fields[a][b].color == ' ') {
                                fields[a][b].color = color;
                    
                                RefreshConnections();
                                // PrintBoard();
                                // PrintBoard(color);
                                // printf("put %c {a = %d, b = %d} ",color, a, b);

                                if (IsOver(color)) {
                                    //diagnistics:
                                    // printf("Is over:");
                                    // PrintBoard();
                                    fields[i][j].color = ' ';
                                    fields[a][b].color = ' ';
                        
                                    return true;
                                }

                                // turning off by hands
                                fields[a][b].color = ' ';
                                // printf("cleared %c {a = %d, b = %d} ",color, a, b);
                            }
                        }
                    }
                }

                // turning off by hands
                fields[i][j].color = ' ';
                // printf("cleared %c {i = %d, j = %d} ",color, i, j);
            }
        }
    }


    return false;
}

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