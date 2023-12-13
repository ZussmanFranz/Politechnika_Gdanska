#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
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
	bool possible_start = false;
	int possible_moves[4][3];
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
	int starts[LICZBA_PIONKOW];
};

void init_game(pole *plansza_obj, gracz* white, gracz* red);
void init_white(pole* plansza_obj, gracz* white);
void init_red(pole* plansza_obj, gracz* red);
void init_starts(pole* plansza_obj);

void plansza(int y, int x, pole* plansza_obj, gracz* player, gracz*inny); //main plansza function
void plansza_borders(int x, int y);
void plansza_pola(int x, int y);
void plansza_numery(int x, int y);
void plansza_pionki(int y, int x, pole* plansza_obj);
void pionek(char stan);
void plus_pionki(int x, int y, pole* plansza_obj, int j);
void plus_p(int filter, pole* plansza_obj, int j);
void plansza_dices(int dice1, int dice2, bool dubl, int moves);
void plansza_banda(int y, int x, gracz* player, gracz* inny);
void plansza_banda_one(int y, int x, gracz* player);
void plansza_dwor(int y, int x, gracz* player, gracz* inny);
void plansza_dwor_one(int y, int x, gracz* player);

void menu_start(int y, int x, pole* plansza_obj, gracz* w, gracz* r, char kol, int b_l, char* g_n, int hl);
void menu_main(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight);
void menu_main_choice(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int hl, int options_number);
void menu_play(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight);
void menu_play_sw(const char* opts[], int opt, int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight);
void menu_play_choice(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight, int opt_number);
void menu_play_choice_enter(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kol, int b_l, char* g_n, int hl);

void game(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char gametype, int turn, bool load);
void game_not_load(int y, int x, pole* plansza_obj, gracz* white, gracz* red);
void start_dices(int y, int x, pole* plansza_obj, gracz* first, int dice_white, int dice_red, gracz* player, gracz* inny);
void ruch_dwoch(int y, int x, pole* plansza_obj, gracz* first, gracz* second, int turn, char gametype);
void ruch(int y, int x, pole* plansza_obj, gracz* player, gracz* inny, int turn, char gametype);
void ruch_commands(int y, int x, pole* plansza_obj, gracz* player, gracz* inny, const char* kolor, int dice1, int dice2, bool dubl, int moves, int turn, char gametype);
void ruch_output(int y, int x, pole* plansza_obj, gracz* player, gracz* inny, const char* kolor, int dice1, int dice2, bool dubl, int moves, int turn);
void move_pionek(int y, int x, int* dice1, int* dice2, bool dubl, pole* plansza_obj, gracz* player, gracz* inny, int* moves);
void move_pionek_wyjście(int* dice1, int* dice2, pole* plansza_obj, gracz* player, int* moves, int start, int end);
void move_pionek_norm(int start, int end, int* dice1, int* dice2, bool dubl, pole* plansza_obj, gracz* player, gracz* inny, int* moves);


void moves_check(int dice1, int dice2, bool dubl, pole* plansza_obj, gracz* player);
void moves_check_dubl(int dice1, int dice2, pole* plansza_obj, int p, gracz* player);
void moves_check_main(int dice1, int dice2, char kolor, pole* plansza_obj, int p, int move_n);
void field_check(int dice, char kolor, char enemy, pole* plansza_obj, int p, int move);
void wyjscie_check(int dice, char kolor, pole* plansza_obj, int p, int move);
void skasuj(int* dice1, int* dice2, int start, int end, pole* plansza_obj, bool dubl, int* moves);
void skasuj_dubl(int* moves, int start, int end, pole* plansza_obj);
//void zbicia_check(gracz* player, pole* plansza_obj);

void starts_zbicia(pole* plansza_obj, gracz* player, int moves);
void starts_normal(pole* plansza_obj, gracz* player, int moves);
bool starts_check(pole* plansza_obj, gracz* player, int moves);
void starts_highlight(int y, int x, pole* plansza_obj, gracz* player, int moves);
void moves_highlight(int y, int x, pole* plansza_obj, int moves, int start);
void highlight(int y, int x, pole* plansza_obj, int pole);
void highlight_home(int y, int x);

