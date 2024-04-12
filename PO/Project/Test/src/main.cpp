#include <ncurses.h>
#include "world.h"


const YX FIELD_SIZE = {3, 5};
const YX PADDING = {0, 1};

void draw_interface(world* my_world)
{
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    mvprintw(1, screen_width/2 - 5, "Round is %d", my_world->GetRound());
    mvprintw(0, screen_width/2 - 15, "Yauheni Pyryeu 201253 project");
    mvprintw(screen_height - 1, screen_height/2 - 14, "q - quit, w a s d - controls");
}

int main() {
    initscr();
    start_color();

    int x, y;
    printw("enter world dimensions: ");
    refresh();
    scanw("%d %d", &y, &x);
    clear();

    noecho(); 
    curs_set(0); 

    world* my_world = new world(y,x, FIELD_SIZE, PADDING);

    char input;

    do
    {
        draw_interface(my_world);

        my_world->Update(input);
        my_world->Draw();

        input = getch();
        clear();
    } while (input != 'q');

    //getch();

    delete my_world;
    endwin();
    return 0;
}
