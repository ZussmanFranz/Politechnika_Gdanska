package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class ZlozenieTransformacji3DTab implements Transformacja3D{
    private int n;
    private Transformacja3D[] transformacje3d;

    public ZlozenieTransformacji3DTab(Transformacja3D[] tr)
    {
        this.transformacje3d = tr;
        this.n = tr.length;
    }

    public int getN() {
        return n;
    }

    public void setTr(Transformacja3D[] tr) {
        this.transformacje3d = tr;
        this.n = tr.length;
    }

    @Override
    public Transformacja3D getTransformacjaOdwrotna3D() {
        try
        {
            Transformacja3D[] temp = new Transformacja3D[n];
            for (int j = 0; j < n; j++)
            {
                temp[j] = transformacje3d[j];
            }

            for (int i = 0; i < n; i++)
            {
                transformacje3d[i] = temp[n - 1 - i].getTransformacjaOdwrotna3D();
            }
            return this;
        }
        catch(BrakTransformacjiOdwrotnejException ex) {
            ex.printStackTrace();
        }

        return null;
    }

    @Override
    public Punkt3D transformuj3D(Punkt3D p) {
        for (int i = 0; i < n; i++)
        {
            p = transformacje3d[i].transformuj3D(p);
            System.out.println(p);
        }
        return p;
    }

    @Override
    public String toString() {
        String finale = "Złożenie "+n+" transformacyj 3D (Tab):";

        for (int i = 0; i < n; i++)
        {
            finale += "\n"+transformacje3d[i].toString();
        }

        return finale;
    }
}
