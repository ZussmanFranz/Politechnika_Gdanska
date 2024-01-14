#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y, int speed, char tp, float scale)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    if (objTexture == NULL)
    {
        printf("There is a problem with texture...\n");
    }

    type = tp;

    sprite = new SpriteComponent(objTexture, scale, &srcRect, &destRect, type);    
    position = new PositionComponent(x, y, speed, type, sprite);

    sprite->on_ground = false;
    sprite->on_stairs = false;
    sprite->brutally_murdered = false;
    sprite->exit = false;

    if ((type == 'P') || (type == 'B'))
    {
        position->gravity = Game::GRAVITY;
    }
    else
    {
        position->gravity = 0;
    }
}


void GameObject::Update()
{
    position->update();
    destRect.x = position->x();
    destRect.y = position->y(); 
}

void GameObject::Render()
{
    sprite->draw();
}


GameObject::~GameObject()
{
    delete position;

    if (type == 'P')
    {
        delete keyboard;
    }
    
}
