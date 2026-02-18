package jan2_2025.zadatak3;

public class Grocerie {
    private String name;
    private double price;

    Grocerie(String name, double price) {
        this.name = name;
        this.price = price;
    }

    String getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    @Override
    public String toString() {
        return "- " + name + " -- " + price + "$\n";
    }
}
