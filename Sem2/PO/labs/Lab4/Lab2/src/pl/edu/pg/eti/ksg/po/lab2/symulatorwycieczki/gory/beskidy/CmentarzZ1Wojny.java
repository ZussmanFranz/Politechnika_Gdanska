package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class CmentarzZ1Wojny extends Atrakcja {
    protected String miasto;
    public CmentarzZ1Wojny(double czas, String miasto) {
        super(czas);
        this.miasto = miasto;
    }

    public CmentarzZ1Wojny(String miasto) {
        super(1.0/3);
        this.miasto = miasto;
    }

    @Override
    public double modyfikujZmienczenieGrupy(double czas) {
        //Brak modyfikacji
        return czas;
    }


    @Override
    public String getNazwa() {
        return "Cmętarz pietwszej wojny światowej w mieście "+miasto;
    }
}
