#include<iostream>
#include<curses.h>

using namespace std;

#define LICZBA_POL 24
#define LICZBA_PIONKOW 15

/*
		curses.h instructions:

	1)initscr(); - turns on window

	2)endwin(); - closes the window

	3)refresh(); - refreshes the window

	4)clear(); - clears the window


	5)move(y, x); - moves cursor to (y, x) location. y - lines, x - columns



	6)printw("something"); - prints something on the window

	7)mvprintw(y, x, "something"); - move(y, x) + printw("something")

*/

int main() {
	initscr();

	printw("Hello!");

	int c = getch();
	printw("%d", c);
	
	move(2, 2);
	printw("%d", c);

	move(5, 5);
	printw("%d", c);

	getch();
	clear();


	getch();
	endwin();
	return 0;
}