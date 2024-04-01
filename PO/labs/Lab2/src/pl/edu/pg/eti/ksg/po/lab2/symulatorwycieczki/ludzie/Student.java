package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

/**
 *
 * @author TB
 */
public class Student extends Czlowiek{

    public Student(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 4.0);
    }

    protected Student(String imie, String nazwisko, Plec plec, double maksymalnaPredkosc) {
        super(imie, nazwisko, plec, maksymalnaPredkosc);
    }

    protected Student(String imie, String nazwisko, Plec plec, double maksymalnaPredkosc, double czasPelnejRegeneracji, double czasPelnegoZmeczenia) {
        super(imie, nazwisko, plec, maksymalnaPredkosc, czasPelnejRegeneracji, czasPelnegoZmeczenia);
    }
    
    

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 3;
    }
    
    
}
