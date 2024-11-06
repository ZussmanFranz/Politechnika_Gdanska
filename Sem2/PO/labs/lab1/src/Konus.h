#pragma once
#include "Bryla.h"
#include "Figures.h"

class Konus : public Bryla
{ 
private:
    Kolo* podstawa;
    Trojkat* przekroj;
protected:
    void Wypisz(std::ostream& out) const override;
public:
    Konus(double bok_podstawa, double bok_os);
    Konus(double bok);

    Kolo* GetPodstawa() const;
    void SetPodstawa(Kolo* podstawa);

    Trojkat* GetPrzekroj() const;
    void SetPrzekroj(Trojkat* przekroj);

    double Pole() const override;
    
    double Objetosc() const override;

    ~Konus() override;
};
