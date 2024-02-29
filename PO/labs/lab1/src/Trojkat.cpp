#include "Trojkat.h"
#include <iostream>
#include <cmath>

Trojkat::Trojkat(double a, double b, double c)
: a(a), b(b), c(c)
{
    std::cout << "Konstruktor Trojkata (" << a <<"," << b << "," << c << ")" << std::endl;
} 
Trojkat::Trojkat(double a, double b)
: a(a), b(b)
{
    this->c = sqrt((a*a) + (b*b));
    std::cout << "Konstruktor Trojkata(prostokatnego) (" << a <<"," << b << "," << c << ")" << std::endl;
}
Trojkat::Trojkat(double a)
: a(a)
{
    this->b = a;
    this->c = sqrt((a*a) + (b*b));
    std::cout << "Konstruktor Trojkata(prostokatnego rownoramiennego) (" << a <<"," << b << "," << c << ")" << std::endl;
}

double Trojkat::GetA() const {
 return a;
}
double Trojkat::GetB() const {
 return b;
}
double Trojkat::GetC() const {
 return c;
}

void Trojkat::SetA(double a)
{
    this->a = a;
}
void Trojkat::SetB(double b)
{
    this->b = b;
}
void Trojkat::SetC(double c)
{
    this->c = c;
}

double Trojkat::Obwod() const {
    //TODO 1 – metoda ma zwracać obwód figury
    return (a + b + c);
}
double Trojkat::Pole() const {
    //TODO 2 - metoda ma zwracać pole figury
    double p = (a + b + c) / 2;
    double pole = sqrt(p * (p - a) * (p - b) * (p - c));
    return (pole);
}
void Trojkat::Wypisz(std::ostream& out) const {
    //TODO 3 - metoda ma wypisywać nazwę i parametry figury
    std::cout << "Trojkat (" << a <<"," << b << "," << c << ")" << std::endl;
    //std::cout << "Pole: " << this->Pole() << " Obwod: " << this->Obwod() << std::endl;
}
Trojkat::~Trojkat() {
    //TODO 4 – destruktor ma drukować na konsoli zawartość obiektu poddawanego destrukcji (W celach diagnostycznych).
    std::cout << "Destruktor Trojkata (" << a <<"," << b << "," << c << ")" << std::endl;
}
