#include "Collision.hpp"

void Collision::AABB(SDL_Rect recA, SDL_Rect recB, int result[6]) //Axis-Aligned Bounding Box
{
    int deep_x = 0;
    int deep_y = 0;

    if ((recA.y <= (recB.y + recB.h)) && ((recA.y + recA.h) > (recB.y + recB.h)))
    {
        result[0] = 1; //top collision detected
        deep_y = recB.y + recB.h - recA.y;
    }
    if (((recA.x + recA.w) > recB.x) && (recA.x < recB.x))
    {
        result[1] = 1; //right collision detected
        deep_x = -1 * (recA.x + recA.w - recB.x);
    }
    if (((recA.y + recA.h) > recB.y) && (recB.y > recA.y))
    {
        result[2] = 1; //bottom collision detected
        deep_y = -1 * (recA.y + recA.h - recB.y);
    }
    if ((recA.x < (recB.x + recB.w)) && ((recB.x + recB.w) < (recA.x + recA.w)))
    {
        result[3] = 1; //left collision detected
        deep_x = recB.x + recB.w - recA.x;
    }

    result[4] = deep_x;
    result[5] = deep_y;

    return;
}

bool Collision::CollisionDetection(int result[6])
{
    for (int i = 0; i < 4; i++)
    {
        if (result[i] != 0)
        {
            return true;
        }
    }
    result[5] = 0;
    result[6] = 0;
    return false;
}

void Collision::FallManager(GameObject* obj_main, GameObject* obj_second)
{
    if ((obj_second->type == 'O') || (obj_second->type == 'W')) //second object is a platform or a window border
    {
        SDL_Rect* rect_main_orig = obj_main->GetRect();
        SDL_Rect* rect_second_orig = obj_second->GetRect();

        SDL_Rect rect_main = *rect_main_orig;
        SDL_Rect rect_second = *rect_second_orig;

        obj_main->sprite->on_ground = false;
        //obj_main->position->velocity_y = 1;

        printf("Fall: destA: (%d) (%d), destB: (%d) (%d)\n", rect_main.x, rect_main.y, rect_second.x, rect_second.y);

        if ((rect_main.x <= (rect_second.x + rect_second.w)) && ((rect_main.x + rect_main.w) >= rect_second.x)) // OX check
        {
            //printf("(%d <= %d + %d) && (%d + %d >= %d)\n", rect_main.x, rect_second.x, rect_second.w, rect_main.x, rect_second.x);
            if ((rect_main.y + rect_main.h - rect_second.y) <= 4) // OY "laser" check
            {
                //printf("Position before: x:(%d), y:(%d)\n", obj_main->position->x(), obj_main->position->y());
                int magnet = rect_second.y - rect_main.y - rect_main.h - 1; // 1 is a distance between the floor and the object;
                obj_main->position->Push(0, -magnet);
                obj_main->sprite->on_ground = true;
                //obj_main->position->velocity_y = 0;
                //printf("Magnet! New position: x:(%d), y:(%d)\n", obj_main->position->x(), obj_main->position->y());
            }
        }
        
    }
    return;
}

void Collision::CollisionManager(GameObject* obj_main, GameObject* obj_second)
{
    SDL_Rect* rect_main = obj_main->GetRect();
    SDL_Rect* rect_second = obj_second->GetRect();

    SDL_Rect rect_main_copy = *rect_main;

    rect_main_copy.x += (obj_main->position->velocity_x * obj_main->position->speed);
    rect_main_copy.y += (obj_main->position->velocity_y * obj_main->position->speed); // I am making prediction of the next move 

    int result[] = {0, 0, 0, 0, 0}; // top right bottom left + distance of push
    Collision::AABB(rect_main_copy, *rect_second, result);
    bool collision_check = Collision::CollisionDetection(result);

    if (collision_check)
    {
        if (result[0]) {printf("T ");}
        if (result[1]) {printf("R ");}
        if (result[2]) {printf("B ");}
        if (result[3]) {printf("L ");}
        printf("\n");

        if (obj_second->type == 'S')
        {
            obj_main->sprite->on_stairs = true;
        }
        else
        {
            if ((result[2] && obj_main->sprite->on_ground) == false)
            {
                obj_main->position->Push(result[4] + 1, 0);
                printf("push X: (%d)", result[4] + 1);
            }
            obj_main->position->Push(0, result[5] + 1); 
            printf(" push Y: (%d)", result[5]);

            printf("\n");

            if ((obj_main->type == 'P') && (obj_second->type == 'B')) // collision of the player and a badya is detected, so the player is DEAD now
            {
                obj_main->sprite->brutally_murdered = true;
                printf("The player has been murdered!\n");
            }
            
            if ((obj_main->type == 'P') && (obj_second->type == 'E')) // the player succesfully escaped
            {
                obj_main->sprite->exit = true;
                printf("The player has escaped!\n"); //...from level n
            }

            if ((obj_main->type == 'B') && ((result[1]) || (result[3])))
            {
                obj_main->position->velocity_x *= -1;
            }
        } 
    }

    return;
}

Collision::Collision()
{

}
Collision::~Collision()
{

}