#pragma once 
#include "Game.hpp"
#include "Components.hpp"

class GameObject
{   
public:
    GameObject(const char* texturesheet, int x, int y, int speed, char type, float scale); // 'P' for player, 'B' for badya, 'O' for obstacle (platform), 'S' for stairs, 'E' for exit, 'A' for antagonist, 'W' for window border
    ~GameObject();

    void Update();
    void Render();
    
    SDL_Rect* GetRect() {return &destRect;}

    SpriteComponent* sprite = nullptr;
    PositionComponent* position = nullptr;
    KeyboardController* keyboard = nullptr;

    char type;
    bool on_ground;
    bool on_stairs;
    bool brutally_murdered;
    bool exit;
private:
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};
