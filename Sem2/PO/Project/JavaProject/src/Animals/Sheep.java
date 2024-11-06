package Animals;

import Abstractions.*;
import com.google.gson.JsonObject;
import java.awt.*;

public class Sheep extends Animal {

    public Sheep(World world, Point position) {
        super(4, 4, position, world);
        this.avatar = 'S';
        this.image_path = "Sheep.png";
        loadImage();
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Sheep(world, newPosition);
    }
}

