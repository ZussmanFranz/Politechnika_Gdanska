#include <ncurses.h>
#include "world.h"
#include "organizm.h"

class world;

const YX FIELD_SIZE = {3, 5};
const YX PADDING = {0, 1};

int main() {
    // initscr();
    // start_color();
    // use_default_colors();

    // int x, y;
    // printw("enter world dimensions: ");
    // refresh();
    // scanw("%d %d", &y, &x);
    // clear();

    // while (y < 5 || x < 5) {
    //     printw("minimal world dimension are 5 x 5\nenter world dimensions: ");
    //     refresh();
    //     scanw("%d %d", &y, &x);
    //     clear();
    // }

    // noecho(); 
    // curs_set(0); 

    // world* my_world = new world(y,x, FIELD_SIZE, PADDING);
    world* my_world = new world(FIELD_SIZE, PADDING);

    while (!(my_world->IsOver()))
    {
        my_world->Update();
    }

    my_world->DrawEndscreen();  

    delete my_world;
    //endwin();
    return 0;
}
