package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;
import java.lang.Math;

public class WietrznaGran extends Wedrowka {
    protected int wiatr;
    public WietrznaGran(double odleglosc) {
        super(odleglosc);
        wiatr = (int)Math.round((Math.random() * 10) % 2);
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc) {
        //Modyfikacja jest randomowa (1.333 albo 0.666)
        predkosc = (wiatr == 1) ? 1.333*predkosc : 0.666*predkosc;
        return predkosc;
    }

    @Override
    public int getTrudnoscNawigacyjna() {
        return 1;
    }

    @Override
    public String getNazwa() {
        return "Wietrzna Gran, wiatr jest " + ((wiatr == 1) ? "dobry":"zły");
    }
}
