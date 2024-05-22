package Animals;

import Abstractions.*;
import com.google.gson.JsonObject;

import java.awt.*;
import java.util.concurrent.ThreadLocalRandom;

public class Antelope extends Animal {

    public Antelope(World world, Point position) {
        super(4, 4, position, world);
        this.avatar = 'A';
        this.image_path = "Antelope.png";
        loadImage();
    }

    @Override
    public int action() {
        int deltaX, deltaY;
        do {
            deltaY = ThreadLocalRandom.current().nextInt(-2, 3); // Generates random number between -2 and 2
            deltaX = ThreadLocalRandom.current().nextInt(-2, 3); // Generates random number between -2 and 2
        } while ((deltaX == 0 && deltaY == 0) || (world.findField(new Point(position.x + deltaX, position.y + deltaY)) == null));

        if (deltaX == 0 && deltaY == 0) {
            return 0;
        }

        return move(new Point(deltaX, deltaY));
    }

    @Override
    public boolean rejectAttack(Organism attacker) {
        if (Math.random() < 0.5) {
            world.getLogger().log("Antelope avoided attack");

            Field newLocation = world.getFreeFieldNear(position);
            if (newLocation == null) {
                return false;
            }

            world.findField(position).setMember(null);

            attacker.getWorld().findField(attacker.getPosition()).setMember(null);
            attacker.setPosition(position);
            attacker.getWorld().findField(attacker.getPosition()).setMember(attacker);

            position = newLocation.getId();

            return true;
        }

        return false;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Antelope(world, newPosition);
    }
}

