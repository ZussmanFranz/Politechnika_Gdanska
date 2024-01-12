#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include "GameObject.hpp"

class Collision
{
public:
    static void AABB(SDL_Rect recA, SDL_Rect recB, int result[6]); // [top, right, bottom, left, push_x, push_y]
    bool CollisionDetection(int result[6]);
    void FallManager(GameObject* obj_main, GameObject* obj_second);
    void CollisionManager(GameObject* obj_main, GameObject* obj_second);

    Collision();
    ~Collision();
};
