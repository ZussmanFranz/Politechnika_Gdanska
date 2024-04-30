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
    bool added = false;
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

        for (int i = 0; i <= 1; i++) {
            for (int j = 0; j <= 1; j++) {
                if ((i == 0) && (j == 0)) {
                    continue;
                }
                
                if ((position.y + i >= size) || (position.x + j >= size)) {
                    topOFB = true;
                }

                if ((!topOFB) && (fields[position.y + i][position.x + j].color == color)){
                    neighbours[neighbours_count] = &fields[position.y + i][position.x + j];
                    neighbours_count++;
                }

                if ((position.y - i < 0) || (position.x - j < 0)) {
                    bottomOFB = true;
                }

                if ((!bottomOFB) && (fields[position.y - i][position.x - j].color == color)){
                    neighbours[neighbours_count] = &fields[position.y - i][position.x - j];
                    neighbours_count++;
                }

                topOFB = false;
                bottomOFB = false;
            }
        }

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
    void Uncheck();
    void RefreshConnections();
    bool IsCorrect() {return ((pawns_r == pawns_b + 1) || (pawns_r == pawns_b));}
    bool IsPossible();
    bool CheckPlayer(char color);
    bool RecursiveCheck(char color, field* current_field);

    int FreeFieldsCount();
    void TurnOffAdded();
    bool Naive(char color, int turns);

    void SetSize(int size) { this->size = size; }
    int GetSize() { return size; }

    field* GetField(int y, int x);

    ~board();
};

