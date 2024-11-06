#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
#include "organizm.h"
#include "animal.h"
#include "player.h"

typedef struct
{
    YX position;
    YX field_size;
    YX id;
    organizm* member;

    void draw_box(YX field_size)
    {
        // int COLOR = COLOR_WHITE;

        // if (member != nullptr) {
        //     if (auto player_ptr = dynamic_cast<player*>(member)) {
        //         COLOR = COLOR_YELLOW;
        //     } else if (auto plant_ptr = dynamic_cast<plant*>(member)) {
        //         COLOR = COLOR_GREEN;
        //     } else if (auto animal_ptr = dynamic_cast<animal*>(member)) {
        //         COLOR = COLOR_RED;
        //     }

        //     init_pair(1, COLOR, COLOR_BLACK);
        //     attron(COLOR_PAIR(1));
        // }

        mvvline(position.y + 1, position.x, ACS_VLINE, field_size.y - 1);
        mvvline(position.y, position.x + field_size.x - 1, ACS_VLINE, field_size.y - 1);
        mvhline(position.y, position.x, ACS_HLINE, field_size.x - 1);
        mvhline(position.y + field_size.y - 1, position.x, ACS_HLINE, field_size.x - 1);

        mvaddch(position.y, position.x, ACS_ULCORNER);
        mvaddch(position.y, position.x + field_size.x - 1, ACS_URCORNER);
        
        mvaddch(position.y + field_size.y - 1, position.x, ACS_LLCORNER);
        mvaddch(position.y + field_size.y - 1, position.x + field_size.x - 1, ACS_LRCORNER);

        // if (member != nullptr){
        //     attroff(COLOR_PAIR(1));
        // }
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
