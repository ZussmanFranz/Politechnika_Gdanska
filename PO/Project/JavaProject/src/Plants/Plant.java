package Plants;

import Abstractions.*;

import java.awt.*;
import java.util.concurrent.ThreadLocalRandom;

public class Plant extends Organism {

    public Plant(int strength, Point position, World world) {
        super(world, strength, 0, position);
    }

    @Override
    public void draw(Graphics g, Point position, Dimension fieldSize) {
        if (strength > startingStrength) {
            g.setFont(new Font("default", Font.BOLD, 12));
        }
        g.setColor(Color.GREEN); // Placeholder for COLOR_PAIR in ncurses
        g.drawString(String.valueOf(avatar), position.x + fieldSize.width / 2, position.y + fieldSize.height / 2);
        g.setFont(new Font("default", Font.PLAIN, 12));
    }

    @Override
    public int action() {
        if (ThreadLocalRandom.current().nextInt(50) == 0) { // 2% chance
            reproduct();
            return 0;
        }
        return 1;
    }

    @Override
    public boolean rejectAttack(Organism attacker) {
        return false;
    }

    @Override
    public int collision(Organism target) {
        return 1; // Plants do not fight
    }

    @Override
    public int fight(Organism target) {
        return 1; // Plants do not fight
    }

    @Override
    public ClassType getClassType() {
        return ClassType.PLANT;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Plant(strength, newPosition, world); // Adjust parameters as necessary
    }
}
