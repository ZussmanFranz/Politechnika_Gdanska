import java.util.Random;

public class Producer implements Runnable {
    private final Warehouse warehouse;

    // Types of products produced
    private static final String[] TYPES = {"A", "B", "C"};
    // Maximum number of produced elements
    private final int max_produce;
    // Maximum delay between producing items
    private final int max_sleep_time;

    private final Random rand = new Random();
    private final Controller controller;

    public Producer(Warehouse warehouse, Controller controller, int max_produce, int max_sleep_time) {
        this.warehouse = warehouse;
        this.controller = controller;
        this.max_produce = max_produce;
        this.max_sleep_time = max_sleep_time;
    }

    @Override
    public void run() {
        while (!controller.stopRequested) {
            String type = TYPES[rand.nextInt(TYPES.length)];
            int quantity = rand.nextInt(max_produce) + 1;
            Product p = new Product(type, quantity);
            warehouse.addProduct(p);
            try {
                Thread.sleep(rand.nextInt(max_sleep_time));
            } catch (InterruptedException ignored) {}
        }
    }
}
