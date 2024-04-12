#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
//#include "organizm.h"

//#include "animals/animals.h"
#include "animals/animal.h"
#include "animals/player.h"
//#include "plants/plants.h"

typedef struct
{
    YX position;
    YX field_size;
    YX id;
    organizm* member;

    void draw_box(YX field_size)
    {
        int COLOR = COLOR_WHITE;

        if (member != nullptr) {
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

            init_pair(1, COLOR, COLOR_BLACK);
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
    const YX dimensions;
    const YX field_size;
    const YX padding;

    player* Player;

    int round;
public:
    world(int y, int x, YX field_size, YX padding);

    void Draw();
    void Update(char input);
    void Add(organizm* added);
    void Destroy(organizm* destroyed);

    YX GetDimensions(){ return dimensions; }
    YX GetFieldSize(){ return field_size; }
    field* FindField(YX id);

    int GetRound(){ return round; }

    ~world();
};

