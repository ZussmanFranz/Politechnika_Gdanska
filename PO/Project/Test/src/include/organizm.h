#pragma once
//#include "world.h"
#include "ncurses.h"
#include "structures.h"


class world;

class organizm {
protected:
    int strength;
    int initiative;
    YX position;
    world& world_point;
    char avatar;

public:
    //organizm();
    organizm(world& world_point):world_point(world_point) {}

    virtual void Action() = 0;  // add virtual
    void Collision();            // add virtual
    virtual void Draw(YX position);
    void SetPosition(YX position);
    YX GetPosition();
    void SetWorld(world& world_ref) {world_point = world_ref}
    virtual CLASS GetClass() = 0;

    ~organizm();
};

// organizm::organizm()
// {}

organizm::~organizm() {}

void organizm::Draw(YX position) {
    mvprintw(position.y, position.x, &avatar);
}