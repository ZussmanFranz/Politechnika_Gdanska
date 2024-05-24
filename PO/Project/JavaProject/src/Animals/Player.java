package Animals;

import Abstractions.*;
import com.google.gson.JsonObject;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Player extends Animal {
    private int abilityCooldown_parameter;
    private int abilityCooldown;
    private int abilityDuration;

    public Player(World world, Point position) {
        super(5, 4, position, world);
        this.avatar = 'P';
        this.image_path = "Player.png";
        loadImage();
        this.abilityCooldown = 10;
        this.abilityCooldown_parameter = 10;
        this.abilityDuration = 500;
    }

    @Override
    public int action() {
        abilityCooldown++;

        if (abilityCooldown == abilityDuration + 1) {
            world.getLogger().log(LogManager.LogMessageType.ABILITY,"Ability is finished :(\n");
        }

        world.repaint();

        Point delta = new Point(0, 0);

        char input = world.getKeyHandler().getPlayerInput();

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
                world.save("save.txt");
                break;
            case 'e':
                if (abilityCooldown > abilityCooldown_parameter) {
                    abilityCooldown = 0;
                    world.getLogger().log(LogManager.LogMessageType.ABILITY,"Ability activated :)\n");
                } else {
                    world.getLogger().log(LogManager.LogMessageType.ABILITY,"It's too early :|\n");
                }
                break;
            case 'p':
                System.out.println("paused!");
                try {
                    Thread.sleep(5000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                delta = new Point(0, 0);
                break;
            default:
                break;
        }

        if (input != ' '){
            System.out.println("Key pressed: " + input);
        }

        return move(delta);
    }


    @Override
    public boolean rejectAttack(Organism attacker) {
        if (abilityCooldown <= abilityDuration) {
            List<Field> fieldsNearAttacker = world.getFieldsNear(attacker.getPosition());

            if (fieldsNearAttacker.isEmpty()) {
                world.getLogger().log(LogManager.LogMessageType.ABILITY,"Shield of Alzur could not protect :(");
                return false;
            }

            Point newPosition = fieldsNearAttacker.get(ThreadLocalRandom.current().nextInt(fieldsNearAttacker.size())).getId();
            attacker.setPosition(newPosition);

            world.getLogger().log(LogManager.LogMessageType.ABILITY,"Shield of Alzur protected player");
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
