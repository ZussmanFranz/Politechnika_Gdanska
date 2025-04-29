import java.util.*;

public class Warehouse {
    private final int capacity;
    // Products are stored in a <Type>(Quantity) manner (sorted by alphabet order)
    private final Map<String, Integer> storage = new HashMap<>();

    // ANSII codes
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_RED_BOLD = "\033[1;31m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_RESET = "\u001B[0m";

    public Warehouse(int capacity) {
        this.capacity = capacity;
    }

    public synchronized boolean addProduct(Product p) {
        int currentTotal = storage.values().stream().mapToInt(Integer::intValue).sum();
        if (currentTotal + p.quantity > capacity) {
            System.out.println(ANSI_RED_BOLD + "Failed to accept: " + p.type + " (" + p.quantity + ")" + ANSI_RESET);
            return false;
        }
        storage.put(p.type, storage.getOrDefault(p.type, 0) + p.quantity);
        System.out.println(ANSI_GREEN + "Produced: " + p + ANSI_RESET);
        return true;
    }

    public synchronized boolean consumeProduct(String type, int quantity) {
        int available = storage.getOrDefault(type, 0);
        if (available >= quantity) {
            storage.put(type, available - quantity);
            if (storage.get(type) == 0) {
                storage.remove(type);
            }
            System.out.println(ANSI_YELLOW + "Consumed: " + type + " (" + quantity + ")" + ANSI_RESET);
            return true;
        } else {
            System.out.println(ANSI_RED + "Failed to consume: " + type + " (" + quantity + ")" + ANSI_RESET);
            return false;
        }
    }

    public synchronized void printStatus() {
        StringBuilder sb = new StringBuilder();
        sb.append("[ ");
        boolean first = true;
        for (Map.Entry<String, Integer> entry : storage.entrySet()) {
            if (!first) sb.append(", ");
            sb.append(entry.getKey()).append(" (").append(entry.getValue()).append(")");
            first = false;
        }
        sb.append(" ]");
        System.out.println(ANSI_PURPLE + "\nCurrent warehouse: " + sb + "\n" + ANSI_RESET);
    }
}
