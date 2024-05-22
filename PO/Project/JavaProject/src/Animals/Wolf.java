package Animals;

import Abstractions.*;
import com.google.gson.JsonObject;

import java.awt.*;

public class Wolf extends Animal {

    public Wolf(World world, Point position) {
        super(9, 5, position, world);
        this.avatar = 'W';
        this.image_path = "Wolf.png";
        loadImage();
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Wolf(world, newPosition);
    }
}