//start moves array commands
void starts_append(gracz* player, int pole);
void starts_reset(gracz* player);

int wartosc_bezwzgledna(int number);
void save_ruch(pole* plansza_obj, gracz* player, gracz* inny, int turn);

void load(int y, int x, pole* plansza_obj, gracz* white, gracz* red);
void load_game(pole* plansza_obj, gracz* player, gracz* inny, int* turn);
void load_players(gracz* p, gracz* i, char f_k);






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

	menu_start(3, 0, plansza_obj, &white, &red, 'W', 1, game_name, 0); //gra się zaczyna

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
			plansza_obj[i].y = HEIGHT - 2;
			plansza_obj[i].x = WIDTH - 6 - (i * 5);
		}
		else if (i < LICZBA_POL/2)
		{
			plansza_obj[i].down = false;
			plansza_obj[i].y = HEIGHT - 2;
			plansza_obj[i].x = (WIDTH / 2) - 6 - ((i - 6) * 5);
		}
		else if (i < (3 * LICZBA_POL/4))
		{
			plansza_obj[i].down = true;
			plansza_obj[i].y = 1;
			plansza_obj[i].x = 3 + ((i - 12) * 5);
		}
		else
		{
			plansza_obj[i].down = true;
			plansza_obj[i].y = 1;
			plansza_obj[i].x = (WIDTH / 2) + 3 + ((i - 18) * 5);
			
		}
	}

	init_white(plansza_obj, white);
	init_red(plansza_obj, red);
	init_starts(plansza_obj);
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
void init_starts(pole* plansza_obj)
{
	for (int p = 0; p < LICZBA_POL; p++)
	{
		plansza_obj[p].possible_start = false;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 1; j < 3; j++)
			{
				plansza_obj[p].possible_moves[i][0] = -1;
				plansza_obj[p].possible_moves[i][j] = 0;
			}
		}
	}
}


