#pragma once
#include "animal.h"

class player: public animal
{  
public:
    player(world* world_point, YX position);

    void Draw(YX position) override;
    //void Action() override;
    int Action(char input);

    CLASS GetClass() override;

    ~player();
};
