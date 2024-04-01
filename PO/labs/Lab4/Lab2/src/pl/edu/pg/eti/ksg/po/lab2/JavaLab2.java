package pl.edu.pg.eti.ksg.po.lab2;

import java.util.HashSet;
import java.util.Set;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Grupa;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.SymulatorWycieczki;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Uczestnik;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wycieczka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.Droga;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.*;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.Czlowiek;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.PrzewodnikStudencki;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.Student;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.StudentKSG;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.LesnyBiegacz;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.BagiennyBiegacz;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.Hydrolog;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.CzlowiekZKontuzja;

/**
 *
 * @author TB
 */

public class JavaLab2 {
    public static void main(String[] args) {
        Wycieczka w = doDydiowki();
        
        PrzewodnikStudencki przewodnik = new PrzewodnikStudencki("Stefan", "Długonogi", Czlowiek.Plec.MEZCZYZNA);
        Set<Uczestnik> uczestnicy = new HashSet<>();
        uczestnicy.add(new CzlowiekZKontuzja("Alojzy", "Mechanik", Czlowiek.Plec.MEZCZYZNA));
        uczestnicy.add(new Hydrolog("Jan", "Elektronik", Czlowiek.Plec.MEZCZYZNA));
        uczestnicy.add(new LesnyBiegacz("Piotr","Teledetekcyjny", Czlowiek.Plec.MEZCZYZNA));
        uczestnicy.add(new BagiennyBiegacz("Leholas", "Wałęsa", Czlowiek.Plec.MEZCZYZNA));
        
        Grupa g = new Grupa(przewodnik, uczestnicy);
        
        SymulatorWycieczki symulator = new SymulatorWycieczki(g, w);
        
        symulator.symuluj();
    }
    
    public static Wycieczka doDydiowki() {
        Wycieczka ret = new Wycieczka("Do Dydiówki");
        ret.dodajElementWycieczki(new ZalanaLakaTurzyc(1.0));
        ret.dodajElementWycieczki(new WietrznaGran(1.5));
        ret.dodajElementWycieczki(new ElektrowniaWodna(0.5, "Elba"));
        ret.dodajElementWycieczki(new PoleBarszczuSosnowskiego(2.0));
        ret.dodajElementWycieczki(new CmentarzZ1Wojny("Mordor"));
        //ret.dodajElementWycieczki(new Las(2.0));
        //ret.dodajElementWycieczki(new Droga(5.0));
        
        return ret;
    }
   
}
