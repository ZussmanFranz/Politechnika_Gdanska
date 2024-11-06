package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

/**
 *
 * @author TB
 */
public class Droga extends Wedrowka{

    public Droga(double odleglosc) {
        super(odleglosc);
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc) {
        //Brak modyfikacji
        return predkosc;
    }

    @Override
    public int getTrudnoscNawigacyjna() {
        return 1;
    }    

    @Override
    public String getNazwa() {
        return "Droga";
    }
    
}
