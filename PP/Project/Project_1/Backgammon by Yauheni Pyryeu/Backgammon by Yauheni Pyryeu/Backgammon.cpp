#include<iostream>
#include<curses.h>

using namespace std;

#define LICZBA_POL 24
#define LICZBA_PIONKOW 15

#define MATRIX_FILTER 1
#define DARK_FILTER 2

#define PLANSZA_WIDTH 70
#define PLANSZA_HEIGHT 17
#define YOU_SCORE_X 62
#define ME_SCORE_X 68

void plansza(WINDOW *win, int start_x, int start_y);

int main() {
	initscr();
	WINDOW* win = newwin(PLANSZA_HEIGHT, PLANSZA_WIDTH, 0, 0);

	start_color();
	init_pair(MATRIX_FILTER, 10, COLOR_BLACK);
	init_pair(DARK_FILTER, 2, COLOR_BLACK);

	attron(COLOR_PAIR(MATRIX_FILTER));
	plansza(win, 5, 5);
	attroff(COLOR_PAIR(MATRIX_FILTER));

	getch();
	endwin();
	return 0;
}

void plansza(WINDOW *win, int start_y, int start_x)
{
	move(start_x, start_y);
	vline(':', PLANSZA_HEIGHT);

	move(start_x, start_y + 1);
	hline('=', PLANSZA_WIDTH / 2 - 2);

	move(start_x, start_y + PLANSZA_WIDTH / 2 - 1);
	printw("0");
	hline('=', PLANSZA_WIDTH / 2 - 2);

	move(start_x, start_y + (PLANSZA_WIDTH / 2) + (PLANSZA_WIDTH / 2 - 2));
	vline(':', PLANSZA_HEIGHT);

	move(start_x + 1, start_y + 1);
	vline(':', PLANSZA_HEIGHT - 2);

	move(start_x + 1, start_y + PLANSZA_WIDTH - 3);
	vline(':', PLANSZA_HEIGHT - 2);

	move(start_x + PLANSZA_HEIGHT - 1, start_y + 1);
	hline('=', PLANSZA_WIDTH / 2 - 2);

	move(start_x + PLANSZA_HEIGHT - 1, start_y + PLANSZA_WIDTH / 2 - 1);
	printw("0");
	hline('=', PLANSZA_WIDTH / 2 - 2);

	for (int b = 0; b < 3; b++)
	{
		move(start_x + 1, start_y + PLANSZA_WIDTH / 2 - 2 + b);
		vline('|', PLANSZA_HEIGHT - 2);
	}

	for (int i = 3; i < PLANSZA_WIDTH/2 - 5; i += 10)
	{
		move(start_x + 1, start_y + i);
		vline('.', 6);
		move(start_x + 1, start_y + i + 1);
		vline('.', 6);

		attroff(COLOR_PAIR(MATRIX_FILTER));
		attron(COLOR_PAIR(DARK_FILTER));
		move(start_x + 1, start_y + i + 5);
		vline(92, 6); // 92 == '\'
		move(start_x + 1, start_y + i + 6);
		vline(47, 6); // 47 == '/'
		attroff(COLOR_PAIR(DARK_FILTER));
		attron(COLOR_PAIR(MATRIX_FILTER));

		move(start_x + 1, start_y + i + PLANSZA_WIDTH / 2);
		vline('.', 6);
		move(start_x + 1, start_y + i + 1 + PLANSZA_WIDTH / 2);
		vline('.', 6);

		move(start_x + 1, start_y + i + 5 + PLANSZA_WIDTH / 2);
		vline(92, 6); // 92 == '\'
		move(start_x + 1, start_y + i + 6 + PLANSZA_WIDTH / 2);
		vline(47, 6); // 47 == '/'
	}

	for (int j = 8; j < PLANSZA_WIDTH/2 - 5; j += 10)
	{
		move(start_x + 10, start_y + j);
		vline('.', 6);
		move(start_x + 10, start_y + j + 1);
		vline('.', 6);

		move(start_x + 10, start_y + j - 5);
		vline(47, 6); // 47 == '/'
		move(start_x + 10, start_y + j - 4);
		vline(92, 6); // 92 == '\'

		move(start_x + 10, start_y + j + PLANSZA_WIDTH / 2);
		vline('.', 6);
		move(start_x + 10, start_y + j + 1 + PLANSZA_WIDTH / 2);
		vline('.', 6);

		move(start_x + 10, start_y + j - 5 + PLANSZA_WIDTH / 2);
		vline(47, 6); // 47 == '/'
		move(start_x + 10, start_y + j - 4 + PLANSZA_WIDTH / 2);
		vline(92, 6); // 92 == '\'
	}
}


/*
		curses.h instructions:

	1)initscr(); - turns on window
	1.1)WINDOW *win = newwin(height, width, start_y, start_x);

	2)endwin(); - closes the window

	3)refresh(); - refreshes the window

	4)clear(); - clears the window


	5)move(y, x); - moves cursor to (y, x) location. y - lines, x - columns



	6)printw("something"); - prints something on the window

	7)mvprintw(y, x, "something"); - move(y, x) + printw("something")


	8)start_color(); - init color mode

	9)init_pair(index, foreground, background); - set foreground and background color at once and associate them with index

	10)attron(pair number) - turn color pair on

	11)attroff(pair number) - turn color pair off
*/