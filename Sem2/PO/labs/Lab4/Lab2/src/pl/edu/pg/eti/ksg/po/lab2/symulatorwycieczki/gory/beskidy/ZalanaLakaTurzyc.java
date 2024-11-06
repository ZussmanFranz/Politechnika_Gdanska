package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

public class ZalanaLakaTurzyc extends Wedrowka {
    protected int trudnosc;
    protected double modyfikacja;
    public ZalanaLakaTurzyc(double odleglosc, int trudnosc, double modyfikacja) {
        super(odleglosc);
        this.trudnosc = trudnosc;
        this.modyfikacja = modyfikacja;
    }
    public ZalanaLakaTurzyc(double odleglosc){
        super(odleglosc);
        trudnosc = 1;
        modyfikacja = 1;
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc) {
        //Modyfikacja jest podana w konstruktorze
        return (predkosc*modyfikacja);
    }

    @Override
    public int getTrudnoscNawigacyjna() {
        return trudnosc;
    }

    @Override
    public String getNazwa() {
        return ("Zalana laka turzyc");
    }
}
