package Fifo;
// element kolejki
class Element {
    public Element nast = null;
    public String dana;
}

// implementacja kolejki fifo
class Kolejka_fifo {
    Element pocz = null, koniec = null;

    public synchronized void dodaj(String s) { // to juz sekcja krytyczna
        Element e = new Element();
        e.dana = s;
        // dodanie elementu do kolejki
        if (koniec == null) // kolejka pusta
            pocz = e;
        else
            koniec.nast = e;
        e.nast = null;
        // poinformuj czekajacy watek
        notify();
    }

    public synchronized String odczytaj() {
        try { // warunek zmiennej warunkowej
            while (pocz == null)
                wait();
        } catch (InterruptedException e) {
            return null;
        }
        // element do zwrotu
        Element ret = pocz;
        // usuniecie z kolejki
        pocz = pocz.nast;
        // kolejka pusta
        if (pocz == null)
            koniec = null;
        return ret.dana;
    }
}

// Watek korzystajacy z fifo
class Fifo_watek extends Thread {
    Kolejka_fifo f;

    // konstruktor
    Fifo_watek(Kolejka_fifo _f) {
        super();
        f = _f;
    }

    // funkcja watku
    public void run() {
        System.out.println(" Nowy watek ");
        // czytaj z kolejki
        System.out.println(" Watek odczytal " + f.odczytaj());
        System.out.println(" Watek konczy ");
    }
}

// jedyna klasa widoczna na zewnatrz
public class Fifo {
    // poczatek programu
    public static void main(String arg[]) throws Exception {
        System.out.println(" FIFO ");
        // utworz kolejke
        Kolejka_fifo f = new Kolejka_fifo();
        // utworz i uruchom watek
        Fifo_watek w = new Fifo_watek(f);
        w.start();
        // czekaj 5 sek
        Thread.sleep(5000);
        // zapisz do kolejki
        System.out.println(" Pisze do kolejki ");
        f.dodaj(" Hello world ");
        // czekaj 1 sek
        Thread.sleep(1000);
        System.out.println(" Koniec ");
    }
}