package Animals;

public class Fox extends Animal {

    public Fox(World world, Point position) {
        super(4, 4, position, world);
        this.avatar = 'F';
    }

    @Override
    public int fight(Organism target) {
        if (target.getStrength() > this.strength) {
            world.getLogger().log("Fox avoided the fight");

            world.findField(this.position).setMember(this);

            return 1;
        }

        return super.fight(target);
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Fox(world, newPosition);
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        // Custom cleanup code, if necessary
    }
}

