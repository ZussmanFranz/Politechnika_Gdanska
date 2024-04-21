#pragma once
#include "organizm.h"
#include "world.h"

class animal: public organizm
{
public:
    animal(int strength, int initiative, YX position, world* world_point);

    void Draw(YX position) override;

    void Move(YX delta);

    void Action() override;

    int Collision(organizm* target) override;
    int Fight(organizm* target); 

    CLASS GetClass() override;

    ~animal();
};