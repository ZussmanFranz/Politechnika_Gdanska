package Plants;

import Abstractions.*;
import java.awt.*;
import java.util.Random;

public class Mlecz extends Plant {

    public Mlecz(World world,Point position) {
        super(0, position, world);
        this.avatar = 'm';
        this.image_path = "Mlecz.png";
        loadImage();
    }

    @Override
    public int action() {
        int result = 1;

        for (int i = 0; i < 3; i++) {
            if (new Random().nextInt(50) == 0) {
                reproduct();
                result = 0;
            }
        }

        return result;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Mlecz(world, newPosition);
    }
}
