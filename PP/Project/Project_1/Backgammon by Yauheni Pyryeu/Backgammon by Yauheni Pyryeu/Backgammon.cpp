#include<iostream>
#include<curses.h>

using namespace std;

#define LICZBA_POL 24
#define LICZBA_PIONKOW 15

#define MATRIX_FILTER 1
#define WHITE_FILTER 2
#define RED_FILTER 3

#define WIDTH 68
#define HEIGHT 17

typedef struct pole
{
	int pionki = 0;
	char stan = 'E';
	int x;
	int y;
	bool down;
};

void init_pola(pole *plansza_obj);
void init_white(pole* plansza_obj);
void init_red(pole* plansza_obj);

void plansza(WINDOW* win, int y, int x, pole* plansza_obj); //main plansza function
void plansza_borders(WINDOW *win, int x, int y);
void plansza_pola(WINDOW* win, int x, int y);
void plansza_numery(WINDOW* win, int x, int y);
void plansza_pionki(WINDOW* win, int x, int y, pole* plansza_obj);
void pionek(char stan);



int main() {
	initscr();
	WINDOW* win = newwin(HEIGHT, WIDTH, 0, 0);

	start_color();
	init_pair(MATRIX_FILTER, 10, COLOR_BLACK); // 10 - Zielony kolor (jasny)
	init_pair(WHITE_FILTER, 7, COLOR_BLACK); // 7 - Biały kolor
	init_pair(RED_FILTER, 4, COLOR_BLACK); // 4 - Czerwony kolor
	attron(COLOR_PAIR(MATRIX_FILTER)); //color się włączył

	pole plansza_obj[LICZBA_POL];
	init_pola(plansza_obj);

	plansza(win, 2, 0, plansza_obj);

	attroff(COLOR_PAIR(MATRIX_FILTER)); //color się wyłączył
	getch(); //oczekiwanie żeby program się nie zamknął od razu
	endwin(); //żadnych argumentów!
	return 0;
}


void init_pola(pole* plansza_obj)
{
	for (int i = 0; i < LICZBA_POL; i++)
	{
		if (i < LICZBA_POL/4)
		{
			plansza_obj[i].down = false;
			plansza_obj[i].y = HEIGHT;
			plansza_obj[i].x = WIDTH - 8 - (i * 5);
		}
		else if (i < LICZBA_POL/2)
		{
			plansza_obj[i].down = false;
			plansza_obj[i].y = HEIGHT;
			plansza_obj[i].x = (WIDTH / 2) - 8 - ((i - 6) * 5);
		}
		else if (i < (3 * LICZBA_POL/4))
		{
			plansza_obj[i].down = true;
			plansza_obj[i].y = 3;
			plansza_obj[i].x = 1 + ((i - 12) * 5);
		}
		else
		{
			plansza_obj[i].down = true;
			plansza_obj[i].y = 3;
			plansza_obj[i].x = (WIDTH / 2) + 1 + ((i - 18) * 5);
			
		}
	}

	init_white(plansza_obj);
	init_red(plansza_obj);
}

void init_white(pole* plansza_obj)
{
	plansza_obj[23].pionki = 2;
	plansza_obj[23].stan = 'W';

	plansza_obj[12].pionki = 5;
	plansza_obj[12].stan = 'W';

	plansza_obj[7].pionki = 3;
	plansza_obj[7].stan = 'W';

	plansza_obj[5].pionki = 5;
	plansza_obj[5].stan = 'W';
}
void init_red(pole* plansza_obj)
{
	plansza_obj[0].pionki = 2;
	plansza_obj[0].stan = 'R';

	plansza_obj[11].pionki = 5;
	plansza_obj[11].stan = 'R';

	plansza_obj[16].pionki = 3;
	plansza_obj[16].stan = 'R';

	plansza_obj[18].pionki = 5;
	plansza_obj[18].stan = 'R';
}


void plansza(WINDOW* win, int y, int x, pole* plansza_obj)
{
	plansza_borders(win, y, x);
	plansza_pola(win, y, x);
	plansza_numery(win, y, x);
	plansza_pionki(win, y, x, plansza_obj);
}

void plansza_borders(WINDOW *win, int y, int x)
{
	move(y, x);
	vline(':', HEIGHT);

	move(y, x + 1);
	hline('=', WIDTH / 2 - 2);

	move(y, x + WIDTH / 2 - 1);
	printw("0");
	hline('=', WIDTH / 2 - 2);

	move(y, x + (WIDTH / 2) + (WIDTH / 2 - 2));
	vline(':', HEIGHT);

	move(y + 1, x + 1);
	vline(':', HEIGHT - 2);

	move(y + 1, x + WIDTH - 3);
	vline(':', HEIGHT - 2);

	move(y + HEIGHT - 1, x + 1);
	hline('=', WIDTH / 2 - 2);

	move(y + HEIGHT - 1, x + WIDTH / 2 - 1);
	printw("0");
	hline('=', WIDTH / 2 - 2);

	for (int b = 0; b < 3; b++)
	{
		move(y + 1, x + WIDTH / 2 - 2 + b);
		vline('|', HEIGHT - 2);
	}

	//BAR label
	move(y + HEIGHT/2, x + WIDTH/2 - 3);
	printw("[BAR]");

	//HOME label
	move(y + HEIGHT/2, x + WIDTH);
	printw("[HOME]");
}

