#include "Kolo.h"
#include <iostream>
#include <cmath>

Kolo::Kolo(double r)
: r(r)
{
    std::cout << "Konstruktor Kola (" << r << ")" << std::endl;
}

double Kolo::GetR() const
{
    return r;
}
void Kolo::SetR(double r)
{
    this->r = r;
}

double Kolo::Obwod() const
{
    return (2 * M_PI * r);
}

double Kolo::Pole() const
{
    return (M_PI * r * r);
}

void Kolo::Wypisz(std::ostream& out) const {
    std::cout << "Kolo (" << r << ")" << std::endl;
}

Kolo::~Kolo()
{
    std::cout << "Dekonstruktor Kola (" << r << ")" << std::endl;
}