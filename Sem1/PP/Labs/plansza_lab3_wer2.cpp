#include<iostream>
#include<string>
#include<cstdlib> //biblioteka dla gry randomowej
//#include<Windows.h> //biblioteka dla funkcji Sleep()
//#include<stdlib.h> //biblioteka zeby odswiezac konsole

using namespace std;

#define NUMBER_OF_PLAYERS 4

typedef struct gracz
{
	bool one = false;
	bool six = false;
	bool start = false;
	int player_sequence[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	bool alive = true;
	int position = 0;
	int previous_position = -1;
	bool mine = false;
	bool lasso = false;
	bool nieparz = false;
};

typedef struct pole
{
	char type = 0;
	int wall = 0;
	int mine = 0;
};

void move(gracz gracze[], pole board[], int numer_gracza, int max, int dice);
void ruch(gracz gracze[], pole board[], int numer_gracza, int max, int dice, bool custom_sequence, int seq, int sequence[]);
void plansza(gracz gracze[], int max, pole board[]);
bool end_of_game(gracz gracze[], int max, int* winner_wsk, bool* draw_wsk);
bool petla(gracz gracze[], int numer_gracza, pole board[]);


int main()
{
	gracz gracze[NUMBER_OF_PLAYERS];
	bool draw = false;
	bool custom_sequence = false;
	bool random = false;
	float chance, result;
	int dice, max, numer_gracza = 0, winner = -1, mineX, mineY, wallX, wallY, seq = 0, seed, ofiara;
	int* winner_wsk = &winner;
	bool* draw_wsk = &draw;
	int sequence[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	string command, tryb, prompt;
	pole board[20]; //po prostu "maksymalny" rozmiar

	do
	{
		cin >> command;
		
		
		if (numer_gracza > NUMBER_OF_PLAYERS - 1)
		{
			numer_gracza = 0;
		}
		while (!gracze[numer_gracza].alive)
		{
			numer_gracza++;
		}

		//zamiast switch
		if (command == "INIT")
		{
			cin >> max;
			board[max].type = 'F';
			continue;
		}
		else if (command == "MOVE")
		{
			cin >> dice;
			ruch(gracze, board, numer_gracza, max, dice, custom_sequence, seq, sequence);
			numer_gracza++;
			continue;
		}
		else if (command == "ABORT")
		{
			cout << "ABORTED" << endl;
			return 0;
		}
		else if (command == "PRINT")
		{
			cin >> tryb;
			if (tryb == "0")
			{
				for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
				{
					if (gracze[i].alive)
					{
						cout << gracze[i].position << ' ';
					}
					else
					{
						cout << "X ";
					}
				}
				cout << endl;
			}
			else if (tryb == "0+")
			{
				plansza(gracze, max, board);
			}
			else if (tryb == "1")
			{
				for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
				{
					if (gracze[i].alive)
					{
						cout << gracze[i].position << ' ';
					}
					else
					{
						cout << "X ";
					}
				}
				for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
				{
					if (gracze[j].alive)
					{
						if (gracze[j].start)
						{
							cout << 1;
						}
						else
						{
							cout << 0;
						}

						if (gracze[j].nieparz)
						{
							cout << 1;
						}
						else
						{
							cout << 0;
						}
					}
					else
					{
						cout << "XX";
					}
				}
				cout << endl;
			}
			continue;
		}
		else if (command == "MINED")
		{
			cin >> mineX;
			cin >> mineY;
			board[mineX].type = 'M';
			board[mineX].mine = mineY;

			for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
			{
				if (gracze[i].position == mineX)
				{
					gracze[i].mine = true;
					ruch(gracze, board, i, max, 0, custom_sequence, seq, sequence);
				}
			}
			continue;
		}
		else if (command == "INITSEQ")
		{
			cin >> seq;
			if (seq == 0)
			{
				for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
				{
					gracze[i].start = true;
				}
			}
			else if (seq > 0 && seq <= 10)
			{
				custom_sequence = true;
				for (int i = 0; i < seq; i++)
				{
					cin >> dice;
					sequence[i] = dice;
				}
			}
			continue;
		}
		else if (command == "ENBLRAND")
		{
			cin >> seed;
			srand(seed);
			random = true;
		}
		else if (command == "LASSO")
		{
			cin >> prompt;
			
			if (prompt.length() == 1)
			{
				continue;
			}

			ofiara = (int)(prompt[1] - 48);
			--ofiara;
			if ((gracze[ofiara].position - gracze[numer_gracza].position) > 1 || (gracze[ofiara].position - gracze[numer_gracza].position) < -1)
			{
				if (random)
				{
					chance = 1 / (float)(gracze[ofiara].position - gracze[numer_gracza].position);
					result = (float)(1 + rand() % 100) / 100;
					//cout << " chance: " << chance << " result: " << result << endl;
					if (result <= chance)
					{
						gracze[ofiara].lasso = true;
						gracze[numer_gracza].lasso = true;

						if ((gracze[ofiara].position - gracze[numer_gracza].position) > 0)
						{
							move(gracze, board, numer_gracza, max, 1);
							move(gracze, board, ofiara, max, -1);
							//cout << "SUCCES" << endl;
						}
						else if ((gracze[ofiara].position - gracze[numer_gracza].position) < 0)
						{
							move(gracze, board, numer_gracza, max, -1);
							move(gracze, board, ofiara, max, 1);
							//cout << "SUCCES" << endl;
						}
					}
					/*else
					{
						cout << "FAILED" << endl;
					}*/
				}
				else
				{
					if ((gracze[ofiara].position - gracze[numer_gracza].position) > 0)
					{
						move(gracze, board, numer_gracza, max, 1);
						move(gracze, board, ofiara, max, -1);
					}
					else if ((gracze[ofiara].position - gracze[numer_gracza].position) < 0)
					{
						move(gracze, board, numer_gracza, max, -1);
						move(gracze, board, ofiara, max, 1);
					}
				}
			}
			/*else
			{
				cout << "IMPOSSIBLE" << endl;
			}*/
			numer_gracza++;
		}
		else if (command == "WALLED")
		{
			cin >> wallX;
			cin >> wallY;
			board[wallX].type = 'W';
			board[wallX].wall = wallY;
		}
		/*else if (command == "CLEAN")
		{
			system("cls");
		}*/
		else
		{
			cout << "BAD INPUT" << endl;
			return 1;
		}
	} while (!end_of_game(gracze, max, winner_wsk, draw_wsk));

	if (draw == false)
	{
		cout << "P" << *winner_wsk << " won" << endl;
		//plansza(gracze, max, board);
	}
	else
	{
		cout << "DRAW" << endl;
	}

	
	return 0;
}

//funkcje

void move(gracz gracze[], pole board[], int numer_gracza, int max, int dice)
{
	if (petla(gracze, numer_gracza, board))
	{
		if (gracze[numer_gracza].alive)
		{
			cout << 'P' << numer_gracza + 1 << " was defeated by mines" << endl;
			gracze[numer_gracza].alive = false;
			gracze[numer_gracza].mine = false;
			return;
		}
	}

	if (gracze[numer_gracza].mine)
	{
		do
		{
			/*system("cls");
			cout << "GRACZ " << numer_gracza + 1 << " PODRZUCONY PRZEZ MINE!" << endl;
			plansza(gracze, max, board);
			Sleep(1000);*/
			gracze[numer_gracza].position += board[gracze[numer_gracza].position].mine;
			if (gracze[numer_gracza].position == gracze[numer_gracza].previous_position)
			{
				cout << 'P' << numer_gracza + 1 << " was defeated by mines" << endl;
				gracze[numer_gracza].alive = false;
				gracze[numer_gracza].mine = false;
				break;
			}

			if (board[gracze[numer_gracza].position].type == 'M' && gracze[numer_gracza].alive)
			{
				gracze[numer_gracza].mine = true;
				move(gracze, board, numer_gracza, max, dice);
			}
			else
			{
				gracze[numer_gracza].mine = false;
			}
		} while (gracze[numer_gracza].mine);
	}
	else
	{
		if (dice > 0)
		{
			for (int d = 0; d < dice; d++)
			{
				if (board[gracze[numer_gracza].position].type == 'W' && gracze[numer_gracza].lasso == false)
				{
					if (board[gracze[numer_gracza].position].wall > dice)
					{
						break;
					}
				}
				gracze[numer_gracza].position++;
				if (board[gracze[numer_gracza].position].type == 'M' && d == dice - 1)
				{
					gracze[numer_gracza].mine = true;
					gracze[numer_gracza].previous_position = gracze[numer_gracza].position;
					move(gracze, board, numer_gracza, max, dice);
				}
			}
		}
		else if (dice < 0)
		{
			for (int d = 0; d > dice; d--)
			{
				if (board[gracze[numer_gracza].position].type == 'W' && gracze[numer_gracza].lasso == false && (board[gracze[numer_gracza].position].wall > dice))
				{
					break;
				}
				gracze[numer_gracza].position--;
				if (board[gracze[numer_gracza].position].type == 'M' && d == dice + 1)
				{
					gracze[numer_gracza].mine = true;
					move(gracze, board, numer_gracza, max, dice);
				}
			}
		}
	}
	if (board[gracze[numer_gracza].position].type == 'M' && gracze[numer_gracza].alive)
	{
		gracze[numer_gracza].mine = true;
		move(gracze, board, numer_gracza, max, dice);
	}
}

void ruch(gracz gracze[], pole board[], int numer_gracza, int max, int dice, bool custom_sequence, int seq, int sequence[])
{
	if (gracze[numer_gracza].start == true)
	{
		move(gracze, board, numer_gracza, max, dice);
	}

	else
	{
		if (custom_sequence == false)
		{
			if (gracze[numer_gracza].one == true && gracze[numer_gracza].six == false && dice != 6)
			{
				gracze[numer_gracza].one = false;
			}
			else
			{
				switch (dice)
				{
				case 1:
					gracze[numer_gracza].one = true;
					break;
				case 6:
					gracze[numer_gracza].six = true;
					if (gracze[numer_gracza].one == true && gracze[numer_gracza].six == true)
					{
						gracze[numer_gracza].start = true;
					}
					break;
				default:
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < seq; i++)
			{
				if (gracze[numer_gracza].player_sequence[i] == 0 && dice == sequence[i])
				{
					gracze[numer_gracza].player_sequence[i] = dice;
					break;
				}
			}

			for (int check = 0; check < seq; check++)
			{
				if (gracze[numer_gracza].player_sequence[check] == 0 && gracze[numer_gracza].player_sequence[check - 1] == sequence[check - 1])
				{
					break;
				}
				else if (gracze[numer_gracza].player_sequence[check] != sequence[check])
				{
					for (int k = 0; k < seq; k++)
					{
						gracze[numer_gracza].player_sequence[k] = 0;
					}
				}
				else if (check == seq - 1 && gracze[numer_gracza].player_sequence[check] == sequence[check])
				{
					gracze[numer_gracza].start = true;
				}
			}
		}
	}

	if (gracze[numer_gracza].position % 2 != 0)
	{
		gracze[numer_gracza].nieparz = true;
	}
	else
	{
		gracze[numer_gracza].nieparz = false;
	}
}

bool petla(gracz gracze[], int numer_gracza, pole board[])
{
	if ((board[gracze[numer_gracza].position].mine == (- 1) * board[gracze[numer_gracza].position + board[gracze[numer_gracza].position].mine].mine) && board[gracze[numer_gracza].position].mine != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void plansza(gracz gracze[], int max, pole board[])
{
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		for (int j = 0; j < max + 1; j++)
		{
			cout << "-------- ";
		}
		cout << endl;
		for (int l = 0; l < max + 1; l++)
		{
			cout << "|  ";
			if (gracze[i].position == l && gracze[i].alive)
			{
				cout << "G" << i + 1;
			}
			else if (gracze[i].position == l && !gracze[i].alive)
			{
				cout << "X" << i + 1;
			}
			else if (board[l].type != 0)
			{
				cout << '!' << board[l].type;
			}
			else
			{
				cout << "  ";
			}
			cout << "  | ";
		}
		cout << endl;
		for (int e = 0; e < max + 1; e++)
		{
			cout << "-------- ";
		}
		cout << endl;
	}
}

bool end_of_game(gracz gracze[], int max, int* winner_wsk, bool* draw_wsk)
{
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if (gracze[i].position >= max)
		{
			*winner_wsk = i + 1;
			return true;
		}
	}
	for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
	{
		if (gracze[j].alive == true)
		{
			break;
		}
		else if (j == NUMBER_OF_PLAYERS - 1 && gracze[j].alive == false)
		{
			*draw_wsk = true;
			return true;
		}
	}
	return false;
}
