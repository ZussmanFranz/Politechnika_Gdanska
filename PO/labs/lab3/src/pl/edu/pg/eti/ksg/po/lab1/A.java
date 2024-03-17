package pl.edu.pg.eti.ksg.po.lab1;

public class A {
    private int liczba;

    public A(int liczba){
        this.liczba = liczba;
    }

    public void setLiczba(int liczba){
        this.liczba = liczba;
    }

    public int getLiczba(){
        return liczba;
    }

    @Override
    public String toString() {
        return "Instancja klasy A zawierająca liczbę " + liczba;
    }
}
