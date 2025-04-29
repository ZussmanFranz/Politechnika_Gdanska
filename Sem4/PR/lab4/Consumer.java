import java.util.Random;

public class Consumer implements Runnable {
    private final Warehouse warehouse;
    
    // Types of products consumed
    private static final String[] TYPES = {"A", "B", "C"};
    // Maximum number of consumed elements
    private final int max_consume;
    // Maximum delay between consuming items
    private final int max_sleep_time;
    
    private final Random rand = new Random();
    private final Controller controller;

    public Consumer(Warehouse warehouse, Controller controller, int max_consume, int max_sleep_time) {
        this.warehouse = warehouse;
        this.controller = controller;
        this.max_consume = max_consume;
        this.max_sleep_time = max_sleep_time;
    }

    @Override
    public void run() {
        while (!controller.stopRequested) {
            String type = TYPES[rand.nextInt(TYPES.length)];
            int quantity = rand.nextInt(max_consume) + 1;
            warehouse.consumeProduct(type, quantity);
            try {
                Thread.sleep(rand.nextInt(max_sleep_time));
            } catch (InterruptedException ignored) {}
        }
    }
}
