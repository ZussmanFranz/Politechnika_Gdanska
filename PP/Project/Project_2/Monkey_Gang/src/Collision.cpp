#include "Collision.hpp"

void Collision::AABB(SDL_Rect recA, SDL_Rect recB, int result[4]) //Axis-Aligned Bounding Box
{
    if (
        (recA.x + recA.w >= recB.x) && 
        (recB.x + recB.w >= recA.x) &&
        (recA.y + recA.h >= recB.y) &&
        (recB.y + recB.h >= recA.y)
    )
        {
            if ((recA.y <= (recB.y + recB.h)) && ((recB.y + recB.h) < (recA.y + recA.h)))
            {
                result[0] = 1; //top collision detected
            }
            if (((recA.x + recA.w) > recB.x) && (recB.x > recA.x))
            {
                result[1] = 1; //right collision detected
            }
            if (((recA.y + recA.h) > recB.y) && (recB.y > recA.y))
            {
                result[2] = 1; //bottom collision detected
            }
            if ((recA.x < (recB.x + recB.w)) && ((recB.x + recB.w) < (recA.x + recA.w)))
            {
                result[3] = 1; //left collision detected
            }
            
        }
    return;
}

bool Collision::CollisionDetection(int result[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (result[i] != 0)
        {
            return true;
        }
    }
    return false;
}

void Collision::CollisionManager(GameObject* obj_main, GameObject* obj_second)
{
    SDL_Rect* rect_main = obj_main->GetRect();
    SDL_Rect* rect_second = obj_second->GetRect();

    SDL_Rect rect_main_copy = *rect_main;
    rect_main_copy.x += (obj_main->position->velocity_x * obj_main->position->speed);
    rect_main_copy.y += (obj_main->position->velocity_y * obj_main->position->speed); // I am making prediction of the next move 

    bool move_x = true;
    bool move_y = true;

    int result[] = {0, 0, 0, 0};
    Collision::AABB(rect_main_copy, *rect_second, result);
    bool collision_check = Collision::CollisionDetection(result);

    if (collision_check)
    {
        /*printf("Collision manager have this: (%d, %d, %d, %d) First object: (%c), second object: (%c)\n",
            result[0], result[1], result[2], result[3], 
            obj_main->type, obj_second->type);*/
        if (obj_second->type == 'S')
        {
            obj_main->sprite->on_stairs = true;
        }
        else
        {
            if (result[0] == 1) //top collision
            {
                //obj_main->position->Push(0, -1 * (obj_main->position->velocity_y * obj_main->position->speed));
                //obj_main->position->velocity_y = 0; 
                obj_main->position->Push(0, 1); // push a little bit lower
                obj_main->sprite->on_ground = false;
                move_y = false;
            }

            if ((result[1] == 1) || (result[3] == 1)) //right collision or left collision
            {
                //obj_main->position->Push(-1 * (obj_main->position->velocity_x * obj_main->position->speed), 0);
                if ((obj_main->type == 'B') && (obj_second->type == 'W'))
                {
                    obj_main->position->velocity_x = -1 * (obj_main->position->velocity_x); // inverting x velocity when badya hits a window border
                    move_x = true;
                }
                else
                {
                    move_x = false;
                }
            }

            if (result[2] == 1) // bottom collision
            {
                //obj_main->position->Push(0, -1 * (obj_main->position->velocity_y * obj_main->position->speed));
                obj_main->sprite->on_ground = true;
                obj_main->position->velocity_y = 0; //stop falling
                obj_main->position->Push(0, -1); // push a little bit higher
                move_y = false;
            }
            else
            {
                obj_main->sprite->on_ground = false;
            }

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
        } 
    }

    if (!move_x)
    {
        if ((obj_main->type == 'B') && (obj_second->type == 'W'))
        {
            obj_main->position->velocity_x *= -1;
            printf("Change direction!\n");
        }
        else
        {
            obj_main->position->velocity_x = 0;
        }
    }
    if (!move_y)
    {
        obj_main->position->velocity_y = 0;
    }
}

Collision::Collision()
{

}
Collision::~Collision()
{

}