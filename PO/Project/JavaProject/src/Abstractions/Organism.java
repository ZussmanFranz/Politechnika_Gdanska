package Abstractions;

import com.google.gson.JsonObject;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public abstract class Organism {
    protected int strength;
    protected final int startingStrength;
    protected boolean strong;
    protected int initiative;
    protected int birth;
    protected boolean deathSentence;
    protected Point position;
    protected World world;
    protected char avatar;
    protected String image_path;
    protected String full_path;
    protected Image image;

    public Organism(World world, int strength, int initiative, Point position, String image_path) {
        this.world = world;
        this.strength = strength;
        this.startingStrength = strength;
        this.initiative = initiative;
        this.position = position;
        this.deathSentence = false;
        this.strong = false;

        this.image_path = image_path;
        loadImage();
    }

    public boolean loadImage(){
        // Construct the path to the image file
        this.full_path = System.getProperty("user.dir") + "/src/icons/";

        if (!(new File(full_path + image_path)).exists()){
            image_path = "Anon.png";
        }

        // Load the image
        image = null;
        try {
            image = ImageIO.read(new File(full_path + image_path));
        } catch (IOException e) {
            System.err.println("Error: Could not read the image file from " + full_path + image_path + "\nCurrent working directory is" + System.getProperty("user.dir"));
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public abstract int action();
    public abstract int collision(Organism target);
    public abstract int fight(Organism target);
    public abstract boolean rejectAttack(Organism attacker);
    public void draw(Graphics g, Point position, Dimension fieldSize){
        if ((strength > startingStrength) && (!strong)){
            strong = true;
            image_path = "strong/" + image_path;
            loadImage();
        }

        g.drawImage(image, position.x, position.y, fieldSize.width, fieldSize.height, null);
    }
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
    public int getStartingStrength(){
        return startingStrength;
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

    public void die() {
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
