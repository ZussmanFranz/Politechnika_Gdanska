#pragma once
#include <iostream>
#include "FiguraPlaska.h"

class Bryla
{
protected:
    virtual void Wypisz(std::ostream& out) const = 0;
    friend std::ostream& operator << (std::ostream& os, const Bryla& figura);
public:
    virtual double Pole() const  = 0;
    virtual double Objetosc() const = 0;
    
    virtual ~Bryla();
};