package Animals;

import Abstractions.*;
import com.google.gson.JsonObject;

import java.awt.*;

public class Fox extends Animal {

    public Fox(World world, Point position) {
        super(4, 4, position, world);
        this.avatar = 'F';
        this.image_path = "Fox.png";
        loadImage();
    }

    @Override
    public int fight(Organism target) {
        if (target.getStrength() > this.strength) {
            world.getLogger().log("Fox avoided the fight");

            world.findField(this.position).setMember(this);

            return 1;
        }

        return super.fight(target);
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Fox(world, newPosition);
    }
}

