import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.InputMismatchException;
import java.util.LinkedList;
import java.util.Scanner;

/**
 * The Inventory class manages an inventory of electronic devices.
 * It provides methods to add, remove, update, list, find the cheapest device,
 * display sorted inventory, calculate the total price of inventory, restock a device,
 * export a inventory report.
 */
public class Inventory {
    private LinkedList<ArrayList<Device>> stock;

    /**
     * Constructs a new Inventory object with empty lists for different device categories.
     * The initializing a linked list and adding a variable both have constant complexity, O(1).
     */
    public Inventory() {
        stock = new LinkedList<>();
        stock.add(new ArrayList<>()); // For Smartphones
        stock.add(new ArrayList<>()); // For Laptops
        stock.add(new ArrayList<>()); // For TVs
        stock.add(new ArrayList<>()); // For Headphones
        stock.add(new ArrayList<>()); // For Keyboards
    }

    /**
     * Adds a new device to the inventory.
     * @param scanner The scanner object to read user input.
     * The complexity of taking inputs has constant, O(1) complexity,
     * switch statements has constant, O(1) complexity,
     * adding a device to ArrayList has constant complexity,O(1) when resizing isnt needed 
     * resizing and adding has linear complexity,O(n).
     * So, in average this method has constant complexity,O(1).
     */
    public void addDevice(Scanner scanner){
        System.out.print("Enter the category name: ");
        String Category = scanner.nextLine();
        System.out.print("Enter the device name: ");
        String Name = scanner.nextLine();
        double Price;
        while (true) {
            try {
                System.out.print("Enter the price (in dollars): ");
                Price = scanner.nextDouble();
                break;  // Exit the loop if the input is valid
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a valid price.");
                scanner.nextLine();
            }
        }

        int Quantity;
        while (true) {
            try {
                System.out.print("Enter the quantity: ");
                Quantity = scanner.nextInt();
                break;  // Exit the loop if the input is valid
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a valid quantity.");
                scanner.nextLine();
            }
        }

        switch (Category) {
            case "Smartphone":
                Smartphone newSmartphone = new Smartphone(Name, Price, Quantity);
                stock.get(0).add(newSmartphone);
                break;
            case "Laptop":
                Laptop newLaptop = new Laptop(Name, Price, Quantity);
                stock.get(1).add(newLaptop);
                break;
            case "TV":
                TV newTv = new TV(Name, Price, Quantity);
                stock.get(2).add(newTv);
                break;
            case "Headphone":
                Headphone newHeadphone = new Headphone(Name, Price, Quantity);
                stock.get(3).add(newHeadphone);
                break;
            case "Keyboard":
                Keyboard newKeyboard = new Keyboard(Name, Price, Quantity);
                stock.get(4).add(newKeyboard);
                break;
            default:
                System.out.println("ERROR! Invalid device category.");
        }
    }

    /**
     * Removes a device from the inventory.
     * @param scanner The scanner object to read user input.
     * Searching for a device to remove has O(m x n) compexity (m number of categories, n number of elements in a category),
     * the removing a device requires linear complexity due to shifting, O(n).
     * So, the complexity of this method is O(m x n). 
     */
    public void removeDevice(Scanner scanner){
        System.out.print("Enter the device name to remove: ");
        String Name = scanner.nextLine();

        boolean isRemoved = false;

        for(ArrayList<Device> deviceList : stock){
            for(int i = 0; i < deviceList.size(); i++){
                Device tempDevice = deviceList.get(i);
            
                if(tempDevice.getName().equals(Name)){
                    deviceList.remove(i);
                    isRemoved = true;
                    break;
                }
            }
            if(isRemoved){
                break;
            }
        }

        if(isRemoved){
            System.out.println("Device \"" + Name + "\" removed successfully.");
        }else{
            System.out.println("ERROR! Device \"" + Name + "\" not found.");
        }
    }

