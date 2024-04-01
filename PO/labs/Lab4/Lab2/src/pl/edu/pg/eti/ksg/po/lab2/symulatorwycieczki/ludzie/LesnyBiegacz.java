package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Uczestnik;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.CmentarzZ1Wojny;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.DrewniaCerkiew;

public class LesnyBiegacz extends Czlowiek implements Uczestnik {
    public LesnyBiegacz(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 6.0);
    }
    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 3;
    }

    @Override
    public void reagujNaAtrakcje(Atrakcja a, double czas) {
        if (a instanceof CmentarzZ1Wojny)
        {
            regeneruj(czas*2);
            mow("Pamiętam ich: nie umieli tak szybko biegać");
        }
        else {
            regeneruj(czas);
            mow("Hmm, atrakcja: " + a.getNazwa());
        }
    }
}
