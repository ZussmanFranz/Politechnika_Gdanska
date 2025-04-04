#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include "GameObject.hpp"

class Collision
{
public:
    static void AABB(SDL_Rect recA, SDL_Rect recB, int result[4]); // [top, right, bottom, left]
    bool CollisionDetection(int result[4]);
    //void FallManager(GameObject* obj_main, GameObject* obj_second);
    void CollisionManager(GameObject* obj_main, GameObject* obj_second);

    Collision();
    ~Collision();
};
