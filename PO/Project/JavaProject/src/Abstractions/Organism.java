package Abstractions;

import java.awt.*;

public abstract class Organism {
    protected int strength;
    protected int startingStrength;
    protected int initiative;
    protected int birth;
    protected boolean deathSentence;
    protected Point position;
    protected World world;
    protected char avatar;

    public Organism(World world, int strength, int initiative, Point position) {
        this.world = world;
        this.strength = strength;
        this.startingStrength = strength;
        this.initiative = initiative;
        this.position = position;
        this.deathSentence = false;
    }

    public abstract int action();
    public abstract int collision(Organism target);
    public abstract int fight(Organism target);
    public abstract boolean rejectAttack(Organism attacker);
    public abstract void draw(Graphics g, Point position, Dimension fieldSize);
    public abstract ClassType getClassType();

    public World getWorld() {
        return world;
    }

    public void setPosition(Point position) {
        this.position = position;
    }

    public Point getPosition() {
        return position;
    }

    public int getStrength() {
        return strength;
    }

    public void setStrength(int newStrength) {
        this.strength = newStrength;
    }

    public int getInitiative() {
        return initiative;
    }

    public void setBirth(int newBirth) {
        this.birth = newBirth;
    }

    public int getBirth() {
        return birth;
    }

    public boolean getDeathSentence() {
        return deathSentence;
    }

    public char getAvatar() {
        return avatar;
    }

    public void setDeathSentence() {
        this.deathSentence = true;
    }

    public abstract Organism makeChild(Point newPosition);

    public void reproduct() {
        Field freeField = world.getFreeFieldNear(position);
        if (freeField == null) {
            return;
        }
        world.add(makeChild(freeField.id));
    }
}
