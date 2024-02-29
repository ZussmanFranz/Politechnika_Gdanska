#include "Prostokat.h"
#include <iostream>

Prostokat::Prostokat(double a, double b)
: a(a), b(b)
{
    std::cout << "Konstruktor Prostokata (" << a <<"," << b << ")" << std::endl;
}
Prostokat::Prostokat(double c)
: a(c), b(c)
{
    std::cout << "Konstruktor Prostokata(kwadrata) (" << a <<"," << b << ")" << std::endl;
}

double Prostokat::GetA() const {
 return a;
}
double Prostokat::GetB() const {
 return b;
}

void Prostokat::SetA(double a)
{
    this->a = a;
}
void Prostokat::SetB(double b)
{
    this->b = b;
}

double Prostokat::Obwod() const {
    //TODO 1 – metoda ma zwracać obwód figury
    return (a * 2 + b * 2);
}
double Prostokat::Pole() const {
    //TODO 2 - metoda ma zwracać pole figury
    return (a * b);
}
void Prostokat::Wypisz(std::ostream& out) const {
    //TODO 3 - metoda ma wypisywać nazwę i parametry figury
    std::cout << "Prostokat (" << a <<"," << b << ")" << std::endl;
    //std::cout << "Pole: " << this->Pole() << " Obwod: " << this->Obwod() << std::endl;
}
Prostokat::~Prostokat() {
    //TODO 4 – destruktor ma drukować na konsoli zawartość obiektu poddawanego destrukcji (W celach diagnostycznych).
    std::cout << "Destruktor Prostokata (" << a <<"," << b << ")" << std::endl;
}
