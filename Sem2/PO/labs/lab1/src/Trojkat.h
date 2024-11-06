#include "FiguraPlaska.h"

class Trojkat: public FiguraPlaska
{
private:
    double a,b,c;
protected:
    void Wypisz(std::ostream& out) const override;
public:
    Trojkat(double a, double b, double c);
    Trojkat(double a, double b);
    Trojkat(double a);

    double GetA() const;
    void SetA(double a);

    double GetB() const;
    void SetB(double b);

    double GetC() const;
    void SetC(double c);

    double Obwod() const override;

    double Pole() const override;

    ~Trojkat() override;
};