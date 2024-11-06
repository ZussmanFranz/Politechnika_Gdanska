package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

/**
 * Przejscie na przełaj przez las
 * @author TB
 */
public class Las extends Wedrowka{

    public Las(double odleglosc) {
        super(odleglosc);
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc) {
        return 0.5f * predkosc;
    }

    @Override
    public int getTrudnoscNawigacyjna() {
        return 3;
    }

    @Override
    public String getNazwa() {
        return "Las";
    }
    
    
}
