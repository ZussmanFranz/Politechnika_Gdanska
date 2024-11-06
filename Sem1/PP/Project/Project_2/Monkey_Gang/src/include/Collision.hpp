#pragma once
#include <SDL2/SDL.h>
#include "GameObject.hpp"

class Collision
{
public:
<<<<<<< HEAD
    static void AABB(SDL_Rect recA, SDL_Rect recB, int result[6]); // [top, right, bottom, left, push_x, push_y]
    bool CollisionDetection(int result[6]);
    void FallManager(GameObject* obj_main, GameObject* obj_second);
=======
    static int* AABB(const SDL_Rect& recA, const SDL_Rect& recB); // [top, right, bottom, left]
    bool CollisionDetection(int result[4]);
>>>>>>> parent of a5a0ea7 (PP jumps almost done)
    void CollisionManager(GameObject* obj_main, GameObject* obj_second);

    Collision();
    ~Collision();
};
