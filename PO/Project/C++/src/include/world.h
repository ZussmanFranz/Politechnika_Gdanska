#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
#include "organizm.h"

#include "animals/animals.h"
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

    YX GetDimensions() const { return dimensions; }
    YX GetFieldSize() const { return field_size; }
    field* FindField(YX id);

    int GetRound(){ return round; }

    ~world();
};

world::world(int y, int x, YX field_size, YX padding)
: field_size(field_size), padding(padding), round(0), dimensions({y,x})
{
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    YX starting_padding = {2, max_x/2 - (x/2*(field_size.x + padding.x))};

    fields = new field*[y];

    for (int i = 0; i < y; i++) {
        fields[i] = new field[x];
    }

    // Initializing fields
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) 
        {
            fields[i][j].field_size = field_size;

            fields[i][j].position.y = i * (field_size.y + padding.y) + starting_padding.y;
            fields[i][j].id.y = i;
            fields[i][j].position.x = j * (field_size.x + padding.x) + starting_padding.x;
            fields[i][j].id.x = j;

            fields[i][j].member = nullptr;
        }
    }

    Player = new player(this, {0,0});

    Add(Player);
}

field* world::FindField(YX id)
{
    if ((id.y <= dimensions.y) && (id.y >= 0) && (id.x <= dimensions.x) && (id.x >= 0))
    {
        return &(fields[id.y][id.x]);
    }
    else
    {
        return nullptr;
    }
}

void  world::Draw()
{
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) 
        {
            fields[i][j].draw_box(field_size);
            if (fields[i][j].member != nullptr) 
            {
                fields[i][j].member->Draw({fields[i][j].position.y + fields[i][j].field_size.y/2, fields[i][j].position.x + fields[i][j].field_size.x/2});
            }
        }
    }

    //organizmy->Draw()
}
void world::Update(char input)
{
    round++;

    for (auto* org : members) { // i should add the initiative and age check
        org->Action();
    }

}

void world::Add(organizm* added)
{
    members.push_back(added);
    FindField(added->GetPosition())->member = added;
}

void world::Destroy(organizm* destroyed)
{
    FindField(destroyed->GetPosition())->member = nullptr;
    
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (*it == destroyed) 
        {
            delete *it;
            members.erase(it);
            break;
        }
    }
}

world::~world()
{
    for (auto it = members.begin(); it != members.end(); ++it) {
        delete *it;
        members.erase(it);
        break;
    }

    for (int i = 0; i < dimensions.y; i++) 
    {
        delete[] fields[i];
    }

    delete[] fields;
}