    /**
     * Updates details of a device in the inventory.
     * @param scanner The scanner object to read user input.
     * Taking inputs has constant complexity, O(1),
     * searching for a device to remove has O(m x n) compexity (m number of categories, n number of elements in a category),
     * updating the price and quantity has constant complexity, O(1).
     * So, the complexity of this method is O(mxn) as a dominant factor.
     */
    public void updateDevice(Scanner scanner){
        System.out.print("Enter the device name to update: ");
        String Name = scanner.nextLine();
        
        double Price = Double.NaN;
        while(true){
            System.out.print("Enter new price(leave blank to keep current price): ");
            String priceInput = scanner.nextLine();
            if(priceInput.isEmpty()) {
                break;  
            }

            try{
                Price = Double.parseDouble(priceInput);
                break;
            }catch(NumberFormatException e) {
                System.out.println("Invalid price. Please enter a valid double.");
            }
        }

        int Quantity = Integer.MIN_VALUE;
        while(true) {
            System.out.print("Enter new quantity (leave blank to keep current quantity): ");
            String quantityInput = scanner.nextLine();
            if(quantityInput.isEmpty()){
                break; 
            }

            try{
                Quantity = Integer.parseInt(quantityInput);
                break; 
            } catch (NumberFormatException e) {
                System.out.println("Invalid quantity. Please enter a valid integer.");
            }
        }

        boolean isFound = false;

        for(ArrayList<Device> deviceList : stock) {
            for(int i = 0; i < deviceList.size(); i++) {
                Device tempDevice = deviceList.get(i);
            
                if(tempDevice.getName().equals(Name)){
                    if(!Double.isNaN(Price)) {
                        tempDevice.setPrice(Price);
                    }
                    if (Quantity != Integer.MIN_VALUE) {
                        tempDevice.setQuantity(Quantity);
                    }
                    isFound = true;
                    break;
                }
            }
            if(isFound){
                break;
            }
        }

        if(isFound){
            System.out.println(Name + " details updated: Price - " + (Double.isNaN(Price) ? "no change" : Price + "$")
                                + ", Quantity - " + (Quantity == Integer.MIN_VALUE ? "no change" : Quantity));
        }else{
            System.out.println("ERROR! Device \"" + Name + "\" not found.");
        }
    }

    /**
     * Lists all devices in the inventory.
     * 
     * Iterating over devices have O(m x n) compexity (m number of categories, n number of elements in a category),
     * the printing a device has constant complexity, O(1).
     * So, the complexity of this method is O(m x n).
     */
    public void listAllDevices(){
        int deviceCount = 1;
        System.out.println("Device List: ");

        for(ArrayList<Device> deviceList : stock) {
            for(int i = 0; i < deviceList.size(); i++) {
                Device tempDevice = deviceList.get(i);
                
                System.out.println(deviceCount + ".  " + tempDevice);
                deviceCount++;
            }
        }
    }

    /**
     * Finds and displays the cheapest device in the inventory.
     * 
     * Iterating over devices have O(m x n) compexity (m number of categories, n number of elements in a category),
     * comparing the price has constant, O(1) complexity.
     * So, the complexity of this method has O(m x n).
     */
    public void findCheapestDevice(){
        Device cheapestOne = null;
        for(ArrayList<Device> deviceList : stock) {
            for(int i = 0; i < deviceList.size(); i++) {
                Device tempDevice = deviceList.get(i);
                
                if (cheapestOne == null || cheapestOne.getPrice() > tempDevice.getPrice()) {
                    cheapestOne = tempDevice;
                }
            }
        }

        if(cheapestOne != null){
            System.out.println("The cheapest device is: ");
            System.out.println(cheapestOne);
        }else{
            System.out.println("No devices found in the inventory.");
        }
    }

