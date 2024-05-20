package Animals;

public class Antelope extends Animal {

    public Antelope(World world, Point position) {
        super(4, 4, position, world);
        this.avatar = 'A';
    }

    @Override
    public int action() {
        int deltaY = (int) (Math.random() * 5) - 2; // Generates random number between -2 and 2
        int deltaX = (int) (Math.random() * 5) - 2; // Generates random number between -2 and 2

        if (deltaX == 0 && deltaY == 0) {
            return 0;
        }

        return move(new Point(position.x + deltaX, position.y + deltaY));
    }

    @Override
    public boolean rejectAttack(Organism attacker) {
        if (Math.random() < 0.5) {
            world.getLogger().log("Antelope avoided attack");

            Field newLocation = world.getFreeFieldNear(position);
            if (newLocation == null) {
                return false;
            }

            world.findField(position).setMember(null);

            attacker.getWorld().findField(attacker.getPosition()).setMember(null);
            attacker.setPosition(position);
            attacker.getWorld().findField(attacker.getPosition()).setMember(attacker);

            position = newLocation.getId();

            return true;
        }

        return false;
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Antelope(world, newPosition);
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        // Custom cleanup code, if necessary
    }
}

