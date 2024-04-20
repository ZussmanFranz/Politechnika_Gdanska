#pragma once
#include <ncurses.h>
//#include "world.h"

typedef struct {
    int y;
    int x;
}YX;

class world;

typedef enum
{
    PLANT,
    ANIMAL,
    PLAYER
}CLASS;

class organizm {
protected:
    int strength;
    int initiative;
    YX position;
    world* world_point;
    char avatar;

public:
    organizm():world_point(nullptr){}
    organizm(world* world_point):world_point(world_point) {}

    virtual void Action() = 0;  // add virtual
    virtual void Collision() = 0;           // add virtual
    virtual void Draw(YX position) { mvprintw(position.y, position.x, &avatar); }
    void SetPosition(YX position) { this->position = position; }
    YX GetPosition() {return position;}
    void SetWorld(world* world_ref) { world_point = world_ref; }
    virtual CLASS GetClass() = 0;

    ~organizm() {}
};