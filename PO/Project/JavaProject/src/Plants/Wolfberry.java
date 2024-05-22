package Plants;

import Abstractions.*;
import java.awt.*;

public class Wolfberry extends Plant {

    public Wolfberry(World world,Point position) {
        super(99, position, world);
        this.avatar = 'w';
        this.image_path = "Wolfberry.png";
        loadImage();
    }

    @Override
    public boolean rejectAttack(Organism attacker) {
        attacker.die();
        world.getLogger().log("Wolfberry instantly killed an attacker");
        return true;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Wolfberry(world, newPosition);
    }
}
