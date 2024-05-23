package Animals;

import Abstractions.*;
import com.google.gson.JsonObject;

import java.util.Random;
import java.awt.*;
import java.util.concurrent.ThreadLocalRandom;

public class Turtle extends Animal {

    public Turtle(World world, Point position) {
        super(2, 1, position, world);
        this.avatar = 'T';
        this.image_path = "Turtle.png";
        loadImage();
    }

    @Override
    public int action() {
        Random rand = new Random();
        if (rand.nextInt(2) == 1) { // 0 - moving, 1 - not moving
            // world.getLogger().log("Turtle decided not to move\n");
            return 0;
        }

        int deltaY = ThreadLocalRandom.current().nextInt(-1, 2);; // Generates random number between -1 and 1
        int deltaX = ThreadLocalRandom.current().nextInt(-1, 2);; // Generates random number between -1 and 1

        if (deltaX == 0 && deltaY == 0) {
            return 0;
        }

        return move(new Point(deltaX, deltaY));
    }

    @Override
    public boolean rejectAttack(Organism attacker) {
        if (attacker.getStrength() < 5) {
            world.getLogger().log(LogManager.LogMessageType.ABILITY,"Turtle rejected attack");
            return true;
        }
        return false;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Turtle(world, newPosition);
    }
}

