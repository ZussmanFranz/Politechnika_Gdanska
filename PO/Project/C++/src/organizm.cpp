#include "organizm.h"
#include "world.h"
#include <ncurses.h>

organizm::organizm()
: world_point(nullptr) 
{}

organizm::organizm(world* world_point)
{
    this->world_point = world_point;
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
    //mvprintw(position.y, position.x, &avatar);
    mvaddch(position.y, position.x, avatar);
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