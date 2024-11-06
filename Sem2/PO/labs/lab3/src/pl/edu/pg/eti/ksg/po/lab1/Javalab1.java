package pl.edu.pg.eti.ksg.po.lab1;
import pl.edu.pg.eti.ksg.po.lab1.transformacje.*;

import java.util.ArrayList;

//import java.util.Scanner;
public class Javalab1 {
    public static void main(String[] args)
    {
        System.out.println("================Zlozenie 3D Tab================");
        try {
            Punkt3D p1 = new Punkt3D(1, 1, 1);

            System.out.println(p1);

            Transformacja3D tr3D_1 = new Translacja3D(-1, 3, 5);
            Transformacja3D tr3D_2 = new Translacja3D(6, 0, -2);
            Transformacja3D tr3D_3 = new ObrotOS('x', 45);

            Transformacja3D[] transformacje3d = {tr3D_1, tr3D_2, tr3D_3};
            //Transformacja3D[] transformacje3d = {tr3D_3};

            Transformacja3D trz3D = new ZlozenieTransformacji3DTab(transformacje3d);

            System.out.println(trz3D);
            System.out.println(p1);

            Punkt3D p2 = trz3D.transformuj3D(p1);

            System.out.println(p2);

            Transformacja3D trrz3D = trz3D.getTransformacjaOdwrotna3D();

            System.out.println(trrz3D);

            Punkt3D p3 = trrz3D.transformuj3D(p2);

            System.out.println(p3);
        } catch (BrakTransformacjiOdwrotnejException ex)
        {
            ex.printStackTrace();
        }
        System.out.println();
        System.out.println("================Zlozenie 3D List================");
        try {
            Punkt3D p1 = new Punkt3D(1, 1, 1);

            System.out.println(p1);

            Transformacja3D tr3D_1 = new Translacja3D(-1, 3, 5);
            Transformacja3D tr3D_2 = new Translacja3D(6, 0, -2);
            Transformacja3D tr3D_3 = new ObrotOS('x', 45);

            ArrayList<Transformacja3D> transformacje3d = new ArrayList<Transformacja3D>();
            transformacje3d.add(tr3D_1);
            transformacje3d.add(tr3D_2);
            transformacje3d.add(tr3D_3);
            //Transformacja3D[] transformacje3d = {tr3D_3};

            Transformacja3D trz3D = new ZlozenieTransformacji3DList(transformacje3d);

            System.out.println(trz3D);
            System.out.println(p1);

            Punkt3D p2 = trz3D.transformuj3D(p1);

            System.out.println(p2);

            Transformacja3D trrz3D = trz3D.getTransformacjaOdwrotna3D();

            System.out.println(trrz3D);

            Punkt3D p3 = trrz3D.transformuj3D(p2);

            System.out.println(p3);
        } catch (BrakTransformacjiOdwrotnejException ex)
        {
            ex.printStackTrace();
        }
        System.out.println();
//        try {
//            Punkt p1 = Punkt.E_X;
//            System.out.println(p1);
//            Transformacja tr = new Translacja(5, 6);
//            System.out.println(tr);
//            Punkt p2 = tr.transformuj(p1);
//            System.out.println(p2);
//            Transformacja trr = tr.getTransformacjaOdwrotna();
//            System.out.println(trr);
//            Punkt p3 = trr.transformuj(p2);
//            System.out.println(p3);
//        } catch (BrakTransformacjiOdwrotnejException ex)
//        {
//            ex.printStackTrace();
//        }
//        System.out.println();
//        try
//        {
//            Punkt p1 = new Punkt(2, 2);
//            System.out.println(p1);
//            Transformacja tr2 = new Skalowanie(5, 4);
//            System.out.println(tr2);
//            Punkt p2 = tr2.transformuj(p1);
//            System.out.println(p2);
//            Transformacja trr2 = tr2.getTransformacjaOdwrotna();
//            System.out.println(trr2);
//            Punkt p3 = trr2.transformuj(p2);
//            System.out.println(p3);
//        }
//        catch(BrakTransformacjiOdwrotnejException ex)
//        {
//            ex.printStackTrace();
//        }
//        System.out.println();
//        try
//        {
//            System.out.println("New code:");
//            Punkt p1 = new Punkt(4, 4);
//            Transformacja tr1 = new Obrot(720);
//            System.out.println(tr1);
//            System.out.println(p1);
//            Punkt p2 = tr1.transformuj(p1);
//            System.out.println(p2);
//            Transformacja trr2 = tr1.getTransformacjaOdwrotna();
//            System.out.println(trr2);
//            Punkt p3 = trr2.transformuj(p2);
//            System.out.println(p3);
//        }
//        catch(BrakTransformacjiOdwrotnejException ex)
//        {
//            ex.printStackTrace();
//        }
//        System.out.println();
//        try
//        {
//            System.out.println("New code 2:");
//            Punkt p1 = new Punkt(4, 4);
//            Transformacja tr1 = new Translacja(-2, -1);
//            Transformacja tr2 = new Obrot(60);
//            Transformacja tr3 = new Skalowanie(2, 5);
//            Transformacja[] transformacje = {tr1, tr2, tr3};
//
//            Transformacja trz = new ZlozenieTransformacji(transformacje);
//            System.out.println(trz);
//            System.out.println(p1);
//            Punkt p2 = trz.transformuj(p1);
//            System.out.println(p2);
//            Transformacja trr2 = trz.getTransformacjaOdwrotna();
//            System.out.println(trr2);
//            Punkt p3 = trr2.transformuj(p2);
//            System.out.println(p3);
//        }
//        catch(BrakTransformacjiOdwrotnejException ex)
//        {
//            ex.printStackTrace();
//        }
//        System.out.println();
//        try
//        {
//            Punkt p1 = new Punkt(2, 2);
//            Transformacja tr2 = new Skalowanie(5, 0);
//            System.out.println(tr2);
//            System.out.println(p1);
//            Punkt p2 = tr2.transformuj(p1);
//            System.out.println(p2);
//            Transformacja trr2 = tr2.getTransformacjaOdwrotna();
//            System.out.println(trr2);
//            Punkt p3 = trr2.transformuj(p2);
//            System.out.println(p3);
//        }
//        catch(BrakTransformacjiOdwrotnejException ex)
//        {
//            ex.printStackTrace();
//        }
//        System.out.println();
    }
}