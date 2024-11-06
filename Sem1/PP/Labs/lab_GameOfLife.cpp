#include<iostream>

using namespace std;

const int MAX = 10;

void read_data(char board[MAX][MAX], int sizeX, int sizeY)
{
	char character;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			character = cin.get();
			if (character == ' ')
			{
				board[i][j] = 'X';
			}
			else if (character == '\n')
			{
				j--;
				continue;
			}
			else
			{
				board[i][j] = character;
			}
		}
	}
	return;
}

void write_data(char board[MAX][MAX], int sizeX, int sizeY)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	return;
}

void write_temporary(char board[MAX + 2][MAX + 2], int sizeX, int sizeY)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	return;
}

void zero_border(char board[MAX][MAX], int sizeX, int sizeY, char temporary_board[MAX + 2][MAX + 2])
{
	for (int i = 0; i < sizeY + 2; i++)
	{
		for (int j = 0; j < sizeX + 2; j++)
		{
			if ((i == 0 || i == sizeY + 1) || (j == 0 || j == sizeX + 1))
			{
				temporary_board[i][j] = '0';
			}
			else
			{
				temporary_board[i][j] = board[i - 1][j - 1];
			}
		}
	}

	return;
}

void game(char board[MAX][MAX], int sizeX, int sizeY)
{
	char temporary_board[MAX + 2][MAX + 2];
	zero_border(board, sizeX, sizeY, temporary_board);
	//write_temporary(temporary_board, sizeX + 2, sizeY + 2);

	int alive_count = 0;

	for (int i = 1; i < sizeY + 1; i++)
	{
		for (int j = 1; j < sizeX + 1; j++)
		{
			if (temporary_board[i][j] == 'X')
			{
				continue;
			}
			else
			{
				if (temporary_board[i][j] == '1')
				{
					alive_count = 0;
					for (int a = -1; a < 2; a++)
					{
						for (int b = -1; b < 2; b++)
						{
							if (temporary_board[i + a][j + b] == '1')
							{
								alive_count++;
							}
							//cout << temporary_board[i + a][j + b];
						}
						//cout << endl;
					}
					if (temporary_board[i][j] != '1')
					{
                        alive_count--;
					}
					if (alive_count == 2 || alive_count == 3)
					{
						board[i - 1][j - 1] = '1';
					}
					else
					{
						board[i - 1][j - 1] = '0';
					}
					//cout << alive_count << endl;
					//cout << endl;
				}
				else if (temporary_board[i][j] == '0')
				{
					alive_count = 0;
					for (int a = -1; a < 2; a++)
					{
						for (int b = -1; b < 2; b++)
						{
							if (temporary_board[i + a][j + b] == '1' && b != 0 && a != 0)
							{
								alive_count++;
							}
							//cout << temporary_board[i + a][j + b];
						}
						//cout << endl;
					}
					if (alive_count == 3)
					{
						board[i - 1][j - 1] = '1';
					}
					else
					{
						board[i - 1][j - 1] = '0';
					}
					//cout << alive_count << endl;
					//cout << endl;
				}
			}
		}
	}

	write_data(board, sizeX, sizeY);

	return;
}

int main()
{
	char board[MAX][MAX];
	int sizeX, sizeY;
	char mode;

	cin >> sizeX;
	cin >> sizeY;

	read_data(board, sizeX, sizeY);
	//write_data(board, sizeX, sizeY);

	cin >> mode;
	if (mode == '0')
	{
		game(board, sizeX, sizeY);
	}
	else if (mode == '1')
	{
		int rounds;
		cin >> rounds;

		for (int r = 0; r < rounds; r++)
		{
			game(board, sizeX, sizeY);
		}
	}

	return 0;
}