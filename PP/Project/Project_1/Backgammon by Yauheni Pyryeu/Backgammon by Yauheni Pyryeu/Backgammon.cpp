#include<iostream>
#include<curses.h>
#include<ctime>

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
	int possible_moves[4];
};

typedef struct gracz
{
	const char* name;
	int pionki = 15;
	int banda = 0;
	int dwor = 0;
	char kolor = 'W';
	bool real = false;
	bool first;
	bool quit = false;
	int bot_type = 1;
};

void init_game(pole *plansza_obj, gracz* white, gracz* red);
void init_white(pole* plansza_obj, gracz* white);
void init_red(pole* plansza_obj, gracz* red);

void plansza(int y, int x, pole* plansza_obj); //main plansza function
void plansza_borders(int x, int y);
void plansza_pola(int x, int y);
void plansza_numery(int x, int y);
void plansza_pionki(int x, int y, pole* plansza_obj);
void pionek(char stan);
void plus_pionki(int x, int y, pole* plansza_obj, int j);
void plansza_dices(int dice1, int dice2, bool dubl);

void menu_start(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight);
void menu_main(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight);
void menu_main_choice(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight, int options_number);
void menu_play(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight);
void menu_play_choice(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight, int opt_number);
void menu_play_choice_enter(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight);


void game(int y, int x, pole* plansza_obj, gracz* white, gracz* red, bool custom);
void start_dices(int y, int x, pole* plansza_obj, gracz* first, int dice_white, int dice_red);
void ruch_dwoch(int y, int x, pole* plansza_obj, gracz* first, gracz* second, int turn, bool custom);
void ruch(int y, int x, pole* plansza_obj, gracz* player, int turn, bool custom);
void ruch_commands(int y, int x, pole* plansza_obj, gracz* player, int dice1, int dice2, bool dubl, int moves, int turn, bool custom);
void move_pionek(int y, int x, pole* plansza_obj, gracz* player);

int main() {
	initscr();
	//WINDOW* win = newwin(HEIGHT, WIDTH, 0, 0);
	//box(win, 0, 0);

	srand(time(NULL)); //enables random with "random" seed
	start_color();
	init_pair(MATRIX_FILTER, 10, COLOR_BLACK); // 10 - Zielony kolor (jasny)
	init_pair(WHITE_FILTER, 7, COLOR_BLACK); // 7 - Biały kolor
	init_pair(RED_FILTER, 4, COLOR_BLACK); // 4 - Czerwony kolor
	attron(COLOR_PAIR(MATRIX_FILTER)); //color się włączył

	pole plansza_obj[LICZBA_POL];
	gracz white, red;
	white.name = "white";
	red.name = "red";
	char game_name[] = "default";
	init_game(plansza_obj, &white, &red);

	menu_start(2, 0, plansza_obj, &white, &red, 'W', 1, game_name, 0); //gra się zaczyna

	attroff(COLOR_PAIR(MATRIX_FILTER)); //color się wyłączył
	endwin(); //żadnych argumentów!
	return 0;
}


void init_game(pole* plansza_obj, gracz* white, gracz* red)
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

	init_white(plansza_obj, white);
	init_red(plansza_obj, red);
}

void init_white(pole* plansza_obj, gracz *white)
{
	plansza_obj[23].pionki = 2;
	plansza_obj[23].stan = 'W';

	plansza_obj[12].pionki = 5;
	plansza_obj[12].stan = 'W';

	plansza_obj[7].pionki = 3;
	plansza_obj[7].stan = 'W';

	plansza_obj[5].pionki = 5;
	plansza_obj[5].stan = 'W';

	(*white).kolor = 'W';
}
void init_red(pole* plansza_obj, gracz *red)
{
	plansza_obj[0].pionki = 2;
	plansza_obj[0].stan = 'R';

	plansza_obj[11].pionki = 5;
	plansza_obj[11].stan = 'R';

	plansza_obj[16].pionki = 3;
	plansza_obj[16].stan = 'R';

	plansza_obj[18].pionki = 5;
	plansza_obj[18].stan = 'R';

	(*red).kolor = 'R';
}


