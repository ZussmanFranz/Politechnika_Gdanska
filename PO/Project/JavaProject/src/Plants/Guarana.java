package Plants;

import Abstractions.*;
import java.awt.*;

public class Guarana extends Plant {

    public Guarana(World world,Point position) {
        super(0, position, world);
        this.avatar = 'u';
    }

    @Override
    public boolean rejectAttack(Organism attacker) {
        attacker.setStrength(attacker.getStrength() + 3);
        world.getLogger().logStrengthIncrease(attacker);
        return false;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Guarana(world, newPosition);
    }
}
