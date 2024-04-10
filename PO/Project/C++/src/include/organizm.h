#pragma once
#include "world.h"
#include "ncurses.h"

typedef struct {
    int y;
    int x;
} YX;

typedef enum {
    PLANT,
    ANIMAL,
    PLAYER
} CLASS;

class organizm {
protected:
    int strength;
    int initiative;
    YX position;
    world* world_point;
    char avatar;

public:
    organizm();
    organizm(world* world_point) {this->world_point = world_point;}

    virtual void Action() = 0;  // add virtual
    void Collision();            // add virtual
    virtual void Draw(YX position);
    void SetPosition(YX position);
    YX GetPosition();
    virtual CLASS GetClass() = 0;

    ~organizm();
};

organizm::organizm()
: world_point(nullptr) 
{}

organizm::~organizm() {}

void organizm::Draw(YX position) {
    mvprintw(position.y, position.x, &avatar);
}