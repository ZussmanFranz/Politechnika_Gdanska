package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class Translacja3D implements Transformacja3D{
    private double dX, dY, dZ;

    public Translacja3D(double dX, double dY, double dZ) {
        this.dX = dX;
        this.dY = dY;
        this.dZ = dZ;
    }

    @Override
    public Transformacja3D getTransformacjaOdwrotna3D() {
        return new Translacja3D(-dX, -dY, -dZ);
    }
    @Override
    public Punkt3D transformuj3D(Punkt3D p) {
        return new Punkt3D(p.getX() + dX, p.getY() + dY, p.getZ() + dZ);
    }
    public double getdX() {
        return dX;
    }
    public double getdY() {
        return dY;
    }
    public double getdZ() { return dZ; }

    @Override
    public String toString() {
        return "Translacja o wektor ("+dX+","+dY+","+dZ+")";
    }
}