void plansza(int y, int x, pole* plansza_obj)
{
	clear();
	plansza_borders(y, x);
	plansza_pola(y, x);
	plansza_numery(y, x);
	plansza_pionki(y, x, plansza_obj);
	move(y + HEIGHT + 1, x);
}
void plansza_borders(int y, int x)
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
void plansza_pola(int y, int x)
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
void plansza_numery(int y, int x)
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
void plansza_pionki(int x, int y, pole* plansza_obj)
{
	attroff(COLOR_PAIR(MATRIX_FILTER));
	for (int j = 0; j < LICZBA_POL; j++)
	{
		if (plansza_obj[j].pionki <= 6)
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
		else
		{
			plus_pionki(x, y, plansza_obj, j);
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
void plus_pionki(int x, int y, pole* plansza_obj, int j)
{
	for (int p = 0; p < 6; p++)
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

	move(y + plansza_obj[j].y + 6, x + plansza_obj[j].x);
	if (plansza_obj[j].stan == 'W')
	{
		attron(COLOR_PAIR(WHITE_FILTER));
		printw("+%d", (plansza_obj[j].pionki - 6));
		attroff(COLOR_PAIR(WHITE_FILTER));
	}
	else
	{
		attron(COLOR_PAIR(RED_FILTER));
		printw("+%d", (plansza_obj[j].pionki - 6));
		attroff(COLOR_PAIR(RED_FILTER));
	}
}
void plansza_dices(int dice1, int dice2, bool dubl)
{
	printw("Dices: ");
	if (dubl)
	{
		printw("%d, %d, %d, %d\n", dice1, dice1, dice1, dice1);
	}
	else
	{
		printw("%d, %d\n", dice1, dice2);
	}
}


void menu_start(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight)
{
	clear();
	move(y, x);
	printw("\t\t\t_    _          _____  _______     __\n");
	printw("\t\t\t| \\ | |   /\\   |  __ \\| __  \\ \\   / /\n");
	printw("\t\t\t|  \\| |  /  \\  | |__) | |  | \\ \\_/ /\n");
	printw("\t\t\t| . ` | / /\\ \\ | _  / | |  | |\\   /\n");
	printw("\t\t\t| |\\  |/ ____ \\| | \\ \\| |__| | | |\n");
	printw("\t\t\t|_| \\_/ _ / \\_ \\_|  \\_\\_____/  |_ |\n\n");

	printw("\t\t\tby Yauheni Pyryeu\n\t\t\t 201253\n\n\n");
	printw("\t\t\tpress any key\n");
	getch();
	menu_main(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
}

void menu_main(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight)
{
	clear();
	move(y, x);
	const char* options[] = { "New game", "Load game", "Hall of fame", "Quit" };
	int options_number = sizeof(options) / sizeof(options[0]);
	
	for (int i = 0; i < options_number; i++)
	{
		if (i == highlight)
		{
			attron(A_STANDOUT);
			printw("\t%s\n", options[i]);
			attroff(A_STANDOUT);
		}
		else
		{
			printw("\t%s\n", options[i]);
		}
	}

	menu_main_choice(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight, options_number);
}
void menu_main_choice(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight, int options_number)
{
	char choice;
	choice = getch();

	switch (choice)
	{
	case 's':
		highlight++;
		if (highlight == options_number)
		{
			highlight = 0;
		}
		menu_main(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
		break;
	case 'w':
		if (highlight == 0)
		{
			highlight = options_number;
		}
		highlight--;
		menu_main(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
		break;
	case '\n':
		switch (highlight)
		{
		case 0:
			menu_play(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
			break;
		case 1:
			//load game
			break;
		case 2:
			//hall of fame
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void menu_play(int y, int x, pole *plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight)
{
	clear();
	move(y, x);
	
	const char* options[] = {"Start", "Tornament", "Custom game", "My color: ", "Bot level: ", "Game name: ", "Quit"};
	int opt_number = sizeof(options) / sizeof(options[0]);

	for (int i = 0; i < opt_number; i++)
	{
		if (i == highlight)
		{
			attron(A_STANDOUT);
		}

		printw("\t%s", options[i]);

		switch (i)
		{
		case 3:
			printw("%s\n", (kolor == 'W') ? "white" : "red");
			break;
		case 4:
			printw("%d\n", bot_level);
			break;
		case 5:
			printw("%s\n", game_name);
			break;
		default:
			printw("\n");
			break;
		}

		if (i == highlight)
		{
			attroff(A_STANDOUT);
		}
	}
	menu_play_choice(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight, opt_number);
}
void menu_play_choice(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight, int opt_number)
{
	char choice;
	choice = getch();

	switch (choice)
	{
	case 's':
		highlight = (highlight == opt_number - 1) ? 0 : (highlight + 1);
		menu_play(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
		break;
	case 'w':
		highlight = (highlight == 0) ? (opt_number - 1) : (highlight - 1);
		menu_play(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
		break;
	case '\n':
		menu_play_choice_enter(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
		break;
	default:
		break;
	}
}
void menu_play_choice_enter(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight)
{
	switch (highlight)
	{
	case 0:
		(*white).real = (kolor == 'W') ? 1 : 0;
		(*red).real = (kolor == 'R') ? 1 : 0;
		game(y, x, plansza_obj, white, red, false);
		break;
	case 1:
		//turnej
		break;
	case 2:
		//custom game
		break;
	case 3:
		//my color
		kolor = (kolor == 'R') ? 'W' : 'R';
		menu_play(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
		break;
	case 4:
		//bot level
		bot_level = (bot_level == 1) ? (bot_level + 1) : (bot_level - 1);
		menu_play(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
		break;
	case 5:
		//game name
		//printw("\tGame name: ");
		scanw("%s", game_name);
		menu_play(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
		break;
	case 6:
		//quit
		return;
		break;
	default:
		break;
	}
}

void game(int y, int x, pole* plansza_obj, gracz* white, gracz* red, bool custom)
{
	int turn = 1;
	int dice_white = (rand() % 6) + 1, dice_red = (rand() % 6) + 1;

	(*white).first = (dice_white > dice_red) ? 1 : 0;
	(*red).first = ((*white).first) ? 0 : 1;

	gracz* first = ((*white).first) ? white : red;
	gracz* second = ((*red).first) ? white : red;

	start_dices(y, x, plansza_obj, first, dice_white, dice_red);
	
	while (((*white).pionki > 0) && ((*red).pionki > 0) && (!(*white).quit) && (!(*red).quit))
	{
		ruch_dwoch(y, x, plansza_obj, first, second, turn, custom);
		turn++;
	}
	if ((!(*white).quit) && (!(*red).quit))
	{
		printw("%s player has won!\n", ((*white).pionki > 0) ? (*white).name : (*red).name);
	}
}
void start_dices(int y, int x, pole* plansza_obj, gracz *first, int dice_white, int dice_red)
{
	plansza(y, x, plansza_obj);
	printw("White dice: %d\n", dice_white);
	printw("Red dice: %d\n", dice_red);
	printw("%s goes first!\n", (*first).name);
	getch();
}
void ruch_dwoch(int y, int x, pole* plansza_obj, gracz* first, gracz* second, int turn, bool custom)
{
	ruch(y, x, plansza_obj, first, turn, custom);
	ruch(y, x, plansza_obj, second, turn, custom);
}
void ruch(int y, int x, pole* plansza_obj, gracz* player, int turn, bool custom)
{
	int dice1 = (rand() % 6) + 1, dice2 = (rand() % 6) + 1;
	int moves;
	bool dubl;
	if (dice1 == dice2)
	{
		moves = 4;
		dubl = true;
	}
	else
	{
		moves = 2;
		dubl = false;
	}

	if ((*player).real)
	{
		plansza(y, x, plansza_obj);
		printw("Turn: %d\n", turn);
		plansza_dices(dice1, dice2, dubl);

		ruch_commands(y, x, plansza_obj, player, dice1, dice2, dubl, moves, turn, custom);
	}
	else
	{
		//ruch bota
	}
}
void ruch_commands(int y, int x, pole* plansza_obj, gracz* player,int dice1, int dice2, bool dubl, int moves, int turn, bool custom)
{
	char command;
	printw("Your color: %s\nCommands: move (m), save (s), quit (q)\n", ((*player).kolor == 'W') ? "white" : "red");

	scanw("%c", &command);
	switch (command)
	{
	case 'm':
		//possible moves check
		for (int m = 0; m < moves; m++)
		{
			move_pionek(y, x, plansza_obj, player);
			plansza(y, x, plansza_obj);
			printw("Turn: %d\n", turn);
			plansza_dices(dice1, dice2, dubl);
			printw("Your color: %s\n", ((*player).kolor == 'W') ? "white" : "red");
			//skasować wykorzystaną kostkę!!!
		}
		break;
	case 's':
		//save
		(*player).quit = true;
		break;
	case 'q':
		(*player).quit = true;
		break;
	default:
		break;
	}
}
void move_pionek(int y, int x, pole* plansza_obj, gracz* player)
{
	//legal moves check
	char start_str[3], end_str[3];
	int start = 0, end = 0;

	printw("Enter starting position: ");
	scanw("%d", &start);;
	start--; //-1 for index shift

	printw("Enter ending position: ");
	scanw("%d", &end);
	end--; //-1 for index shift
	
	plansza_obj[start].pionki--;
	plansza_obj[end].pionki++;
	plansza_obj[end].stan = plansza_obj[start].stan;
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