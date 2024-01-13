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
                result[1] = (recA.x + recA.w) - recB.x; //right collision detected
            }
            if (((recA.y + recA.h) > recB.y) && (recB.y > recA.y))
            {
                result[2] = (recA.y + recA.h) - recB.y; //bottom collision detected
            }
            if ((recA.x < (recB.x + recB.w)) && ((recB.x + recB.w) < (recA.x + recA.w)))
            {
                result[3] = recA.x < (recB.x + recB.w); //left collision detected
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

        //printf("Fall: destA: (%d) (%d), destB: (%d) (%d)\n", rect_main.x, rect_main.y, rect_second.x, rect_second.y);

        if ((rect_main.x <= (rect_second.x + rect_second.w)) && ((rect_main.x + rect_main.w) >= rect_second.x)) // OX check
        {
            //printf("(%d <= %d + %d) && (%d + %d >= %d)\n", rect_main.x, rect_second.x, rect_second.w, rect_main.x, rect_second.x);
            if (((-rect_main.y - rect_main.h + rect_second.y) <= 4) && ((-rect_main.y - rect_main.h + rect_second.y) >= 0)) // OY "laser" check
            {
                //printf("Position before: x:(%d), y:(%d)\n", obj_main->position->x(), obj_main->position->y());
                int magnet = (-rect_main.y - rect_main.h + rect_second.y) - 1; // 1 is a distance between the floor and the object;
                obj_main->position->Push(0, magnet);
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
    rect_main_copy.y += (obj_main->position->velocity_y * obj_main->position->speed) + 1; // I am making prediction of the next move. + 1 is for fall check

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
            
            if (result[0]) //top collision
            {
                //obj_main->position->Push(0, -1 * (obj_main->position->velocity_y * obj_main->position->speed));
                //obj_main->position->velocity_y = 0; 
                obj_main->position->Push(0, result[0] + 2);
                obj_main->position->velocity_y *= -1;
                obj_main->sprite->on_ground = false;
            }

            if ((result[1]) || (result[3])) //right collision or left collision
            {
                //obj_main->position->Push(-1 * (obj_main->position->velocity_x * obj_main->position->speed), 0);
                int d_y = (result[0]) ? result[0] : result[2];
                int d_x = 0;

                d_x = (result[1]) ? result[1] : result[3];

                if (((abs(result[0]) < d_x) || (abs(result[2]) < d_x)) && (abs(d_y) > 1))
                {
                    obj_main->position->Push(-d_x, 0);
                    if ((obj_main->type == 'B') && ((obj_second->type == 'W') || (obj_second->type == 'O')))
                    {
                        obj_main->position->velocity_x = -1 * (obj_main->position->velocity_x); // inverting x velocity when badya hits a window border
                    }      
                }
            }

            if (result[2]) // bottom collision
            {
                //obj_main->position->Push(0, -1 * (obj_main->position->velocity_y * obj_main->position->speed));
                obj_main->sprite->on_ground = true;
                obj_main->position->velocity_y = 0; //stop falling
                if (result[2] > 1)
                {
                    //printf("%d %d %d %d\n", result[0], result[1], result[2], result[3]);
                    obj_main->position->Push(0, -result[2]+1); // push a little bit higher
                }
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
}

Collision::Collision()
{

}
Collision::~Collision()
{

}