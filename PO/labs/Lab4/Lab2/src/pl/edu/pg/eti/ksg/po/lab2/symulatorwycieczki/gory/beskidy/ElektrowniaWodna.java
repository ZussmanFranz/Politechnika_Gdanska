package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class ElektrowniaWodna extends Atrakcja {
    protected String rzeka;
    public ElektrowniaWodna(double czas, String rzeka) {
        super(czas);
        this.rzeka = rzeka;
    }

    @Override
    public double modyfikujZmienczenieGrupy(double czas) {
        //Brak modyfikacji
        return czas;
    }


    @Override
    public String getNazwa() {
        return "Elektrownia Wodna na rzekie "+rzeka;
    }
}
