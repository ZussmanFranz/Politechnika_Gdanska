package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Uczestnik;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.CmentarzZ1Wojny;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.ElektrowniaWodna;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.ZalanaLakaTurzyc;

public class BagiennyBiegacz extends Czlowiek implements Uczestnik {
    public BagiennyBiegacz(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 5.0);
    }
    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 3;
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas) {
        if (w instanceof ZalanaLakaTurzyc)
        {
            aktualizujZmeczenie(czas/2);
            mow(w.getNazwa()+" mi nie straszy!");
        }
        else {
            aktualizujZmeczenie(czas);
            mow("Hmm, wędrówka: "+w.getNazwa());
        }
    }
}
