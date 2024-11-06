#include<iostream>
using namespace std;

int main() 
{
	int x = 0; // deklaracja i inicjalizacja zmiennej
	cout << x << endl; // 0
	int y = 0; // tylkodeklaracja zmiennej
	cout << y << endl; // b³¹d! wyœwietlony
											// wynik jest
											// przypadkow¹ liczb¹
	return 0;
}