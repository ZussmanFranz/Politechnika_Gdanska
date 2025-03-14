#pragma once
#include "animal.h"


class player: public virtual animal
{  
public:
    player(world* world_point, YX position)
    :animal(5,4, position, world_point)
    {
        avatar = 'P';
    }

    void Draw(YX position) override;
    void Action() override;
    void Action(char input);

    void Collision() override {}

    CLASS GetClass() override { return PLAYER; }

    ~player();
};


void player::Draw(YX position)
{
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    
    attron(COLOR_PAIR(1));
    
    mvprintw(position.y, position.x, &avatar);
    
    attroff(COLOR_PAIR(1));
}

void player::Action()
{
    YX delta = {0,0};

    char input = getch();

    switch (input)
    {
    case 'w':
        delta = {-1, 0};
        break;
    case 'a':
        delta = {0, -1};
        break;
    case 's':
        delta = {1, 0};
        break;
    case 'd':
        delta = {0, 1};
        break;     
    default:
        break;
    }

    Move(delta);
    //finish the logic!
}

void player::Action(char input)
{
    YX delta = {0,0};

    switch (input)
    {
    case 'w':
        delta = {-1,0};
        break;
    case 'a':
        delta = {0,-1};
        break;
    case 's':
        delta = {1,0};
        break;
    case 'd':
        delta = {0,1};
        break;
    default:
        break;
    }

    Move(delta);
}

player::~player()
{
}
