/**
 * The Device interface represents a generic electronic device.
 * Classes that implements this interface should provide methods
 * to get and set the device's category, name, price, and quantity.
 */
public interface Device {
    /**
     * Returns the category of the device. 
     * @return The category of the device.
     */
    public String getCategory();

    /**
     * Returns the name of the device. 
     * @return The name of the device.
     */
    public String getName();

    /**
     * Sets the name of the device.
     * @param Name The new name of the device.
     */
    public void setName(String Name);

    /**
     * Returns the price of the device. 
     * @return The price of the device.
     */
    public double getPrice();

    /**
     * Sets the price of the device.
     * @param Price The new price of the device.
     */
    public void setPrice(double Price);

    /**
     * Returns the quantity of the device.
     * @return The quantity of the device.
     */
    public int getQuantity();

    /**
     * Sets the quantity of the device.
     * @param Quantity The new quantity of the device.
     */
    public void setQuantity(int Quantity);
}
