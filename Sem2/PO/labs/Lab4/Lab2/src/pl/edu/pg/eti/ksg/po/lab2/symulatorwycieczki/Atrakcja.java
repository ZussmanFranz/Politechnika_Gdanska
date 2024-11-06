package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki;

public abstract class Atrakcja implements ElementWycieczki{
    private double czas;

    /**
     * @param czas - długość wędrówki w GOTach
     */
    public Atrakcja(double czas) {
        this.czas = czas;
    }

    public double getCzas() {
        return czas;
    }

    /**
     * Metoda odzwierciedla to jak dana atrakcja wpływa na zmieczenie się grupy.
     * @param czas
     * @return
     */
    public abstract double modyfikujZmienczenieGrupy(double czas);
}
