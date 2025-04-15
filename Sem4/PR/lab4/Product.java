public class Product {
    String type;
    int quantity;

    public Product(String type, int quantity) {
        this.type = type;
        this.quantity = quantity;
    }

    @Override
    public String toString() {
        return type + " (" + quantity + ")";
    }
}
