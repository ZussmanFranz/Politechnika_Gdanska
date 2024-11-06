#include "organizm.h"
#include "world.h"
#include <ncurses.h>

organizm::organizm()
: world_point(nullptr) 
{}

organizm::organizm(world* world_point, int strength, int initiative, YX position)
{
    this->world_point = world_point;
    this->strength = strength;
    this->starting_strength = strength;
    this->initiative= initiative;
    this->position = position;
    death_sentence = false;
}

void organizm::Reproduct()
{
    field* free_field = world_point->GetFreeFieldNear(position);
    
    if (free_field == nullptr) {
        return;
    }

    world_point->Add(MakeChild(free_field->id));
    return;
}

void organizm::Draw(YX position) {
    mvwaddch(world_point->GetWindow(),position.y, position.x, avatar);
    return;
}

world* organizm::GetWorld()
{
    return world_point;
}

void organizm::SetPosition(YX position)
{
    this->position = position;
}

YX organizm::GetPosition()
{
    return position;
}

organizm::~organizm() {}