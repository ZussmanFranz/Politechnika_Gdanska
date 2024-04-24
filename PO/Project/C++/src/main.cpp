#include <cstdio>
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

    bool load = false;

    int x, y;
    printf("Enter \"0 0\" to load an existing game\nenter world dimensions: ");
    scanf("%d %d", &y, &x);
    clear();

    if (y == 0 || x == 0) {
        load = true;
    }

    while ((y < 5 || x < 5) && (!load)) {
        printf("minimal world dimension are 5 x 5\nenter world dimensions: ");
        scanf("%d %d", &y, &x);
        clear();
        if (y == 0 || x == 0) {
            load = true;
        }
    }

    // noecho(); 
    // curs_set(0); 

    // world* my_world = new world(y,x, FIELD_SIZE, PADDING);

    world* my_world = nullptr;
    
    if (load) {
        //load constructor
    }
    else {
        my_world = new world(y,x,FIELD_SIZE, PADDING);
    }

    while (!(my_world->IsOver()))
    {
        my_world->Update();
    }

    my_world->DrawEndscreen();  

    delete my_world;
    //endwin();
    return 0;
}
