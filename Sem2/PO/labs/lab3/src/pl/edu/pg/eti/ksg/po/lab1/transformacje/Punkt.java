package pl.edu.pg.eti.ksg.po.lab1.transformacje;

import javax.swing.*;
import java.awt.*;

public class Punkt {
    /*
     * Słowo kluczowe final oznacza, że po pierwszym przypisaniu
     * zawartość pól x oraz y nie może zostać zmieniona
     * w tym miejscu jest to odpowiednik słowa kluczowego const
     * z języka C++.
     */
    protected double x,y;
    public Punkt(double x, double y) {
        this.x = x;
        this.y = y;
    }
    public double getX() {
        return x;
    }
    public double getY() {
        return y;
    }
    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Point)
        {
            Point other = (Point)obj;
            return (other.x == x) && (other.y == y);
        }
        return false;
    }
    @Override
    public int hashCode() {
        return 69 * Double.hashCode(x) * Double.hashCode(y) + 1337;
    }
    @Override
    public String toString() {
        return "The instance of Point class with x = "+x+" and y = "+y;
    }

    /**
     * Początek układu współrzędnych.
     * W tym miejscu słowo kluczowe final oznacza, że statyczne
     * pole klasy Punkt nie może zostać zmienione.
     * Dotyczy to jednak samej referencji, a nie obiektu, na który
     * wskazuje.
     */
    public static final Punkt O = new Punkt(0, 0);
    /**
     * Punkt (1,0) w układzie współrzędnych
     */
    public static final Punkt E_X = new Punkt(1, 0);
    /**
     * Punkt (0,1) w układzie współrzędnych
     */
    public static final Punkt E_Y = new Punkt(0, 1);
}