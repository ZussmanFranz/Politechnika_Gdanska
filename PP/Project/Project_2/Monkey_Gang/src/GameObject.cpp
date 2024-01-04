#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren)
{
    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet, renderer);
}

void GameObject::Update()
{
    xpos = 0;
    ypos = 0;

    srcRect.h = 64;
    srcRect.w = 64;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = (int)(srcRect.w * 0.75);
    destRect.h = (int)(srcRect.h * 0.75);
}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}


GameObject::~GameObject()
{
}
