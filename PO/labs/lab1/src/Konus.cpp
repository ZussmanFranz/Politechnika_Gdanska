#include "Konus.h"
#include <iostream>
#include <cmath>

Konus::Konus(double bok_podstawa, double bok_os)
{
    std::cout << "Konstruktor Konusu o przekroju i podstawie: ";
    this->przekroj = new Trojkat(bok_podstawa, bok_os);
    this->podstawa = new Kolo(bok_podstawa);
}
Konus::Konus(double bok)
{
    std::cout << "Konstruktor Konusu o przekroju i podstawie: ";
    this->przekroj = new Trojkat(bok);
    this->podstawa = new Kolo(bok);
}

Kolo* Konus::GetPodstawa() const
{
    return podstawa;
}
void Konus::SetPodstawa(Kolo* podstawa)
{
    this->podstawa = podstawa;
}

Trojkat* Konus::GetPrzekroj() const
{
    return przekroj;
}
void Konus::SetPrzekroj(Trojkat* przekroj)
{
    this->przekroj = przekroj;
}

void Konus::Wypisz(std::ostream& out) const
{
    std::cout << "Konus:\n";
    std::cout << "Przekroj (trojkat) (" << this->przekroj->GetA() << "," << this->przekroj->GetB() << "," << this->przekroj->GetC() << ")\n";
    std::cout << "Podstawa (kolo) (" << this->podstawa->GetR() << ")\n";
}

double Konus::Pole() const
{
    return ((M_PI * podstawa->GetR() * przekroj->GetC()) + podstawa->Pole());
}

double Konus::Objetosc() const
{
    return (podstawa->Pole() * przekroj->GetB() / 3);
}

Konus::~Konus()
{
    std::cout << "Dekonstruktor Konusu: ";
    delete(przekroj);
    delete(podstawa);
}