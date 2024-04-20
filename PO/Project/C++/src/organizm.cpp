#include "organizm.h"
#include <ncurses.h>

organizm::organizm()
: world_point(nullptr) 
{}

organizm::organizm(world* world_point)
{
    this->world_point = world_point;
}

organizm::~organizm() {}

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