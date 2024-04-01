package pl.edu.pg.eti.ksg.po.lab1.transformacje;

import java.util.ArrayList;

public class ZlozenieTransformacji3DList implements Transformacja3D{
    private int n;
    private ArrayList<Transformacja3D> transformacje3d;

    public ZlozenieTransformacji3DList(ArrayList<Transformacja3D> tr)
    {
        this.transformacje3d = tr;
        this.n = tr.size();
    }

    public int getN() {
        return n;
    }

    public void setTr(ArrayList<Transformacja3D> tr) {
        this.transformacje3d = tr;
        this.n = tr.size();
    }`

    @Override
    public Transformacja3D getTransformacjaOdwrotna3D() {
        try
        {
            ArrayList<Transformacja3D> temp = new ArrayList<Transformacja3D>();

            for (int j = 0; j < n; j++)
            {
                temp.add(transformacje3d.get(j));
            }

            transformacje3d.clear();

            for (int i = 0; i < n; i++)
            {
                transformacje3d.add(temp.get(n - 1 - i).getTransformacjaOdwrotna3D());
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
            p = transformacje3d.get(i).transformuj3D(p);
            System.out.println(p);
        }
        return p;
    }

    @Override
    public String toString() {
        String finale = "Złożenie "+n+" transformacyj 3D (List):";

        for (int i = 0; i < n; i++)
        {
            finale += "\n"+transformacje3d.get(i).toString();
        }

        return finale;
    }
}
