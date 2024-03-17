package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class ObrotOS extends Obrot implements Transformacja3D{
    private char os;
    protected double alpha, beta, gamma;

    /*
    x, y or z (in lowercase!)
    * */
    public ObrotOS(char os, double angle){
        super(angle);

        alpha = 0;
        beta = 0;
        gamma = 0;

        switch (os){
            case 'x':
                alpha = Math.toRadians(angle);
                break;
            case 'y':
                beta = Math.toRadians(angle);
                break;
            case 'z':
                gamma = Math.toRadians(angle);
                break;
            default:
                break;
        }

        this.os = os;
    }

    @Override
    public Punkt3D transformuj3D(Punkt3D p) {
        double scale = 100;
        double xN = p.getX(), yN = p.getY(), zN = p.getZ();
            //x
            if (alpha != 0)
            {
                xN = p.getX();
                yN = p.getY()*Math.cos(alpha) - p.getZ()*Math.sin(alpha);
                zN = p.getY()*Math.sin(alpha) + p.getZ()*Math.cos(alpha);
            }

            //y
            if (beta != 0)
            {
                xN = p.getX()*Math.cos(beta) + p.getY()*Math.sin(beta);
                yN = p.getY();
                zN = p.getZ()*Math.cos(beta) - p.getX()*Math.sin(beta);
            }

            //z
            if (gamma != 0)
            {
                xN = p.getX()*Math.cos(gamma) - p.getY()*Math.sin(gamma);
                yN = p.getX()*Math.sin(gamma) + p.getY()*Math.cos(gamma);
                zN = p.getZ();
            }

            xN = Math.round(xN * 100) / 100.0;
            yN = Math.round(yN * 100) / 100.0;
            zN = Math.round(zN * 100) / 100.0;

        return new Punkt3D(xN,yN,zN);
    }
    @Override
    public Transformacja3D getTransformacjaOdwrotna3D() {
        return new ObrotOS(os, -degrees);
    }
    @Override
    public String toString() {
        return "Obrot o kąt "+angle+" radian ("+degrees+") stopni wokół osi "+os+"\n Alpha: "+alpha+" Beta: "+beta+" Gamma: "+gamma;
    }
}
