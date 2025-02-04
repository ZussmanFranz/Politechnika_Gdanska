#pragma once
#include "animal.h"

class player: public animal
{  
protected:
    int ability_cooldown;
public:
    player(world* world_point, YX position);

    void Draw(YX position) override;
    int Action() override;
    organizm* MakeChild(YX new_position) override;

    bool RejectAttak(organizm* attaker) override; //The shield of Alzur

    int GetCooldown() { return ability_cooldown; }
    void SetCooldown(int value) { ability_cooldown = value; }

    CLASS GetClass() override;

    ~player();
};
