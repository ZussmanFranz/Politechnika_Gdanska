#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
#include "organizm.h"
//#include "animals/animal.h"
//#include "animals/animals.h"
//#include "plants/plants.h"
#include "logmanager.h"

typedef struct
{
    YX position;
    YX field_size;
    YX id;
    organizm* member;

    void draw_box(YX field_size)
    {
        if (member != nullptr) {
            int COLOR = COLOR_MAGENTA;
            
            switch (member->GetClass())
            {
            case PLAYER:
                COLOR = COLOR_YELLOW;
                break;
            case PLANT:
                COLOR = COLOR_GREEN;
                break;
            case ANIMAL:
                COLOR = COLOR_RED;
                break;
            default:
                break;
            }

            init_pair(1, COLOR, -1);
            attron(COLOR_PAIR(1));
        }

        mvvline(position.y + 1, position.x, ACS_VLINE, field_size.y - 1);
        mvvline(position.y, position.x + field_size.x - 1, ACS_VLINE, field_size.y - 1);
        mvhline(position.y, position.x, ACS_HLINE, field_size.x - 1);
        mvhline(position.y + field_size.y - 1, position.x, ACS_HLINE, field_size.x - 1);

        mvaddch(position.y, position.x, ACS_ULCORNER);
        mvaddch(position.y, position.x + field_size.x - 1, ACS_URCORNER);
        
        mvaddch(position.y + field_size.y - 1, position.x, ACS_LLCORNER);
        mvaddch(position.y + field_size.y - 1, position.x + field_size.x - 1, ACS_LRCORNER);

        if (member != nullptr){
            attroff(COLOR_PAIR(1));
        }
        return;
    }
}field;


class world
{
private:
    std::vector<organizm*> members;
    field** fields;
    YX dimensions;
    YX field_size;
    YX padding;

    int round;
    bool end;

    logmanager* Logger;
public:
    world(int y, int x, YX field_size, YX padding);

    void Draw();
    void Update(char input);
    void Add(organizm* added);
    void Destroy(organizm* destroyed);
    void Kill(organizm* killed);

    void GenerateRandomOrganizm();
    void GenerateRandomStart(int number_of_organizms);

    YX GetDimensions() const { return dimensions; }
    YX GetFieldSize() const { return field_size; }
    field* FindField(YX id);
    field* GetRandomField();

    int GetRound(){ return round; }
    bool IsOver() { return end; }

    logmanager* GetLogger() { return Logger; }

    ~world();
};

