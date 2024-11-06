#include "FiguraPlaska.h"

class Prostokat : public FiguraPlaska
{
private:
    double a,b;
protected:
    void Wypisz(std::ostream& out) const override;
public:
    Prostokat(double a, double b);
    Prostokat(double c);

    double GetA() const;
    void SetA(double a);

    double GetB() const;
    void SetB(double a);

    double Obwod() const override;
    
    double Pole() const override;

    ~Prostokat() override;
};
