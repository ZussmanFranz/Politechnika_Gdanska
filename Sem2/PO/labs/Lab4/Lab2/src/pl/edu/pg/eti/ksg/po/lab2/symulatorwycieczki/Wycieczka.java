package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author TB
 */
public class Wycieczka {
    private String nazwa;
    private List<ElementWycieczki> elementy = new ArrayList<>();

    public Wycieczka(String nazwa) {
        this.nazwa = nazwa;
    }
    
    public void dodajElementWycieczki(ElementWycieczki elementWycieczki) {
        elementy.add(elementWycieczki);
    }
    
    /**
     * @return Dlugosc wycieczki w GOTach 
     */
    public double getDlugosc() {
        return elementy.stream()
                .filter(ew -> ew instanceof Wedrowka)
                .map(ew -> (Wedrowka)ew)
                .map(Wedrowka::getOdleglosc)
                .reduce(0.0, Double::sum);
    }
    
//    /**
//     * @return Sumaryczny czas wszystkich atrakcji 
//     */
//    public double getCzasAtrakcji() {
//        return elementy.stream()
//                .filter(ew -> ew instanceof Atrakcja)
//                .map(ew -> (Atrakcja)ew)
//                .map(Atrakcja::getWymaganyCzas)
//                .reduce(0.0, (a,b) -> Double::sum);
//    }
    
    public ElementWycieczki getElementWycieczki(int i) {
        return elementy.get(i);
    }
    
    public int getLiczbaElementowWycieczki() {
        return elementy.size();
    }

    public String getNazwa() {
        return nazwa;
    }
   
    
    @Override
    public String toString() {
        return "Wycieczka \"" + nazwa + "\", długość: "+ getDlugosc() + " GOT,"
                //+ " czas atrakcji: "+getCzasAtrakcji() + " h"
                ;
    }
    
    
}
