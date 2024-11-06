package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class DrewniaCerkiew extends Atrakcja {
    public DrewniaCerkiew(double czas) {
        super(czas);
    }
    public DrewniaCerkiew() {
        super(0.5);
    }

    @Override
    public double modyfikujZmienczenieGrupy(double czas) {
        //Brak modyfikacji
        return czas;
    }


    @Override
    public String getNazwa() {
        return "Drewniana Cerkiew";
    }
}
