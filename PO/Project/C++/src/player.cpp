#include "player.h"
#include "world.h"
#include <cstdlib>
#include <ncurses.h>
#include <vector>

player::player(world* world_point, YX position)
:animal(5,4, position, world_point)
{
    avatar = 'P';
    ability_cooldown = 10;
}   

void player::Draw(YX position)
{   
    if (strength > starting_strength) 
    {
        wattron(world_point->GetWindow(),A_BOLD); 
    }

    wattron(world_point->GetWindow(),COLOR_PAIR(3));
    
    mvwaddch(world_point->GetWindow(),position.y, position.x, avatar);
    
    wattroff(world_point->GetWindow(),COLOR_PAIR(3));

    if (strength > starting_strength) 
    {
        wattroff(world_point->GetWindow(),A_BOLD); 
    }
}


int player::Action()
{
    ability_cooldown++;

    if (ability_cooldown == 6) {
        world_point->GetLogger()->Log("ability is finished :(\n");
    }

    world_point->Draw();

    YX delta = {0,0};

    char input = wgetch(world_point->GetWindow());

    switch (input)
    {
    case 'w':
        delta = {-1,0};
        break;
    case 'a':
        delta = {0,-1};
        break;
    case 's':
        delta = {1,0};
        break;
    case 'd':
        delta = {0,1};
        break;
    case 'q':
        world_point->StopIt();
        break;
    case 'e':
        if (ability_cooldown > 10) 
        {
            ability_cooldown = 0;
            world_point->GetLogger()->Log("ability activated :)\n");
        }
        else 
        {
            world_point->GetLogger()->Log("it's too early :|\n");
        }
        break;
    default:
        break;
    }

    return Move(delta);
}

bool player::RejectAttak(organizm* attaker)
{
    if (ability_cooldown <= 5) {
        std::vector<field*> fields_near_attaker = world_point->GetFieldsNear(attaker->GetPosition());
        
        if (fields_near_attaker.size() == 0) {
            world_point->GetLogger()->Log("Shield of Alzur could not protect :(");
            return false;
        }

        YX new_position = (fields_near_attaker[rand() % fields_near_attaker.size()])->id;

        attaker->SetPosition(new_position);

        world_point->GetLogger()->Log("Shield of Alzur protected player");
        return true;
    }

    return false;
}

CLASS player::GetClass() 
{ 
    return PLAYER; 
}

organizm* player::MakeChild(YX new_position)
{
    return (new player(world_point, new_position));
}

player::~player()
{
}