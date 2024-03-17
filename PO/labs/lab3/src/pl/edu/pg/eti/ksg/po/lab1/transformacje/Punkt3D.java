package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class Punkt3D extends Punkt{
    protected double z;

    public Punkt3D(double x, double y, double z)
    {
        super(x, y);
        this.z = z;
    }

    @Override
    public double getX() {
        return super.getX();
    }

    @Override
    public double getY() {
        return super.getY();
    }

    public double getZ() {
        return z;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Punkt3D)
        {
            Punkt3D other = (Punkt3D)obj;
            return (other.x == x) && (other.y == y) && (other.z == z);
        }
        return false;
    }
    @Override
    public int hashCode() {
        return 69 * Double.hashCode(x) * Double.hashCode(y) * Double.hashCode(z) + 1337;
    }
    @Override
    public String toString() {
        return "The instance of Point class with x = "+x+", y = "+y+" and z = "+z;
    }
}
