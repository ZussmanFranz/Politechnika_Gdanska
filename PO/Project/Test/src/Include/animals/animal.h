#ifndef ANIMAL_H
#define ANIMAL_H


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
    world_point->FindField(position)->member = nullptr;

    position = {position.y + delta.y, position.x + delta.x};

    // if (position.x > world_point->GetDimensions().x)
    // {
    //     position.x = world_point->GetDimensions().x;
    // }
    // else if (position.x < 0)
    // {
    //     position.x = 0;
    // }

    // if (position.y > world_point->GetDimensions().y)
    // {
    //     position.y = world_point->GetDimensions().y;
    // }
    // else if (position.y < 0)
    // {
    //     position.y = 0;
    // }

    world_point->FindField(position)->member = this;

    printw("Moved to {%d,%d}", position.y, position.x);
    return;
}


#endif // ANIMAL_H