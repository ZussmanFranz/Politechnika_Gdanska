#pragma once
#include "organizm.h"
#include "world.h"

class plant: public organizm
{
public:
    plant(int strength, YX position, world* world_point);

    void Draw(YX position) override;

    int Action() override;

    //inherited virtuals
    bool RejectAttak(organizm* attaker) override { return false;}
    int Collision(organizm* target) override { return 1;}
    int Fight(organizm* target) override { return 1; }

    CLASS GetClass() override { return PLANT; }

    ~plant();
};