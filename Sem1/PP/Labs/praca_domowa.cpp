#include<iostream>
using namespace std;

int main() 
{
	int x = 0; // deklaracja i inicjalizacja zmiennej
	cout << x << endl; // 0
	int y = 0; // tylkodeklaracja zmiennej
	cout << y << endl; // b��d! wy�wietlony
											// wynik jest
											// przypadkow� liczb�
	return 0;
}