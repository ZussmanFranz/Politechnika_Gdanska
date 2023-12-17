#include<iostream>
#include<SDL2/SDL.h>

const int WIDTH = 800, HEIGH = 600;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("HELLO SDL, YOU ARE FINALLY HERE!", 50, 50, WIDTH, HEIGH, SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == NULL)
    {
        std::cout << "cannot create window: " << SDL_GetError() << std::endl;
        return 1; 
    }
    
    SDL_Event windowEvent;

    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}