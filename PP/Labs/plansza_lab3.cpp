#include<iostream>
#include<cstdlib> //biblioteka dla gry randomowej
#include<Windows.h> //biblioteka dla funkcji Sleep()
#include<stdlib.h> //biblioteka ¿eby odœwie¿aæ konsolê

using namespace std;

#define NUMBER_OF_PLAYERS 4

/*
Instrukcja:
1)Podaæ iloœæ pól
2)Podaæ tryb gry:
	a) S - standardowa
	b) R - randomowa
3)W trybie S korzystaæ z nastêpnych poleceñ:
	a)M - rzut kostki kolejnego gracza (M spacja wynik_rzutu)
	b)P - obecna pozycja wszystkich gracze i ich stan
	c)B - bardziej przyjemny widok planszy :)
*/

typedef struct gracz
{
	bool one = false;
	bool six = false;
	bool start = false;
	int position = 0;
	bool nieparz = false;
};

void ruch(gracz gracze[], int numer_gracza, int max, int dice, char tryb)
{
	if (gracze[numer_gracza].start == true)
	{
		gracze[numer_gracza].position += dice;

		for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
		{
			if ((gracze[numer_gracza].position == gracze[i].position) && (numer_gracza != i))
			{
				gracze[i].one = false;
				gracze[i].six = false;
				gracze[i].start = false;
				gracze[i].position = 0;
				gracze[i].nieparz = false;

				if (tryb == 'R')
				{
					cout << endl << "GRACZ " << i + 1 << "BITY PRZEZ GRACZA " << numer_gracza + 1 << endl;
					Sleep(1000);
				}
			}
		}
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
				if (tryb == 'R')
				{
					cout << " GRACZ " << numer_gracza + 1 << " WYSTARTOWAL" << endl;
					Sleep(1000);
				}
			}
			break;
		default:
			break;
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

void plansza(gracz gracze[], int max)
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
			if (gracze[i].position == l)
			{
				cout << "G" << i + 1;
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

bool end_of_game(gracz gracze[], int max, int* winner_wsk)
{
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if (gracze[i].position >= max)
		{
			*winner_wsk = i + 1;
			return true;
		}
	}
	return false;
}

int main()
{
	gracz gracze[NUMBER_OF_PLAYERS];
	int X, dice, max, numer_gracza = 0, winner = -1;
	int* winner_wsk = &winner;
	char command, tryb;

	cout << "Instrukcja:\n1)Podac ilosc pol\n2)Podac tryb gry : \na) S - standardowa\nb) R - randomowa\n3)W trybie S korzystac z nastêpnych polecen : \n" <<
		"a)M - rzut kostki kolejnego gracza(M spacja wynik_rzutu)\n" <<
		"	b)P - obecna pozycja wszystkich gracze i ich stan\n" <<
		"	c)B - bardziej przyjemny widok planszy : )\n" << endl;

	cin >> X;
	max = X - 1;
	cin >> tryb;
	system("cls");

	if (tryb == 'S')
	{
		do
		{
			cin >> command;

			if (numer_gracza > 3)
			{
				numer_gracza = 0;
			}

			if (command == 'M')
			{
				cin >> dice;
				if (dice < 1 || dice > 6)
				{
					cout << "invalid command" << endl;
					continue;
				}
				else
				{
					ruch(gracze, numer_gracza, max, dice, tryb);
					numer_gracza++;
				}
			}
			else if (command == 'P')
			{
				for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
				{
					cout << gracze[i].position << ' ';
				}
				for (int g = 0; g < NUMBER_OF_PLAYERS; g++)
				{
					cout << gracze[g].start << gracze[g].nieparz;
				}
				cout << endl;
			}
			else if (command == 'B')
			{
				plansza(gracze, max);
			}
			else
			{
				cout << "invalid command" << endl;
				continue;
			}
		} while (!end_of_game(gracze, max, winner_wsk));

		cout << "END OF GAME" << endl;
		plansza(gracze, max);
	}

	if (tryb == 'R')
	{
		int runda = 0;
		srand((unsigned)time(NULL));

		do
		{
			for (numer_gracza = 0; numer_gracza < NUMBER_OF_PLAYERS; numer_gracza++)
			{
				dice = 1 + (rand() % 6);
				cout << "dice: " << dice << endl;
				ruch(gracze, numer_gracza, max, dice, tryb);
			}
			Sleep(1000);
			system("cls");
			plansza(gracze, max);
			Sleep(1000);
			runda++;
		} while (!end_of_game(gracze, max, winner_wsk));

		system("cls");
		cout << "END OF GAME" << endl;
		plansza(gracze, max);
		cout << "GRACZ NUMER " << winner << " - ZWYCIEZCA!" << endl;
		cout << "GRA TRWALA " << runda << " RUND!" << endl;
	}

	return 0;
}