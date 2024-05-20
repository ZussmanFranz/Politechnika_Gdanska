package Plants;

public class Grass extends Plant {

    public Grass(Point position, World world) {
        super(0, position, world);
        this.avatar = 'g';
    }

    @Override
    public Organism makeChild(Point newPosition) {
        return new Grass(newPosition, world);
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        // Custom cleanup code, if necessary
    }
}
