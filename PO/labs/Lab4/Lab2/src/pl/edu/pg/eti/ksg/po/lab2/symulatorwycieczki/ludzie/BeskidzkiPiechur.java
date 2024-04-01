package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Uczestnik;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.DrewniaCerkiew;

public class BeskidzkiPiechur extends Czlowiek implements Uczestnik {

    public BeskidzkiPiechur(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 4.0, 20, 20);
    }
    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 3;
    }

    @Override
    public void reagujNaAtrakcje(Atrakcja a, double czas) {
        if (a instanceof DrewniaCerkiew)
        {
            regeneruj(czas * 2);
            mow("Prawosławie - to podstawa zdrowego duchu");
        }
        else {
            regeneruj(czas);
            mow("Hmm, atrakcja: " + a.getNazwa());
        }
    }
}