void plansza(int y, int x, pole* plansza_obj, gracz * player, gracz * inny)
{
	clear();
	plansza_borders(y, x);
	plansza_pola(y, x);
	plansza_numery(y, x);
	plansza_pionki(y, x, plansza_obj);
	plansza_banda(y, x, player, inny);
	plansza_dwor(y, x, player, inny);
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
void plansza_pionki(int y, int x, pole* plansza_obj)
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
void plus_pionki(int y, int x, pole* plansza_obj, int j)
{
	for (int p = 0; p < 6; p++)
	{
		int p_y = y + 3 + plansza_obj[j].y, p_x = x + plansza_obj[j].x;
		int jump = (plansza_obj[j].down) ? p : (-p);
		move(p_y + jump, p_x - 3);
		pionek(plansza_obj[j].stan);
	}

	if (plansza_obj[j].stan == 'W')
	{
		move(y + plansza_obj[j].y - 3, x + plansza_obj[j].x - 3);
		plus_p(WHITE_FILTER, plansza_obj, j);
	}
	else
	{
		int red_y = (plansza_obj[j].down) ? (y + plansza_obj[j].y + 9) : (y + plansza_obj[j].y - 3);
		move(red_y, x + plansza_obj[j].x - 3);
		plus_p(RED_FILTER, plansza_obj, j);
	}
}
void plus_p(int filter, pole* plansza_obj, int j)
{
	attron(COLOR_PAIR(filter));
	printw("+%d", (plansza_obj[j].pionki - 6));
	attroff(COLOR_PAIR(filter));
}
void plansza_dices(int dice1, int dice2, bool dubl, int moves)
{
	printw("Dices: ");
	if (dubl)
	{
		for (int d = 0; d < moves; d++)
		{
			printw("%d ", dice1);
		}
		printw("\n");
	}
	else
	{
		if (moves == 2)
		{
			printw("%d, %d\n", dice1, dice2);
		}
		else
		{
			printw("%d\n", ((dice1 == 0) ? dice2 : dice1));
		}
	}
}
void plansza_banda(int y, int x, gracz* player, gracz* inny)
{
	plansza_banda_one(y, x, player);
	plansza_banda_one(y, x, inny);
}
void plansza_banda_one(int y, int x, gracz* player)
{
	int jump = (player->kolor == 'W') ? 2 : (-2);
	int filter = (player->kolor == 'W') ? WHITE_FILTER : RED_FILTER;
	attron(COLOR_PAIR(filter));
	move(y + (HEIGHT/2) + jump, x + (WIDTH/2) - 1);
	if (player->banda < 10)
	{
		printw("%d", player->banda);
	}
	else
	{
		printw("9");
		jump += (player->kolor == 'W') ? 1 : (-1);
		move(y + (HEIGHT / 2) + jump, x + (WIDTH / 2) - 1);
		printw("%d", (player->banda - 9));
	}
	attroff(COLOR_PAIR(filter));
	attron(COLOR_PAIR(MATRIX_FILTER));
}
void plansza_dwor(int y, int x, gracz* player, gracz* inny)
{
	plansza_dwor_one(y, x, player);
	plansza_dwor_one(y, x, inny);
}
void plansza_dwor_one(int y, int x, gracz* player)
{
	int jump = (player->kolor == 'W') ? 2 : (-2);
	int filter = (player->kolor == 'W') ? WHITE_FILTER : RED_FILTER;
	attron(COLOR_PAIR(filter));

	move(y + (HEIGHT / 2) + jump, x + WIDTH);
	printw("%d", player->dwor);

	attroff(COLOR_PAIR(filter));
	attron(COLOR_PAIR(MATRIX_FILTER));
}


void menu_start(int y, int x, pole* plansza_obj, gracz* w, gracz* r, char kol, int b_l, char* g_n, int hl)
{
	clear();
	move(y, x);
	printw("\t_    _          _____  _______     __\n");
	printw("\t| \\ | |   /\\   |  __ \\| __  \\ \\   / /\n");
	printw("\t|  \\| |  /  \\  | |__) | |  | \\ \\_/ /\n");
	printw("\t| . ` | / /\\ \\ | _  / | |  | |\\   /\n");
	printw("\t| |\\  |/ ____ \\| | \\ \\| |__| | | |\n");
	printw("\t|_| \\_/ _ / \\_ \\_|  \\_\\_____/  |_ |\n\n");

	printw("\tby Yauheni Pyryeu\n\t\t\t 201253\n\n\n");
	printw("\tpress any key\n");
	getch();
	menu_main(y, x, plansza_obj, w, r, kol, b_l, g_n, hl);
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
void menu_main_choice(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int hl, int options_number)
{
	char choice = getch();

	switch (choice)
	{
	case 's':
		hl++;
		hl = (hl == options_number) ? 0 : hl;
		menu_main(y, x, plansza_obj, white, red, kolor, bot_level, game_name, hl);
		break;
	case 'w':
		hl = (hl == 0) ? options_number : hl;
		hl--;
		menu_main(y, x, plansza_obj, white, red, kolor, bot_level, game_name, hl);
		break;
	case '\n':
		switch (hl)
		{
		case 0:
			menu_play(y, x, plansza_obj, white, red, kolor, bot_level, game_name, hl);
			break;
		case 1:
			//load game
			load(y, x, plansza_obj, white, red);
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
	
	const char* opts[] = {"Start", "Tornament", "Custom game", "My color: ", "Bot level: ", "Game name: ", "Quit"};
	int opt = sizeof(opts) / sizeof(opts[0]);

	menu_play_sw(opts, opt, y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight);
	menu_play_choice(y, x, plansza_obj, white, red, kolor, bot_level, game_name, highlight, opt);
}
void menu_play_sw(const char* opts[], int opt, int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kolor, int bot_level, char* game_name, int highlight)
{
	for (int i = 0; i < opt; i++)
	{
		if (i == highlight)
		{
			attron(A_STANDOUT);
		}

		printw("\t%s", opts[i]);

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
void menu_play_choice_enter(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char kol, int b_l, char* g_n, int hl)
{
	switch (hl)
	{
	case 0:
		(*white).real = (kol == 'W') ? 1 : 0;
		(*red).real = (kol == 'R') ? 1 : 0;
		game(y, x, plansza_obj, white, red, 'N', 1, false);
		break;
	case 1:
		//turnej menu
		break;
	case 2:
		(*white).real = 1;
		(*red).real = 1;
		game(y, x, plansza_obj, white, red, 'C', 1, false);
		break;
	case 3:
		//my color
		kol = (kol == 'R') ? 'W' : 'R';
		menu_play(y, x, plansza_obj, white, red, kol, b_l, g_n, hl);
		break;
	case 4:
		//bot level
		//bot_level = (bot_level == 1) ? (bot_level + 1) : (bot_level - 1);
		menu_play(y, x, plansza_obj, white, red, kol, b_l, g_n, hl);
		break;
	case 5:
		//game name
		scanw("%s", g_n);
		menu_play(y, x, plansza_obj, white, red, kol, b_l, g_n, hl);
		break;
	case 6:
		//quit
		return;
		break;
	default:
		break;
	}
}

void game(int y, int x, pole* plansza_obj, gracz* white, gracz* red, char gametype, int turn, bool load)
{
	if (!load)
	{
		game_not_load(y, x, plansza_obj, white, red);
	}
	gracz* first = ((*white).first) ? white : red;
	gracz* second = ((*red).first) ? white : red;

	while (((*white).pionki > 0) && ((*red).pionki > 0) && (!(*white).quit) && (!(*red).quit))
	{
		ruch_dwoch(y, x, plansza_obj, first, second, turn, gametype);
		turn++;
	}
	if ((!(*white).quit) && (!(*red).quit))
	{
		clear();
		printw("%s player has won!\n", ((*white).pionki > 0) ? (*white).name : (*red).name);
	}
}
void game_not_load(int y, int x, pole* plansza_obj, gracz* white, gracz* red)
{
	gracz* first;
	gracz* second;
	int dice_white = (rand() % 6) + 1, dice_red = (rand() % 6) + 1;

	(*white).first = (dice_white > dice_red) ? 1 : 0;
	(*red).first = ((*white).first) ? 0 : 1;

	first = ((*white).first) ? white : red;
	second = ((*red).first) ? white : red;

	start_dices(y, x, plansza_obj, first, dice_white, dice_red, first, second);
}

void start_dices(int y, int x, pole* plansza_obj, gracz *first, int dice_white, int dice_red, gracz* player, gracz* inny)
{
	plansza(y, x, plansza_obj, player, inny);
	printw("White dice: %d\n", dice_white);
	printw("Red dice: %d\n", dice_red);
	printw("%s goes first!\n", (*first).name);
	getch();
}
void ruch_dwoch(int y, int x, pole* plansza_obj, gracz* first, gracz* second, int turn, char gametype)
{
	ruch(y, x, plansza_obj, first, second, turn, gametype);
	ruch(y, x, plansza_obj, second, first, turn, gametype);
}
void ruch(int y, int x, pole* plansza_obj, gracz* player, gracz* inny, int turn, char gametype)
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
		plansza(y, x, plansza_obj, player, inny);
		plansza_dices(dice1, dice2, dubl, moves);
		const char* kolor = ((*player).kolor == 'W') ? "white" : "red";
		printw("Turn: %d\nYour color: %s\nCommands: move (m), save (s), quit (q)\n", turn, kolor);
		ruch_commands(y, x, plansza_obj, player, inny, kolor, dice1, dice2, dubl, moves, turn, gametype);
	}
	else
	{
		//ruch bota
	}
}
void ruch_commands(int y, int x, pole* plansza_obj, gracz* player, gracz* inny, const char * kolor, int dice1, int dice2, bool dubl, int moves, int turn, char gametype)
{
	char command;

	scanw("%c", &command);
	switch (command)
	{
	case 'm':
		while (moves > 0)
		{
			ruch_output(y, x, plansza_obj, player, inny, kolor, dice1, dice2, dubl, moves, turn);
			move_pionek(y, x, &dice1, &dice2, dubl, plansza_obj, player, inny, &moves);
		}
		break;
	case 's':
		save_ruch(plansza_obj, player, inny, turn);
		(*player).quit = true;
		break;
	case 'q':
		(*player).quit = true;
		break;
	default:
		break;
	}
}
void ruch_output(int y, int x, pole* plansza_obj, gracz* player, gracz* inny, const char* kolor, int dice1, int dice2, bool dubl, int moves, int turn)
{
	plansza(y, x, plansza_obj, player, inny);
	printw("Turn: %d\nYour color: %s\n", turn, kolor);
	plansza_dices(dice1, dice2, dubl, moves);
	moves_check(dice1, dice2, dubl, plansza_obj, player);
	starts_zbicia(plansza_obj, player, moves);
	starts_check(plansza_obj, player, moves);
	starts_highlight(y, x, plansza_obj, player, moves);
}
void move_pionek(int y, int x, int *dice1, int *dice2, bool dubl, pole* plansza_obj, gracz* player, gracz* inny, int *moves)
{
	int start = 0, end = 0;

	mvprintw(y + HEIGHT + 4, x, "Enter starting position: ");
	scanw("%d", &start);
	start--; //-1 for index shift
	
	plansza(y, x, plansza_obj, player, inny);
	moves_highlight(y, x, plansza_obj, *moves, start);

	mvprintw(y + HEIGHT + 5, x, "Enter ending position: ");
	scanw("%d", &end);
	end--; //-1 for index shift

	if (end == 99) // wpisz 100 aby wejść do dworu
	{
		move_pionek_wyjście(dice1, dice2, plansza_obj, player, moves, start, end);
	}
	else
	{
		move_pionek_norm(start, end, dice1, dice2, dubl, plansza_obj, player, inny, moves);
	}
}
void move_pionek_wyjście(int* dice1, int* dice2, pole* plansza_obj, gracz* player, int* moves, int start, int end)
{
	plansza_obj[start].pionki--;
	player->dwor++;
	player->pionki--;
	int dystans = (player->kolor == 'W') ? (start) : (24 - start);
	if ((dystans > *dice1) && (dystans > *dice2) && (dice1 != dice2))
	{
		*dice1 = 0;
		*dice2 = 0;
		(*moves) -= 2;
	}
	else if (dice1 == dice2)
	{
		(*moves) -= dystans / *dice1;
	}
	else
	{
		(*moves)--;
		if (*dice1 >= dystans)
		{
			*dice1 = 0;
		}
		else
		{
			*dice2 = 0;
		}
	}
}
void move_pionek_norm(int start, int end, int* dice1, int* dice2, bool dubl, pole* plansza_obj, gracz* player, gracz* inny, int* moves)
{
	bool zbicie = (plansza_obj[end].stan == inny->kolor) ? 1 : 0;
	if (zbicie)
	{
		inny->banda += plansza_obj[end].pionki;
		inny->pionki--;
		plansza_obj[end].pionki = 0;
	}
	plansza_obj[start].pionki--;
	plansza_obj[end].pionki++;
	plansza_obj[end].stan = plansza_obj[start].stan;
	if (plansza_obj[start].pionki <= 0)
	{
		plansza_obj[start].pionki = 0;
		plansza_obj[start].stan = 'E';
	}


	skasuj(dice1, dice2, start, end, plansza_obj, dubl, moves);
}

void moves_check(int dice1, int dice2, bool dubl, pole* plansza_obj, gracz* player)
{
	dice1 = (player->kolor == 'W') ? (-dice1) : dice1;
	dice2 = (player->kolor == 'W') ? (-dice2) : dice2;

	init_starts(plansza_obj);
	for (int p = 0; p < LICZBA_POL; p++)
	{
		if (plansza_obj[p].stan == (*player).kolor)
		{
			plansza_obj[p].possible_start = true;
			if (dubl)
			{
				moves_check_dubl(dice1, dice2, plansza_obj, p, player);
			}
			else
			{
				moves_check_main(dice1, dice2, (player->kolor), plansza_obj, p, 0);
			}
		}
		else
		{
			plansza_obj[p].possible_start = false;
		}
	}
}
void moves_check_dubl(int dice1, int dice2, pole* plansza_obj, int p, gracz* player)
{
	char enemy = (player->kolor == 'W') ? 'R' : 'W';
	bool zbicie;
	for (int d = 1; d <= 4; d++)
	{
		zbicie = ((plansza_obj[p + (dice1 * d)].stan == enemy) && (plansza_obj[p + (dice1 * d)].pionki == 1)) ? 1 : 0;
		if (((p + (dice1 * d)) < 24) && ((p + (dice1 * d)) >= 0))
		{
			plansza_obj[p].possible_moves[d - 1][0] = ((plansza_obj[p + (dice1 * d)].stan != enemy) || zbicie) ? (p + (dice1 * d)) : (-1);
			plansza_obj[p].possible_moves[d - 1][1] = d; //cost of moves
		}
		else
		{
			plansza_obj[p].possible_moves[d - 1][0] = 100;
			plansza_obj[p].possible_moves[d - 1][2] = 2;
			plansza_obj[p].possible_moves[d - 1][1] = d;
		}
	}
}
void moves_check_main(int dice1, int dice2, char kolor, pole* plansza_obj, int p, int move_n)
{
	char enemy = (kolor == 'W') ? 'R' : 'W';

	if (dice1 != 0)
	{
		field_check(dice1, kolor, enemy, plansza_obj, p, move_n);
		if (plansza_obj[p].possible_moves[move_n][0] != (-1))
		{
			moves_check_main(0, dice2, kolor, plansza_obj, (p + dice1), move_n + 1);
		}
	}
	if (dice2 != 0)
	{
		field_check(dice2, kolor, enemy, plansza_obj, p, move_n + 2);
		if (plansza_obj[p].possible_moves[move_n + 2][0] != (-1))
		{
			moves_check_main(dice1, 0, kolor, plansza_obj, (p + dice2), move_n + 3);
		}
	}
}
void field_check(int dice, char kolor, char enemy, pole* plansza_obj, int p, int move)
{
	bool zbicie = ((plansza_obj[p + dice].stan == enemy) && (plansza_obj[p + dice].pionki == 1)) ? 1 : 0;
	bool wyjscie = (((p + dice) >= LICZBA_POL) || ((p + dice) < 0)) ? 1 : 0;
	if (wyjscie)
	{
		wyjscie_check(dice, kolor, plansza_obj, p, move);
	}
	else if ((plansza_obj[p + dice].stan != enemy) || zbicie)
	{
		plansza_obj[p].possible_moves[move][0] = p + dice;
		plansza_obj[p].possible_moves[move][1] = (move % 2) + 1;
		plansza_obj[p].possible_moves[move][2] = (zbicie) ? 1 : 0;
	}
	else
	{
		plansza_obj[p].possible_moves[move][0] = -1; // -1 znaczy brak możliwości ruchu
	}
}
void wyjscie_check(int dice, char kolor, pole* plansza_obj, int p, int move)
{
	/*if (kolor == 'W')
	{
		for (int pole = 23; pole > 5; pole--)
		{
			if (plansza_obj[pole].stan == 'W')
			{
				plansza_obj[p].possible_moves[move][0] = -1;// są jeszcze pionki poza domem
				plansza_obj[p].possible_moves[move][1] = 0;
				plansza_obj[p].possible_moves[move][2] = 0;
				return;
			}
		}
	}
	else
	{
		for (int pole = 0; pole < 18; pole++)
		{
			if (plansza_obj[pole].stan == 'R')
			{
				plansza_obj[p].possible_moves[move][0] = -1;// są jeszcze pionki poza domem
				plansza_obj[p].possible_moves[move][1] = 0;
				plansza_obj[p].possible_moves[move][2] = 0;
				return;
			}
		}
	}*/
	plansza_obj[p].possible_moves[move][0] = 100; // oznacza wyjście na dwór
	plansza_obj[p].possible_moves[move][1] = (move % 2) + 1;
	plansza_obj[p].possible_moves[move][2] = 2; 
}
void skasuj(int * dice1, int *dice2, int start, int end, pole * plansza_obj, bool dubl, int *moves)
{
	if (dubl)
	{
		skasuj_dubl(moves, start, end, plansza_obj);
	}
	else
	{
		for (int s = 0; s < 4; s++)
		{
			if (plansza_obj[start].possible_moves[s][0] == end)
			{
				int koszt = plansza_obj[start].possible_moves[s][1];
				if (koszt == 1)
				{
					int dystans = end - start;
					dystans = wartosc_bezwzgledna(dystans);
					*dice1 = ((*dice1) == dystans) ? 0 : (*dice1);
					*dice2 = ((*dice2) == dystans) ? 0 : (*dice2);
					(*moves)--;
					//wykorzystana kostka została skasowana
				}
				else if (koszt == 2)
				{
					*dice1 = 0;
					*dice2 = 0;
					*moves -= 2;
					//wszystkie kostki zostały skasowane
				}
				break;
			}
		}
	}
}
void skasuj_dubl(int* moves, int start, int end, pole* plansza_obj)
{
	for (int s = 0; s < 4; s++)
	{
		if (plansza_obj[start].possible_moves[s][0] == end)
		{
			int koszt = plansza_obj[start].possible_moves[s][1];
			*moves -= koszt;
			break;
		}
	}
}

void starts_zbicia(pole* plansza_obj, gracz* player, int moves)
{
	starts_reset(player);
	int zbicia = 0;
	for (int p = 0; p < LICZBA_POL; p++)
	{
		if ((plansza_obj[p].stan == (*player).kolor) && (plansza_obj[p].possible_start))
		{
			for (int z = 0; z < 4; z++)
			{
				if (plansza_obj[p].possible_moves[z][2] == 1) 
				{
					zbicia++;
					starts_append(player, p);
				}
			}
		}
	}

	if (zbicia <= 0) //zbić nie było
	{
		starts_normal(plansza_obj, player, moves);
	}
}
void starts_normal(pole* plansza_obj, gracz* player, int moves)
{
	starts_reset(player);
	for (int p = 0; p < LICZBA_POL; p++)
	{
		if ((plansza_obj[p].stan == (*player).kolor) && (plansza_obj[p].possible_start))
		{
			for (int z = 0; z < 4; z++)
			{
				if ((plansza_obj[p].possible_moves[z][2] != 1) && (plansza_obj[p].possible_moves[z][0] != -1))
				{
					starts_append(player, p);
				}
			}
		}
	}
}
bool starts_check(pole* plansza_obj, gracz* player, int moves)
{
	bool legal = false;
	for (int st = 0; st < LICZBA_PIONKOW; st++)
	{
		if (player->starts[st] != -1)
		{
			for (int c = 0; c < 4; c++)
			{
				if (plansza_obj[player->starts[st]].possible_moves[c][0] != -1)
				{
					legal = true;
				}
			}
			player->starts[st] = (legal) ? (player->starts[st]) : (-1);
		}
	}
	if (legal)
	{
		return true;
	}
	return false;
}
void starts_highlight(int y, int x, pole* plansza_obj, gracz* player, int moves)
{
	for (int s = 0; s < LICZBA_PIONKOW; s++)
	{
		if (player->starts[s] != -1)
		{
			highlight(y, x, plansza_obj, player->starts[s]);
		}
	}
}
void moves_highlight(int y, int x, pole* plansza_obj, int moves, int start)
{
	int zbicia = 0, koszt;
	for (int m = 0; m < 4; m++)
	{
		koszt = plansza_obj[start].possible_moves[m][1];
		if ((plansza_obj[start].possible_moves[m][2] == 1) && (koszt <= moves))
		{
			zbicia++;
			highlight(y, x, plansza_obj, plansza_obj[start].possible_moves[m][0]);
		}
	}

	if (zbicia == 0)
	{
		for (int n = 0; n < 4; n++)
		{
			koszt = plansza_obj[start].possible_moves[n][1];
			if (plansza_obj[start].possible_moves[n][2] == 2)
			{
				highlight_home(y, x);
			}
			else if ((plansza_obj[start].possible_moves[n][0] != (-1)) && (koszt <= moves))
			{
				highlight(y, x, plansza_obj, plansza_obj[start].possible_moves[n][0]);
			}
		}
	}
}
void highlight(int y, int x, pole* plansza_obj, int pole)
{
	int jump = (plansza_obj[pole].down) ? (-2) : 2;
	move(y + plansza_obj[pole].y + jump, x + plansza_obj[pole].x);
	attron(A_STANDOUT);
	printw("%d", (pole + 1));
	attroff(A_STANDOUT);
	//attron(MATRIX_FILTER);
	move(HEIGHT + 5, 0);
}
void highlight_home(int y, int x)
{
	move(y + (HEIGHT/2), x + WIDTH);
	attron(COLOR_PAIR(A_STANDOUT));
	printw("[HOME!!!]");
	attroff(COLOR_PAIR(A_STANDOUT));
	attron(COLOR_PAIR(MATRIX_FILTER));
}

//start moves array commands
void starts_append(gracz* player, int pole)
{
	for (int i = 0; i < LICZBA_POL; i++)
	{
		if (player->starts[i] == -1)
		{
			player->starts[i] = pole;
			break;
		}
	}
	return;
}
void starts_delete(gracz* player, int pole)
{
	int start = 0;
	while (player->starts[start] != -1)
	{
		if (player->starts[start] == pole)
		{
			int shift = start;
			player->starts[start] = -1;
			while (player->starts[shift + 1] != -1)
			{
				player->starts[shift] = player->starts[start + 1];
				shift++;
			}
			break;
		}
		else
		{
			start++;
		}
	}
}
void starts_reset(gracz* player)
{
	for (int i = 0; i < LICZBA_PIONKOW; i++)
	{
		player->starts[i] = -1;
	}
	return;
}

int wartosc_bezwzgledna(int number)
{
	if (number < 0)
	{
		number = (-number);
	}
	return number;
}


void save_ruch(pole *plansza_obj, gracz* player, gracz* inny, int turn)
{
	//char* file_name = game_name;
	//to_txt(file_name);

	FILE* file = fopen("save.txt", "w");

	for (int pole = 0; pole < LICZBA_POL; pole++)
	{
		fprintf(file, "%d ", plansza_obj[pole].pionki);//pionki na polach
	}

	fprintf(file, "\n");

	for (int stan = 0; stan < LICZBA_POL; stan++)
	{
		fprintf(file, "%c ", plansza_obj[stan].stan); // kolor pól
	}

	fprintf(file, "\n%d ",turn); //numer ruchu

	fprintf(file, "%c ", player->kolor); //kolor aktywnego gracza
	fprintf(file, "%c ", (player->first) ? player->kolor : inny->kolor); //kolor pierwszego gracza

	fprintf(file, "%d %d %d ", player->pionki, player->banda, player->dwor);
	fprintf(file, "%d %d %d ", inny->pionki, inny->banda, inny->dwor);

	fclose(file);
	//submit_save(game_name);
}

void load(int y, int x, pole* plansza_obj, gracz* white, gracz* red)
{
	int dice1, dice2, turn;
	load_game(plansza_obj, white, red, &turn);
	game(y, x, plansza_obj, white, red, 'C', turn, true);
}
void load_game(pole* plansza_obj, gracz* player, gracz* inny, int* turn)
{
	FILE* file = fopen("save.txt", "r");

	for (int pole = 0; pole < LICZBA_POL; pole++)
	{
		fscanf(file, "%d ", &(plansza_obj[pole].pionki));//pionki na polach
	}

	for (int stan = 0; stan < LICZBA_POL; stan++)
	{
		fscanf(file, "%c ", &(plansza_obj[stan].stan)); //kolor pól
	}

	fscanf(file, "%d", turn); //numer ruchu

	fscanf(file, " %c", &(player->kolor)); //kolor aktywnego gracza
	char first_k;
	fscanf(file, " %c", &first_k); //kolor pierwszego gracza

	fscanf(file, "%d %d %d %d %d %d ", &(player->pionki), &(player->banda), &(player->dwor), &(inny->pionki), &(inny->banda), &(inny->dwor));
	
	load_players(player, inny, first_k);
	
	/*for (int i = 0; i < 24; i++)
	{
		printw("%d %c ", plansza_obj[i].pionki, plansza_obj[i].stan);
	}
	printw("\n%d ", *turn);
	printw("%c %c ", (player->kolor), ((player->first) ? player->kolor : inny->kolor));
	printw("%d %d %d ", player->pionki, player->banda, player->dwor);
	printw("%d %d %d ", inny->pionki, inny->banda, inny->dwor);
	getch();*/

	fclose(file);
}
void load_players(gracz* p, gracz* i, char f_k)
{
	p->first = ((p->kolor == f_k) ? 1 : 0);
	i->first = ((p->first) ? 0 : 1);
	i->kolor = (p->kolor == 'W') ? 'R' : 'W';
	p->real = true;
	i->real = true;
}


