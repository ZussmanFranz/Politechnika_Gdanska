package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wycieczka;


/**
 *
 * @author TB
 */
public class PrzewodnikStudencki extends Student {

    public PrzewodnikStudencki(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 5.0);
    }

    @Override
    public void opiszWycieczke(Wycieczka wycieczka) {
        mow("Szanowna grupo, proszę o uwagę. Teraz opowiem Wam o wycieczce.");
        super.opiszWycieczke(wycieczka);
    }

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 4;
    }
    
}
