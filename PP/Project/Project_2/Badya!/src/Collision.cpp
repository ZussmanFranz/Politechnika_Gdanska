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
                result[0] = -recA.y + (recB.y + recB.h); //top collision detected
            }
            if (((recA.x + recA.w) > recB.x) && (recB.x > recA.x))
            {
                result[1] = -1 * ((recA.x + recA.w) - recB.x + 1); //right collision detected
            }
            if (((recA.y + recA.h) > recB.y) && (recB.y > recA.y))
            {
                result[2] = (recA.y + recA.h) - recB.y; //bottom collision detected
            }
            if ((recA.x < (recB.x + recB.w)) && ((recB.x + recB.w) < (recA.x + recA.w)))
            {
                result[3] = (recB.x + recB.w) - recA.x + 1; //left collision detected
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
    rect_main_copy.y += (obj_main->position->velocity_y * obj_main->position->speed) + 1; // I am making prediction of the next move. + 1 is for fall check

    int result[] = {0, 0, 0, 0};
    Collision::AABB(rect_main_copy, *rect_second, result);
    bool collision_check = Collision::CollisionDetection(result);

    if (collision_check)
    {
        //printf("(%c)\n", obj_second->type);
        /*printf("Collision manager have this: (%d, %d, %d, %d) First object: (%c), second object: (%c)\n",
            result[0], result[1], result[2], result[3], 
            obj_main->type, obj_second->type);*/
        if (obj_second->type == 'S')
        {   
            if (obj_main->type == 'P')
            {
                obj_main->sprite->on_stairs = true;
            }
        }
        else if (obj_second->type == 'E')
        {
            obj_main->sprite->exit = true;
        }
        else if ((obj_second->type == 'P') && (obj_main->type == 'B'))
        {
            obj_second->sprite->brutally_murdered = true;
        }
        else if ((obj_second->type == 'P') && (obj_main->type == 'G'))
        {
            obj_second->sprite->exit = true;
        }
        else if(obj_second->type == 'A')
        {
            if (obj_main->type == 'P')
            {
                obj_main->sprite->brutally_murdered = true;
            }
        }
        else
        {
            int d_y = (result[0]) ? result[0] : result[2];
            int d_x = (result[1]) ? result[1] : result[3];

            if (result[0]) //top collision
            {
                if ((abs(d_y) > abs(d_x))) // && (obj_main->sprite->on_stairs == false))
                {
                    obj_main->position->Push(0, result[0] + 2);     
                }
                obj_main->position->velocity_y *= -1;
                obj_main->sprite->on_ground = false;
            }

            if (result[2]) // bottom collision
            {
                //obj_main->position->Push(0, -1 * (obj_main->position->velocity_y * obj_main->position->speed));
                obj_main->sprite->on_ground = true;
                obj_main->position->velocity_y = 0; //stop falling
                if ((result[2] > 1)) // && (obj_main->sprite->on_stairs == false))
                {
                    obj_main->position->Push(0, -result[2]+1); // push a little bit higher
                    result[1] = result[3] = 0;
                }
            }

            if ((result[1]) || (result[3])) //right collision or left collision
            {
                if (obj_second->type == 'W')
                {
                    if (result[1])
                    {
                        obj_main->position->Push(-5, -2);  
                    }
                    else
                    {
                        obj_main->position->Push(5, -2);  
                    }
                    
                    if ((obj_main->type == 'B') || (obj_main->type == 'G'))
                    {
                        obj_main->position->velocity_x *= -1;
                    }
                    
                }
                else
                {
                    if ((abs(d_y) < abs(d_x)) && (abs(d_y) > 1))
                    {
                        obj_main->position->Push(d_x, 0);    
                    }
                }
            }

            if ((obj_main->type == 'P') && (obj_second->type == 'B')) // collision of the player and a badya is detected, so the player is DEAD now
            {
                obj_main->sprite->brutally_murdered = true;
                //printf("The player has been murdered!\n");
            }
            
            if ((obj_main->type == 'P') && ((obj_second->type == 'E') || (obj_second->type == 'G'))) // the player succesfully escaped
            {
                obj_main->sprite->exit = true;
                //printf("The player has escaped form level %d!\n", Game::level);
            }
        } 
    }
}

Collision::Collision()
{

}
Collision::~Collision()
{

}