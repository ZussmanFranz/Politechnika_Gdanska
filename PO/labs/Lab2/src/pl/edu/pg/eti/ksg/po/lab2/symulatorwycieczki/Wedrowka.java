package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki;

/**
 * Wędrówka
 * @author TB
 */
public abstract class Wedrowka implements ElementWycieczki {
    private double odleglosc;
    
    /**
     * @param odleglosc - długość wędrówki w GOTach
     */
    public Wedrowka(double odleglosc) {
        this.odleglosc = odleglosc;
    }

    public double getOdleglosc() {
        return odleglosc;
    }
    
    /**
     * Metoda odzwierciedla to jak dany teren wpływa na prędkość poruszania się gurpy.
     * @param predkosc
     * @return 
     */
    public abstract double modyfikujPredkoscGrupy(double predkosc);
    
    /**
     * @return Trudność nawigacyjna terenu w skali 1-5 
     */
    public abstract int getTrudnoscNawigacyjna();
}
