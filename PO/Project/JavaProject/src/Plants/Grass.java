package Plants;

import Abstractions.*;
import Animals.Sheep;
import com.google.gson.JsonObject;

import java.awt.*;

public class Grass extends Plant {

    public Grass(World world,Point position) {
        super(0, position, world);
        this.avatar = 'g';
        this.image_path = "Grass.png";
        loadImage();
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Grass(world, newPosition);
    }
}
