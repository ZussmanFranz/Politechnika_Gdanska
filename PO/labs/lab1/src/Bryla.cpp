#include "Bryla.h"

std::ostream& operator << (std::ostream& os, const Bryla& figura)
{
    figura.Wypisz(os);
    return os;
}

Bryla::~Bryla() {
    
}