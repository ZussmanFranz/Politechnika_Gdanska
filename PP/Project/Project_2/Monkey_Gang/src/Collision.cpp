#include "Collision.hpp"

int* Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) //Axis-Aligned Bounding Box
{
    int result[] = {0, 0, 0, 0};
    if (
        recA.x + recA.w >= recB.x && 
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
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
    return result;
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

    int* result = Collision::AABB((*rect_main), (*rect_second));

    if (Collision::CollisionDetection(result))
    {
        if (result[0] == 1) //top collision
        {
            obj_main->position->Push(0, -1 * (obj_main->position->velocity_y * obj_main->position->speed));
            obj_main->position->velocity_y = -1 * (obj_main->position->velocity_y); // inverting y velocity
        }
        if ((result[1] == 1) || (result[3] == 1)) //right collision or left collision
        {
            obj_main->position->Push(-1 * (obj_main->position->velocity_x * obj_main->position->speed), 0);
            if ((obj_main->type == 'B') && ((obj_second->type == 'O') || (obj_second->type == 'W')))
            {
                obj_main->position->velocity_x = -1 * (obj_main->position->velocity_x); // inverting x velocity when badya hits a wall
            }
            
        }
        if (result[2] == 1) // bottom collision
        {
            obj_main->position->Push(0, -1 * (obj_main->position->velocity_y * obj_main->position->speed));
            obj_main->position->velocity_y = 0; //stop falling
            obj_main->on_ground = true;
        }
        

        if ((obj_main->type == 'P') && (obj_second->type == 'B')) // collision of the player and a badya is detected, so the player is DEAD now
        {
            obj_main->brutally_murdered = true;
            printf("The player has been murdered!\n");
        }
        
        if ((obj_main->type == 'P') && (obj_second->type == 'E')) // the player succesfully escaped
        {
            obj_main->exit = true;
            printf("The player has escaped!\n"); //...from level n
        }
    }
    
}