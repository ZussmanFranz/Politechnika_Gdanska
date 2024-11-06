package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class ZlozenieTransformacji implements Transformacja{
    private int n;
    private Transformacja[] transformacje;

    public ZlozenieTransformacji(Transformacja[] tr)
    {
        this.transformacje = tr;
        this.n = tr.length;
    }

    public int getN() {
        return n;
    }

    public void setTr(Transformacja[] tr) {
        this.transformacje = tr;
        this.n = tr.length;
    }

    @Override
    public Transformacja getTransformacjaOdwrotna() {
        try
        {
            Transformacja[] temp = new Transformacja[n];
            for (int j = 0; j < n; j++)
            {
                temp[j] = transformacje[j];
            }

            for (int i = 0; i < n; i++)
            {
                transformacje[i] = temp[n - 1 - i].getTransformacjaOdwrotna();
            }
            return this;
        }
        catch(BrakTransformacjiOdwrotnejException ex) {
            ex.printStackTrace();
        }

        return null;
    }

    @Override
    public Punkt transformuj(Punkt p) {
        for (int i = 0; i < n; i++)
        {
            p = transformacje[i].transformuj(p);
        }
        return p;
    }

    @Override
    public String toString() {
        String finale = "Złożenie "+n+" transformacyj:";

        for (int i = 0; i < n; i++)
        {
            finale += "\n"+transformacje[i].toString();
        }

        return finale;
    }
}
