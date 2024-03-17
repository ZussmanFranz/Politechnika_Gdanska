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

    static void load(int lvl);
    void finish();

    bool running() {return isRunning;}

    static SDL_Renderer* renderer;
    static SDL_Event event;

    static Uint32 FinishTime;
    static Uint32 WorldTime;
    static Uint32 SkipTime;
    static Uint32 delta_B;
    static Uint32 delta_A;
    static Uint32 delta_Frame;

    static int level;
    static const int number_of_levels = 3;

    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 768;

    const int BADYA_DELAY = 400; // number of frames between badya spawns 
    const int NEW_FRAME_DELAY = 6; // number of frames between "animation switches"

    const int PLAYER_SPEED = 4;
    const float PLAYER_SCALE = 0.6; // scale of destination rectangle 
    const int BADYA_SPEED = 4;
    const float BADYA_SCALE = 0.6; // scale of destination rectangle 
    static constexpr float GRAVITY = 0.05f; 

    const int BADYA_SPAWN_X = 96; // Axises of the place where badyas spawn
    const int BADYA_SPAWN_Y = 64; //
private:
    int cnt;
    bool isRunning;
    SDL_Window* window;
};
#endif