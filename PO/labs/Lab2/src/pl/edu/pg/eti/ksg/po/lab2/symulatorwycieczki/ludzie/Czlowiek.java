package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.*;

/**
 * @author TB
 */
public abstract class Czlowiek implements Uczestnik {
    
    /**
     * Płeć
     */
    public enum Plec
    {
        /**
         * Kobieta
         */
        KOBIETA,
        
        /**
         * Mężczyzna
         */
        MEZCZYZNA;
    }
    
    
    private final String imie;
    private final String nazwisko;
    private final Plec plec;
    private final double maksymalnaPredkosc;
    private final double czasPelnejRegeneracji;
    private final double czasPelnegoZmeczenia;
    
    private double poziomZmeczenia;

    public Czlowiek(String imie, String nazwisko, Plec plec, double maksymalnaPredkosc) {
        this(imie, nazwisko,plec, maksymalnaPredkosc, 18,18);
    }

    public Czlowiek(String imie, String nazwisko, Plec plec, double maksymalnaPredkosc, double czasPelnejRegeneracji, double czasPelnegoZmeczenia) {
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.plec = plec;
        this.maksymalnaPredkosc = maksymalnaPredkosc;
        this.czasPelnejRegeneracji = czasPelnejRegeneracji;
        this.czasPelnegoZmeczenia = czasPelnegoZmeczenia;
    }
    
    


    public String getImie() {
        return imie;
    }

    public String getNazwisko() {
        return nazwisko;
    }

    public Plec getPlec() {
        return plec;
    }
    
    protected void mow(String wiadomosc) {
        System.out.println(imie+" "+nazwisko+" mówi: " + wiadomosc);
    }

    @Override
    public double getPoziomZmeczenia() {
        return poziomZmeczenia;
    }

    @Override
    public double getBazowaPredkosc() {
        double kondycja = Math.max(1 - poziomZmeczenia, 0);
        return kondycja * maksymalnaPredkosc;
    }

    protected void regeneruj(double czas) {
        double zregenerowano = czas/czasPelnejRegeneracji;
        poziomZmeczenia = Math.max(poziomZmeczenia - zregenerowano, 0);
        System.out.println("Poziom zmęczenia u "+imie+" "+nazwisko+" zmalał o "+zregenerowano+" i wynosi "+ poziomZmeczenia +".");
    }
    
    
    protected void aktualizujZmeczenie(double czas) {
        double dodatkoweZmeczenie = czas/czasPelnegoZmeczenia;
        poziomZmeczenia = Math.min(poziomZmeczenia + dodatkoweZmeczenie, 1.0);
        System.out.println("Poziom zmęczenia u "+imie+" "+nazwisko+" wzrósł o "+dodatkoweZmeczenie +" i wynosi "+ poziomZmeczenia+".");
        
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas) {
        aktualizujZmeczenie(czas);
        mow("Hmm, wędrówka: "+w.getNazwa());
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(imie);
        sb.append(" ").append(nazwisko);
        sb.append(", maksymalnaPredkosc: ")
                .append(maksymalnaPredkosc).append(" GOT/h");
        return sb.toString();
    }

    public void opiszWycieczke(Wycieczka wycieczka) {
        mow("Oto wycieczka: "+ wycieczka.getNazwa());

        mow("Będzie podzielona na "+wycieczka.getLiczbaElementowWycieczki() +" etapów.");
        for(int i=0; i<wycieczka.getLiczbaElementowWycieczki(); i++) {
            ElementWycieczki elementWycieczki = wycieczka.getElementWycieczki(i);
            int lp = i+1;
            if(elementWycieczki instanceof Wedrowka) {
                Wedrowka wedrowka = (Wedrowka) elementWycieczki;
                mow(lp+". Wędrówka: "+wedrowka.getNazwa() + " długość: "+wedrowka.getOdleglosc() + " GOT");
            }
//            else if(elementWycieczki instanceof Atrakcja) {
//                Atrakcja atrakcja = (Atrakcja) elementWycieczki;
//                mow(lp+". Atrakcja: "+atrakcja.getNazwa() + " spędzimy tam " + atrakcja.getWymaganyCzas() + " h");
//            }
            else {
                mow(lp+". Inny element: "+elementWycieczki.getNazwa());
            }
        }

    }
    
    
}
