#pragma once
#include <SDL2/SDL.h>
#include "GameObject.hpp"

class Collision
{
public:
    static int* AABB(const SDL_Rect& recA, const SDL_Rect& recB); // [top, right, bottom, left]
    bool CollisionDetection(int result[4]);
    void CollisionManager(GameObject* obj_main, GameObject* obj_second);

    Collision();
    ~Collision();
};
