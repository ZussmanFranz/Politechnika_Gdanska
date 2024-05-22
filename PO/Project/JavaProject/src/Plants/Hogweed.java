package Plants;

import Abstractions.*;
import java.awt.*;
import java.util.List;
import java.util.Random;

public class Hogweed extends Plant {

    public Hogweed(World world,Point position) {
        super(10, position, world);
        this.avatar = 'h';
        this.image_path = "Hogweed.png";
        loadImage();
    }

    @Override
    public int action() {
        if (new Random().nextInt(50) == 0) {
            reproduct();
            // return 0;
        }

        // Kill neighbors
        List<Field> near = world.getFieldsNear(position);

        for (Field field : near) {
            if (field.getMember() != null && !(field.getMember() instanceof Hogweed)) {
                world.getLogger().log("hogweed killed an organism with the area attack");
                world.destroy(field.getMember());
            }
        }

        return 1;
    }

    @Override
    public boolean rejectAttack(Organism attacker) {
        attacker.die();
        world.getLogger().log("hogweed instantly killed an attacker");
        return true;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Hogweed(world, newPosition);
    }
}

