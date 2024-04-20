#include <iostream>

typedef struct YX
{
    int y;
    int x;
};


class board
{
private:
    char fields[11][11];
    int rows;
    char* current_field;
    const YX ERROR_FIELD = {-1,-1}; 
public:
    board();

    void IncrementRows() { rows++; }
    void SetRows(int rows) { this->rows = rows; }
    int GetRows() { return rows; }

    char* GetCurrent() { return current_field; }

    char* GetField(int y, int x);
    YX FindField(char* wanted);

    char* GetNext();//?

    void AddField(int y, int x, char c);

    ~board();
};

board::board()
: rows(0)
{
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            fields[i][j] = 0;       
        }
    }
}

char* board::GetField(int y, int x)
{
    if (y > rows || x > rows || y < 0 || x < 0)
    {
        return &(fields[y][x]);
    }
    else{
        return nullptr;
    }
}

YX board::FindField(char* wanted)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (&(fields[i][j]) == wanted)
            {
                return {i, j};
            }
        }
    }

    return ERROR_FIELD;
}

char* board::GetNext()
{
    YX current_field_coords = FindField(current_field);

    if (current_field_coords.y - 1 < 0)
    {
        
    }
    
}

void board::AddField(int y, int x, char c)
{
    if (y < 0 || x < 0 || y > 11 || x > 11)
    {
        return;
    }
    

    if (y >= rows || x >= rows)
    {
        rows++; 
    }
    
    fields[y][x] = c;
    return;
}

board::~board()
{
}
