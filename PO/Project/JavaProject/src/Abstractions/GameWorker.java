package Abstractions;

import javax.swing.*;
import java.util.List;

public class GameWorker extends SwingWorker<Void, Void> {
    private World world;

    public GameWorker(World world) {
        this.world = world;
    }

    @Override
    protected Void doInBackground() throws Exception {
        while (!world.isOver()) {
            publish();
            Thread.sleep(1000 / world.getSpeed()); // Adjust the delay as needed
        }
        world.clean();
        return null;
    }

    @Override
    protected void process(List<Void> chunks) {
        world.update();
    }

    @Override
    protected void done() {
        world.drawEndscreen();
    }
}
