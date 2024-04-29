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
    std::string string_representation;
    task current_task;
    int size;
    int pawns_b;
    int pawns_r;
    const YX ERROR_FIELD = {-1,-1}; 
public:
    board(int rows, std::istream& input_stream);

    void HandleBoard(std::istream& input_stream);
    void PrintBoard();

    void HandleTask(std::istream& input_stream, char start_c);
    void PrintTask();
    int SolveTask();

    // void Convert();
    // void PrintFields();

    void SetSize(int size) { this->size = size; }
    int GetSize() { return size; }

    field* GetField(int y, int x);

    ~board();
};