    /**
     * Lists devices sorted by price in ascending order.
     * 
     * The complexity of sorting categories using ArrayList.sort has O(nlogn) complexity,
     * iteration through devices has O(n) complexity,
     * finding lowest device has O(1) complexity,
     * printing and incrementing index with if statements has constant O(1) complexity.
     * So, the complexity of this method is O(nlogn).
     */
    public void listSortedDevices(){
        for(ArrayList<Device> deviceList : stock) {
            deviceList.sort(Comparator.comparingDouble(Device::getPrice));
        }
    
        ArrayList<Device> smartPhones = stock.get(0);         
        int smartphoneIndex = 0;
        ArrayList<Device> laptops = stock.get(1);             
        int laptopIndex = 0;
        ArrayList<Device> tvs = stock.get(2);                 
        int tvIndex = 0;
        ArrayList<Device> headPhones = stock.get(3);          
        int headphoneIndex = 0;
        ArrayList<Device> keyboards = stock.get(4);           
        int keyboardIndex = 0;
        
        int listingCount = 1;
        System.out.println("Devices sorted by price: ");

        while(true){
            Device lowest = lowestDevice(
                smartPhones, laptops, tvs, headPhones, keyboards, 
                smartphoneIndex, laptopIndex, tvIndex, headphoneIndex, keyboardIndex);

            if(lowest != null){
                System.out.println(listingCount + ".  " + lowest);
                listingCount++;

                if (lowest instanceof Smartphone) {
                    smartphoneIndex++;
                } else if (lowest instanceof Laptop) {
                    laptopIndex++;
                } else if (lowest instanceof TV) {
                    tvIndex++;
                } else if (lowest instanceof Headphone) {
                    headphoneIndex++;
                } else if (lowest instanceof Keyboard) {
                    keyboardIndex++;
                }
            }else{
                break;
            }
        }
    }
    
    /**
     * Finds the device with the lowest price among the provided lists of devices.
     *
     * @param smartPhones    The list of smartphones.
     * @param laptops        The list of laptops.
     * @param tvs            The list of TVs.
     * @param headPhones     The list of headphones.
     * @param keyboards      The list of keyboards.
     * @param smartphoneIndex    The current index of the smartphone list.
     * @param laptopIndex        The current index of the laptop list.
     * @param tvIndex            The current index of the TV list.
     * @param headphoneIndex     The current index of the headphone list.
     * @param keyboardIndex      The current index of the keyboard list.
     * @return The device with the lowest price among the provided lists, or null if the lists are empty or the indices are out of bounds.
     * 
     * The complexity of is statements have constant,O(1) complexity,
     * reaching the device and price has constant, O(1) complexity,
     * returning the device is constant,O(1) complexity.
     * So,the complexity of this method is O(1).
     */
    private Device lowestDevice(ArrayList<Device> smartPhones, ArrayList<Device> laptops, 
                                ArrayList<Device> tvs, ArrayList<Device> headPhones, ArrayList<Device> keyboards, 
                                int smartphoneIndex, int laptopIndex , int tvIndex, int headphoneIndex, int keyboardIndex){
        Device lowest = null;
        double lowestPrice = Double.MAX_VALUE;

        if (!smartPhones.isEmpty() && smartphoneIndex < smartPhones.size() && smartPhones.get(smartphoneIndex).getPrice() < lowestPrice){
            lowest = smartPhones.get(smartphoneIndex);
            lowestPrice = smartPhones.get(smartphoneIndex).getPrice();
        }
        if (!laptops.isEmpty() && laptopIndex < laptops.size() && laptops.get(laptopIndex).getPrice() < lowestPrice) {
            lowest = laptops.get(laptopIndex);
            lowestPrice = laptops.get(laptopIndex).getPrice();
        }
        if (!tvs.isEmpty() && tvIndex < tvs.size() && tvs.get(tvIndex).getPrice() < lowestPrice) {
            lowest = tvs.get(tvIndex);
            lowestPrice = tvs.get(tvIndex).getPrice();
        }
        if (!headPhones.isEmpty() && headphoneIndex < headPhones.size() && headPhones.get(headphoneIndex).getPrice() < lowestPrice) {
            lowest = headPhones.get(headphoneIndex);
            lowestPrice = headPhones.get(headphoneIndex).getPrice();
        }
        if (!keyboards.isEmpty() && keyboardIndex < keyboards.size() && keyboards.get(keyboardIndex).getPrice() < lowestPrice) {
            lowest = keyboards.get(keyboardIndex);
            lowestPrice = keyboards.get(keyboardIndex).getPrice();
        }

        return lowest;
    }
    
    /**
     * Calculates and displays the total value of all devices in the inventory.
     * 
     * Iterating over devices have O(m x n) compexity (m number of categories, n number of elements in a category),
     * adding the prices has constant,O(1) complexity.
     * So,the complexity of this method is O(m x n).
     */
    public void calculateTotalPrice(){
        double totalValue = 0.0;
    
        for(ArrayList<Device> deviceList : stock) {
            for(int i = 0; i < deviceList.size(); i++) {
                Device tempDevice = deviceList.get(i);
                
                totalValue += tempDevice.getPrice();
            }
        }
    
        System.out.println("Total inventory value:  $" + totalValue );
    }   