void plansza_pola(WINDOW* win, int y, int x)
{
	for (int i = 3; i < WIDTH / 2 - 5; i += 10)
	{
		//move(y + 1, x + i);
		mvvline(y + 1, x + i, '.', 6);
		//move(y + 1, x + i + 1);
		mvvline(y + 1, x + i + 1, '.', 6);

		//move(y + 1, x + i + 5);
		mvvline(y + 1, x + i + 5, 92, 6); // 92 == '\'
		//move(y + 1, x + i + 6);
		mvvline(y + 1, x + i + 6, 47, 6); // 47 == '/'

		//move(y + 1, x + i + WIDTH / 2);
		mvvline(y + 1, x + i + WIDTH / 2, '.', 6);
		//move(y + 1, x + i + 1 + WIDTH / 2);
		mvvline(y + 1, x + i + 1 + WIDTH / 2, '.', 6);

		//move(y + 1, x + i + 5 + WIDTH / 2);
		mvvline(y + 1, x + i + 5 + WIDTH / 2, 92, 6); // 92 == '\'
		//move(y + 1, x + i + 6 + WIDTH / 2);
		mvvline(y + 1, x + i + 6 + WIDTH / 2, 47, 6); // 47 == '/'
	}

	for (int j = 8; j < WIDTH/2 - 5; j += 10)
	{
		//move(y + 10, x + j);
		mvvline(y + 10, x + j, '.', 6);
		//move(y + 10, x + j + 1);
		mvvline(y + 10, x + j + 1, '.', 6);

		//move(y + 10, x + j - 5);
		mvvline(y + 10, x + j - 5, 47, 6); // 47 == '/'
		//move(y + 10, x + j - 4);
		mvvline(y + 10, x + j - 4, 92, 6); // 92 == '\'

		//move(y + 10, x + j + WIDTH / 2);
		mvvline(y + 10, x + j + WIDTH / 2, '.', 6);
		//move(y + 10, x + j + 1 + WIDTH / 2);
		mvvline(y + 10, x + j + 1 + WIDTH / 2, '.', 6);

		//move(y + 10, x + j - 5 + WIDTH / 2);
		mvvline(y + 10, x + j - 5 + WIDTH / 2, 47, 6); // 47 == '/'
		//move(y + 10, x + j - 4 + WIDTH / 2);
		mvvline(y + 10, x + j - 4 + WIDTH / 2, 92, 6); // 92 == '\'
	}
}

void plansza_numery(WINDOW* win, int y, int x)
{
	for (int n1 = 0; n1 < 6; n1++)
	{
		move(y + HEIGHT, x + WIDTH - 6 - (n1 * 5));
		printw("%d", n1 + 1);

		move(y + HEIGHT, x + (WIDTH / 2) - 6 - (n1 * 5));
		printw("%d", n1 + 7);
	}

	for (int n2 = 12, krok = 0; n2 < 18; n2++, krok++)
	{
		move(y - 1, x + 3 + (krok * 5));
		printw("%d", n2 + 1);

		move(y - 1, x + 3 + (WIDTH/2) + (krok * 5));
		printw("%d", n2 + 7);
	}
}

void plansza_pionki(WINDOW* win, int x, int y, pole* plansza_obj)
{
	attroff(COLOR_PAIR(MATRIX_FILTER));
	for (int j = 0; j < LICZBA_POL; j++)
	{
		for (int p = 0; p < plansza_obj[j].pionki; p++)
		{
			if (plansza_obj[j].down)
			{
				move(y + plansza_obj[j].y + p, x + plansza_obj[j].x);
				pionek(plansza_obj[j].stan);
			}
			else
			{
				move(y + plansza_obj[j].y - p, x + plansza_obj[j].x);
				pionek(plansza_obj[j].stan);
			}
		}
	}
	attron(COLOR_PAIR(MATRIX_FILTER));
}

void pionek(char stan)
{
	if (stan == 'W')
	{
		attron(COLOR_PAIR(WHITE_FILTER));
		printw("<>");
		attroff(COLOR_PAIR(WHITE_FILTER));
	}
	else
	{
		attron(COLOR_PAIR(RED_FILTER));
		printw("<>");
		attroff(COLOR_PAIR(RED_FILTER));
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