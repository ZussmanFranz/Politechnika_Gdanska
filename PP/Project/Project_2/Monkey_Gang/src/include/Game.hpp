#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() {return isRunning;}

    static SDL_Renderer* renderer;
    static SDL_Event event;

    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 768;
    const int PLAYER_SPEED = 3;
    const float PLAYER_SCALE = 0.75;
    const int BADYA_SPEED = 2;
    const float BADYA_SCALE = 0.75;
private:
    int cnt;
    bool isRunning;
    SDL_Window* window;
};
#endif