#include <cstdio>
#include <iostream>
#include <string>

struct YX
{
    int y;
    int x;
};

struct field
{
    char color;
    bool checked = false;
    YX position;
    field* neighbours[6];
    int neighbours_count;

    int SetNeighbours(field** fields, int size)
    {
        for (int n = 0; n < 6; n++) {
            neighbours[n] = nullptr;
        }

        neighbours_count = 0;
        bool topOFB = false;
        bool bottomOFB = false;

        if (color == ' ') {
            return neighbours_count;
        }

        //printf("setting a field {%d, %d}: %c.\n", position.y, position.x, color);

        for (int i = 0; i <= 1; i++) {
            for (int j = 0; j <= 1; j++) {
                if ((i == 0) && (j == 0)) {
                    continue;
                }
                
                if ((position.y + i >= size) || (position.x + j >= size)) {
                    topOFB = true;
                }
                // else {
                //     printf("trying a field {%d, %d}: %c.", position.y + i, position.x + j, fields[position.y + i][position.x + j].color);
                // }

                if ((!topOFB) && (fields[position.y + i][position.x + j].color == color)){
                    neighbours[neighbours_count] = &fields[position.y + i][position.x + j];
                    neighbours_count++;
                    //printf(" ...OK\n");
                }
                // else if (!topOFB) {
                //     printf(" ...NOT OK\n");
                // }

                if ((position.y - i < 0) || (position.x - j < 0)) {
                    bottomOFB = true;
                }
                // else {
                //     printf("trying a field {%d, %d}: %c.", position.y - i, position.x - j, fields[position.y - i][position.x - j].color);
                // }

                if ((!bottomOFB) && (fields[position.y - i][position.x - j].color == color)){
                    neighbours[neighbours_count] = &fields[position.y - i][position.x - j];
                    neighbours_count++;
                    //printf(" ...OK\n");
                }
                // else if (!bottomOFB) {
                //     printf(" ...NOT OK\n");
                // }

                topOFB = false;
                bottomOFB = false;
            }
        }

        printf("\n");

        return neighbours_count;
    }
};

enum task
{
    SIZE,
    PAWNS,
    IS_CORRECT,
    IS_OVER,
    IS_POSSIBLE,
    CAN_RED_IN_1_NAIVE,
    CAN_RED_IN_2_NAIVE,
    CAN_BLUE_IN_1_NAIVE,
    CAN_BLUE_IN_2_NAIVE,
    CAN_RED_IN_1_PERFECT,
    CAN_RED_IN_2_PERFECT,
    CAN_BLUE_IN_1_PERFECT,
    CAN_BLUE_IN_2_PERFECT,
    ERROR
};

class board
{
private:
    field** fields;
    task current_task;
    int size;
    int pawns_b;
    int pawns_r;
    bool won_b;
    bool won_r;
    const YX ERROR_FIELD = {-1,-1}; 
public:
    board(int rows, std::istream& input_stream);

    void HandleBoard(std::istream& input_stream);
    void PrintBoard();
    void PrintBoard(char search_color);

    void HandleTask(std::istream& input_stream, char start_c);
    void PrintTask();
    int SolveTask();

    bool IsOver();
    bool IsCorrect() {return ((pawns_r - 1 == pawns_b) || (pawns_r == pawns_b));}
    bool CheckPlayer(char color);
    bool RecursiveCheck(char color, field* current_field);

    void SetSize(int size) { this->size = size; }
    int GetSize() { return size; }

    field* GetField(int y, int x);

    ~board();
};

