package Animals;

import Abstractions.*;

import java.awt.*;
import java.util.concurrent.ThreadLocalRandom;

public class Animal extends Organism {

    public Animal(int strength, int initiative, Point position, World world) {
        super(world, strength, initiative, position, "Anon.png");
    }


    public int move(Point delta) {
        boolean collided = false;
        world.findField(position).setMember(null);

        Point newPosition = new Point(position.x + delta.x, position.y + delta.y);

        if (newPosition.x >= world.getDimensions().width) {
            newPosition.x = world.getDimensions().width - 1;
            delta.x = 0;
            System.out.println("collision Right!");
        } else if (newPosition.x < 0) {
            newPosition.x = 0;
            delta.x = 0;
            System.out.println("collision Left!");
        }

        if (newPosition.y >= world.getDimensions().height) {
            newPosition.y = world.getDimensions().height - 1;
            delta.y = 0;
            System.out.println("collision Bottom!");
        } else if (newPosition.y < 0) {
            newPosition.y = 0;
            delta.y = 0;
            System.out.println("collision Top!");
        }

        if (delta.x == 0 && delta.y == 0) {
            world.findField(position).setMember(this);
            return 0;
        }

        Organism target = world.findField(newPosition).getMember();

        if (target != null) {
            collided = true;
        }

        if (collided && collision(target) == 1) {
            return 1;
        }

        position = newPosition;
        world.findField(position).setMember(this);

        return collided ? 1 : 0;
    }

    @Override
    public int action() {
        int deltaX, deltaY;
        do {
            deltaY = ThreadLocalRandom.current().nextInt(-1, 2); // Generates random number between -1 and 1
            deltaX = ThreadLocalRandom.current().nextInt(-1, 2); // Generates random number between -1 and 1
        } while ((deltaX == 0 && deltaY == 0) || (world.findField(new Point(position.x + deltaX, position.y + deltaY)) == null));

        return move(new Point(deltaX, deltaY));
    }

    @Override
    public int collision(Organism target) {
        world.getLogger().logCollision(this, target);

        if (world.sameType(this, target)) {
            reproduct();
            world.getLogger().logReproductionCollision(this, target);
            return 1;
        }

        int result = fight(target);
        world.getLogger().logCollisionResult((result == 1) ? target : this);

        return result;
    }

    @Override
    public int fight(Organism target) {
        if (target.rejectAttack(this)) {
            if (deathSentence) {
                world.destroy(this);
                return 1;
            }
            world.findField(position).setMember(this);
            return 1;
        }

        if (target == null) {
            return 0;
        }

        if (target.getStrength() <= strength) {
            world.destroy(target);
            return 0;
        } else {
            world.destroy(this);
            return 1;
        }
    }

    @Override
    public boolean rejectAttack(Organism attacker) {
        return false;
    }

    @Override
    public ClassType getClassType() {
        return ClassType.ANIMAL;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Animal(strength, initiative, newPosition, world); // Adjust parameters as necessary
    }
}
