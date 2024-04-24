#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <ncurses.h>
#include "organizm.h"
//#include "animals/animal.h"
//#include "animals/animals.h"
//#include "plants/plants.h"
#include "logmanager.h"

struct field
{
    YX position;
    YX field_size;
    YX id;
    organizm* member;

    void draw_box(YX field_size)
    {
        int pair;

        if (member != nullptr) {
            switch (member->GetClass())
            {
            case ANIMAL:
                pair = 1;
                break;
            case PLANT:
                pair = 2;
                break;
            case PLAYER:
                pair = 3;
                break;
            default:
                break;
            }

            attron(COLOR_PAIR(pair));
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
            attroff(COLOR_PAIR(pair));
        }
        return;
    }
};


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
    void DrawInterface();
    void DrawEndscreen();
    
    organizm* GetPlayer();

    void Update();
    void Add(organizm* added);
    void Destroy(organizm* destroyed);
    void SortMembers();
    int CountNeighboursSameType(organizm* me);
    bool SameType(organizm* a, organizm* b);
    void Clean();

    void GenerateRandomOrganizm(int type, int sub_type);
    void GenerateRandomStart(int number_of_organizms);
    void GenerateEvenStart(int number_of_organizms);

    YX GetDimensions() const { return dimensions; }
    YX GetFieldSize() const { return field_size; }
    field* FindField(YX id);
    field* GetRandomField();
    field* GetFreeFieldNear(YX position);
    std::vector<field*> GetFieldsNear(YX position);

    int GetRound(){ return round; }
    bool IsOver() { return end; }
    void StopIt() { end = true; }

    logmanager* GetLogger() { return Logger; }

    ~world();
};

