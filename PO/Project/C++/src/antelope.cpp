#include "antelope.h"
#include "world.h"
#include <cstdlib>

antelope::antelope(world* world_point, YX position)
:animal(4,4, position, world_point)
{
    avatar = 'A';
}

int antelope::Action() // 0 - normal move, 1 - collision detected
{
    int delta_y = rand() % 5 - 2; // Generates random number between -2 and 2
    int delta_x = rand() % 5 - 2; // Generates random number between -2 and 2

    if ((delta_x == 0) && (delta_y == 0)) {
        return 0;
    }

    return Move({delta_y, delta_x});
}

bool antelope::RejectAttak(organizm* attaker)
{
    if (rand() % 2 == 1) {
        world_point->GetLogger()->Log("antelope avoided attak");

        //find free field near it
        //if there is no free space, return false;
        field* new_lokation = world_point->GetFreeFieldNear(position);

        if (new_lokation == nullptr) {
            return  false;
        }

        world_point->FindField(position)->member = nullptr;

        attaker->GetWorld()->FindField(attaker->GetPosition())->member = nullptr;
        attaker->SetPosition(position);
        attaker->GetWorld()->FindField(attaker->GetPosition())->member = attaker;

        position = new_lokation->id;

        return true;
    }

    return false;
}

organizm* antelope::MakeChild(YX new_position)
{
    return (new antelope(world_point, new_position));
}

antelope::~antelope()
{
}