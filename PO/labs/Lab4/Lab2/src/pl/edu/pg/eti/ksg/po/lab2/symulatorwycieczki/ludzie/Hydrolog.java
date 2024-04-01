package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Uczestnik;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.ElektrowniaWodna;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.ZalanaLakaTurzyc;
import java.lang.Math;

public class Hydrolog extends Czlowiek implements Uczestnik {
    protected int pH;
    public Hydrolog(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 3.0);
        pH = 7;
    }
    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 3;
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas) {
        if ((w instanceof ZalanaLakaTurzyc))
        {
            aktualizujZmeczenie(czas);
            mow("Hmm, "+w.getNazwa()+", czas zbadać dno butelki! *dźwięki picia* Hmm, tym razem wpiszę, że pH = "+pH);
            pH = (int)(Math.random() * 10) ;
        }
        else {
            aktualizujZmeczenie(czas);
            mow("Hmm, wędrówka: "+w.getNazwa());
        }
    }

    @Override
    public void reagujNaAtrakcje(Atrakcja a, double czas) {
        if ((a instanceof ElektrowniaWodna))
        {
            regeneruj(czas);
            mow("Hmm, "+a.getNazwa()+", czas zbadać dno butelki! *dźwięki picia* Hmm, tym razem wpiszę, że pH = "+pH);
            pH = (int)(Math.random() * 10) ;
        }
        else {
            regeneruj(czas);
            mow("Hmm, atrakcja: "+a.getNazwa());
        }
    }
}
