/**
 * The Keyboard class represents a Keyboard device,
 * implements the Device interface.
 */
public class Keyboard implements Device {
    private final String category = "Keyboard";
    private String name;
    private double price;
    private int quantity;

    /**
     * Constructs a new Keyboard object with the given name, price, and quantity.
     * @param Name     The name of the Keyboard.
     * @param Price    The price of the Keyboard.
     * @param Quantity The quantity of the Keyboard.
     * Assigning a new value to a variable has constant complexity,
     * the complexity of this method O(1).
     */
    public Keyboard(String Name, double Price,int Quantity){
        name = Name;
        price = Price;
        quantity = Quantity;
    }

    /**
     * Returns the category of the device. 
     * @return The category of the device.
     * Returning a variable has constant complexity, 
     * the complexity is O(1).
     */
    @Override
    public String getCategory(){
        return category;
    }

    /**
     * Returns the name of the device. 
     * @return The name of the device.
     * Returning a variable has constant complexity, 
     * the complexity is O(1).
     */
    @Override
    public String getName(){
        return name;
    }

    /**
     * Sets the name of the device.
     * @param Name The new name of the device.
     * Assigning a value to a variable has constant complexity,
     * the complexity is O(1).
     */
    @Override
    public void setName(String Name){
        name = Name;
    }

    /**
     * Returns the price of the device. 
     * @return The price of the device.
     * Returning a variable has constant complexity, 
     * the complexity is O(1).
     */
    @Override
    public double getPrice(){
        return price;
    }

    /**
     * Sets the price of the device.
     * @param Price The new price of the device.
     * Assigning a value to a variable has constant complexity,
     * the complexity is O(1).
     */
    @Override
    public void setPrice(double Price){
        price = Price;
    }

    /**
     * Returns the quantity of the device.
     * @return The quantity of the device.
     * Returning a variable has constant complexity, 
     * the complexity is O(1).
     */
    @Override
    public int getQuantity(){
        return quantity;
    }

    /**
     * Sets the quantity of the device.
     * @param Quantity The new quantity of the device.
     * Assigning a value to a variable has constant complexity,
     * the complexity is O(1).
     */
    @Override
    public void setQuantity(int Quantity){
        quantity = Quantity;
    }

    /**
     * Returns a string representation of the Keyboard.
     * @return A string representation of the Keyboard.
     * The complexity of returning a String and concatenation of Strings
     * has constant complexity, O(1).
     */
    @Override
    public String toString() {
        return "Category: " + category + ", Name: " + name + ", Price: $" + price + ", Quantity: " + quantity;
    }
}
