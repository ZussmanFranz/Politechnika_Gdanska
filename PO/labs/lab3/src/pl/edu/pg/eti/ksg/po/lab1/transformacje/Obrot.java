package pl.edu.pg.eti.ksg.po.lab1.transformacje;
import java.lang.Math;

public class Obrot implements Transformacja{
    protected double degrees;
    protected double angle;

    /*
    * Taking argument in degrees, transforms it into radians
    * */
    public Obrot(double a)
    {
        this.degrees = a;
        this.angle = Math.toRadians(a);
    }

    @Override
    public Transformacja getTransformacjaOdwrotna() {
        return new Obrot(-degrees);
    }
    @Override
    public Punkt transformuj(Punkt p) {
        double scale = 100;
        return new Punkt( (Math.round((p.getX()*Math.cos(angle) - p.getY()*Math.sin(angle)) * scale)) / scale, (Math.round((p.getX()*Math.sin(angle) + p.getY()*Math.cos(angle)) * scale)) / scale);
    }
    public double getAngle()
    {
        return angle;
    }

    @Override
    public String toString() {
        return "Obrot o kąt "+angle+" radian ("+degrees+") stopni";
    }
}
