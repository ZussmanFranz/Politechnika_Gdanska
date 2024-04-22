#include "animal.h"


animal::animal(int strength, int initiative, YX position, world* world_point)
: organizm(world_point)
{
    this->strength = strength;
    this->initiative = initiative;
    this->position = position;
}


void animal::Draw(YX position)
{
    init_pair(1, COLOR_RED, -1);
    
    attron(COLOR_PAIR(1));
    
    mvaddch(position.y, position.x, avatar);
    
    attroff(COLOR_PAIR(1));
}

int animal::Move(YX delta) //0 - normal move, 1 - collision
{
    bool collided = false;

    world_point->FindField(position)->member = nullptr;

    YX new_position = {position.y + delta.y, position.x + delta.x};

    if (new_position.x >= world_point->GetDimensions().x)
    {
        new_position.x = world_point->GetDimensions().x - 1;
        //mvprintw(0, 0, "right wall");
    }
    else if (new_position.x < 0)
    {
        new_position.x = 0;
        //mvprintw(0, 0, "left wall");
    }

    if (new_position.y >= world_point->GetDimensions().y)
    {
        new_position.y = world_point->GetDimensions().y - 1;
        //mvprintw(2, 0, "bottom wall");
    }
    else if (new_position.y < 0)
    {
        new_position.y = 0;
        //mvprintw(2, 0, "top wall");
    }

    //fight with the member of the new position (must return 1 if attak is failed and 0 is attak is succesful)
    organizm* target = world_point->FindField(new_position)->member;

    if (target != nullptr)
    {
        collided = true;
    }

    if ((collided) && (Collision(target) == 1))
    {
    //     //diagnostics:
    //     printw("\nattaker is dead.");
    //     getch();

        return 1;
    }

    //world_point->FindField(position)->draw_box(world_point->GetFieldSize());
    
    position = new_position;

    world_point->FindField(position)->member = this;

    //world_point->FindField(position)->draw_box(world_point->GetFieldSize());

    if (collided)
    {
        return 1;
    }
    return 0;
}

int animal::Action() // 0 - normal move, 1 - collision detected
{
    int delta_y = rand() % 3 - 1; // Generates random number between -1 and 1
    int delta_x = rand() % 3 - 1; // Generates random number between -1 and 1

    return Move({delta_y, delta_x});
}

int animal::Collision(organizm* target)
{
    world_point->GetLogger()->LogCollision(this, target);
    
    int result = Fight(target);
    
    world_point->GetLogger()->LogCollisionResult((result) ? target : this);
    
    // //diagnostics:
    // printw("\nresult is %d", result);
    // getch();


    // //diagnostics:
    // printw("\nlogged(no)");
    // getch();

    return result;
}

int animal::Fight(organizm* target)
{
    // //diagnostics:
    // clear();
    // printw("collision!");
    // getch();

    if (target == nullptr)
    {
        return 0;
    }

    if (target->GetStrength() <= strength)
    {
        // //diagnostics:
        // printw("\nsucces.");
        // getch();

        // succes
        //world_point->Kill(target);
        world_point->Destroy(target);
        return 0;
    }
    else if (target->GetStrength() > strength)
    {
        // //diagnostics:
        // printw("\nfail.");
        // getch();

        // failed
        //world_point->Kill(this);
        world_point->Destroy(this);
        return 1;
    }
}

CLASS animal::GetClass()
{
    return ANIMAL; 
}

animal::~animal()
{
}