#pragma once
#include "organizm.h"

class animal: public virtual organizm
{
private:
public:
    animal(int strength, int initiative, YX position, world* world_point)
    : organizm(world_point)
    {
        this->strength = strength;
        this->initiative = initiative;
        this->position = position;
    }

    void Draw(YX position) override;
    void Move(YX delta);

    CLASS GetClass() override { return ANIMAL; }

    ~animal();
};

animal::~animal()
{
}

void animal::Draw(YX position)
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    
    attron(COLOR_PAIR(1));
    
    mvprintw(position.y, position.x, &avatar);
    
    attroff(COLOR_PAIR(1));
}

void animal::Move(YX delta)
{
    YX new_position = {position.y + delta.y, position.x + delta.x};

    if (new_position.x > world_point->GetDimensions().x)
    {
        new_position.x = world_point->GetDimensions().x;
    }
    else if (new_position.x < 0)
    {
        new_position.x = 0;
    }

    if (new_position.y > world_point->GetDimensions().y)
    {
        new_position.y = world_point->GetDimensions().y;
    }
    else if (new_position.y < 0)
    {
        new_position.y = 0;
    }

    return;
}
