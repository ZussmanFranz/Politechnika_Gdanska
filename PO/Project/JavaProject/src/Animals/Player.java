package Animals;

import Abstractions.*;
import com.google.gson.JsonObject;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class Player extends Animal {
    private int abilityCooldown;

    public Player(World world, Point position) {
        super(5, 4, position, world);
        this.avatar = 'P';
        this.abilityCooldown = 10;
    }

    @Override
    public void draw(Graphics g, Point position, Dimension fieldSize) {
        if (strength > startingStrength) {
            g.setFont(new Font("default", Font.BOLD, 12));
        }
        g.setColor(Color.YELLOW); // Placeholder for COLOR_PAIR(3) in ncurses
        g.drawString(String.valueOf(avatar), position.x + fieldSize.width / 2, position.y + fieldSize.height / 2);
        g.setFont(new Font("default", Font.PLAIN, 12));
    }

    @Override
    public int action() {
        abilityCooldown++;

        if (abilityCooldown == 6) {
            world.getLogger().log("Ability is finished :(\n");
        }

        world.repaint();

        Point delta = new Point(0, 0);

        char input = ' ';
//        System.out.println("Player is handling input");
//        try {
//            input = world.getKeyHandler().getKey();
//        } catch (InterruptedException e) {
//            throw new RuntimeException(e);
//        }

        synchronized (world) {
            while (input == ' ') {
                try {
                    System.out.println("waiting for player's action");
                    world.wait(); // Wait for the player's input
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                input = world.getPlayerDirection();
            }
        }

        switch (input) {
            case 'w':
                delta = new Point(0, -1);
                break;
            case 'a':
                delta = new Point(-1, 0);
                break;
            case 's':
                delta = new Point(0, 1);
                break;
            case 'd':
                delta = new Point(1, 0);
                break;
            case 'q':
                world.stop();
                break;
            case 'e':
                if (abilityCooldown > 10) {
                    abilityCooldown = 0;
                    world.getLogger().log("Ability activated :)\n");
                } else {
                    world.getLogger().log("It's too early :|\n");
                }
                break;
            default:
                break;
        }

        System.out.println("Key pressed: " + input);
//        world.resetPlayerDirection();

        return move(delta);
    }

//    public void action(KeyHandler keyHandler) throws InterruptedException {
//        System.err.println("Human action");
//        char key = keyHandler.getKey();
//        switch (key) {
//            case 'w':
//                // move up
//                break;
//            case 'a':
//                // move left
//                break;
//            case 's':
//                // move down
//                break;
//            case 'd':
//                // move right
//                break;
//            case 'e':
//                // custom action
//                break;
//            case 'q':
//                // quit or another action
//                break;
//        }
//        System.out.println("Key pressed: " + key);
//    }

    @Override
    public boolean rejectAttack(Organism attacker) {
        if (abilityCooldown <= 5) {
            List<Field> fieldsNearAttacker = world.getFieldsNear(attacker.getPosition());

            if (fieldsNearAttacker.isEmpty()) {
                world.getLogger().log("Shield of Alzur could not protect :(");
                return false;
            }

            Point newPosition = fieldsNearAttacker.get(ThreadLocalRandom.current().nextInt(fieldsNearAttacker.size())).getId();
            attacker.setPosition(newPosition);

            world.getLogger().log("Shield of Alzur protected player");
            return true;
        }

        return false;
    }

    @Override
    public ClassType getClassType() {
        return ClassType.PLAYER;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Player(world, newPosition);
    }

    public int getCooldown() {
        return abilityCooldown;
    }

    public void setCooldown(int value) {
        this.abilityCooldown = value;
    }
}