    /**
     * Restocks or reduces the quantity of a device in the inventory.
     * @param scanner The scanner object to read user input.
     * 
     * Iterating over devices have O(m x n) compexity (m number of categories, n number of elements in a category),
     * the selection for add/remove in if statements and input process has constant,O(1) complexity,
     * changing the value of quantity has constant,O(1) complexity.
     * So, the complexity of this method is O(m x n).
     */
    public void restockDevice(Scanner scanner){
        System.out.print("Enter the device name to update: ");
        String Name = scanner.nextLine();
        
        boolean isFound = false;
    
        for(ArrayList<Device> deviceList : stock) {
            for(int i = 0; i < deviceList.size(); i++) {
                Device tempDevice = deviceList.get(i);
    
                if(tempDevice.getName().equals(Name)) {
                    while(true) {
                        try{
                            isFound = true;
                            System.out.print("Do you want to add or remove stock? (Add/Remove): ");
                            String selection = scanner.nextLine();
                            int updatingQuantity = 0;
                            int selectionType = 0;
        
                            switch(selection) {
                                case "Add":
                                    System.out.print("Enter the quantity to add: ");
                                    updatingQuantity = scanner.nextInt();
                                    selectionType = 1;
                                    break;
                                case "Remove":
                                    System.out.print("Enter the quantity to remove: ");
                                    updatingQuantity = scanner.nextInt();
                                    selectionType = -1;
                                    break;
                                default:
                                    System.out.println("Invalid option. Please try again.");
                                    continue; 
                            }
        
                            if(selectionType != 0) {
                                int newQuantity = tempDevice.getQuantity() + (selectionType * updatingQuantity);
                                if(newQuantity < 0)
                                    newQuantity = 0;
                                
                                tempDevice.setQuantity(newQuantity);
                                String action = (selectionType == 1) ? "restocked" : "reduced";
                                System.out.println(tempDevice.getName() + " " + action + ". New quantity: " + tempDevice.getQuantity());
                                isFound = true;
                            } else {
                                System.out.println("Invalid option. Please try again.");
                            }
                            break;
                        }catch(InputMismatchException e){
                            System.out.println("ERROR! Invalid input, please enter a valid input.");
                            scanner.nextLine();
                            continue;
                        }
                    }
                    break;
                }
            }
            if(isFound) {
                break;
            }
        }
    
        if (!isFound) {
            System.out.println("ERROR! Device \"" + Name + "\" not found.");
        }
    }
    
    /**
     * Exports the inventory details to a text file.
     * 
     * Iterating over devices have O(m x n) compexity (m number of categories, n number of elements in a category),
     * printing the devices and calculating total price has constant,O(1) complexity.
     * So,the complexity of this method has O(m x n) complexity.
     */
    public void exportReport(){
        try{
            FileWriter file = new FileWriter("report.txt", true);
            PrintWriter printFile = new PrintWriter(file);

            LocalDate currentDate = LocalDate.now();
            DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
            String formattedDate = currentDate.format(dateFormatter);

            //Write header
            printFile.println("\nElectronics Shop Inventory Report");
            printFile.println("Generated on: " + formattedDate); 
            printFile.println("----------------------------------------");

            // Write device details
            int deviceCount = 0;
            double totalInventoryValue = 0.0;
            for (ArrayList<Device> deviceList : stock) {
                for (Device device : deviceList) {
                    deviceCount++;
                    printFile.printf("| %-3d | %-10s | %-20s | $%-10.2f | %-8d |\n", 
                        deviceCount, device.getCategory(), device.getName(), device.getPrice(), device.getQuantity());
                    totalInventoryValue += device.getPrice();
                }
            }

            //Write summary
            printFile.println("----------------------------------------\n");
            printFile.println("Summary:");
            printFile.printf("Total Number of Devices: %d\n", deviceCount);
            printFile.printf("Total Inventory Value: $%.3f\n\n", totalInventoryValue);
            printFile.println("End of Report");

            //Close the file
            printFile.close();
            file.close();

            System.out.println("Report written successfully to report.txt!");
        }catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
    }

}
