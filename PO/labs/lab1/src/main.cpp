#include <iostream>
#include "Konus.h"

const int NUMBER_OF_OBJECTS = 4;

int main(void)
{
    std::ostream* out;
    

    FiguraPlaska* figury[NUMBER_OF_OBJECTS];

    figury[0] = new Prostokat(1,5);
    figury[1] = new Trojkat(3.6, 7, 8);
    figury[2] = new Prostokat(6);
    figury[3] = new Kolo(8);

    std::cout << "\nObjects:\n\n";
    for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
    {
        if (figury[i] != nullptr)
        {
            std::cout << *(figury[i]) << "Obwod: " << (figury[i])->Obwod() << "\nPole: " << (figury[i])->Pole() << "\n\n";
        }
    }

    for (int j = 0; j < NUMBER_OF_OBJECTS; j++)
    {
        delete(figury[j]);
    }

    Bryla* konus = new Konus(5, 8);

    std::cout << *konus << "Pole: " << konus->Pole() << "\nObjetosc: " << konus->Objetosc() << "\n\n";

    delete(konus);
}