#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y, int speed, char tp, float scale)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    if (objTexture == NULL)
    {
        printf("There is a problem with texture...\n");
    }
    sprite = new SpriteComponent(objTexture, scale, &srcRect, &destRect);    
    position = new PositionComponent(x, y, speed, tp);

    type = tp;

    on_ground = false;
    on_stairs = false;
    brutally_murdered = false;
    exit = false;
}


void GameObject::Update()
{
    position->update();
    destRect.x = position->x();
    destRect.y = position->y(); 
    //printf("x: %d y: %d\n", destRect.x, destRect.y);
    //sprite->frame_update();
}

void GameObject::Render()
{
    sprite->draw();
}


GameObject::~GameObject()
{
}
