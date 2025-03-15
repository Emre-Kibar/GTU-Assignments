import java.util.Scanner;
import java.util.InputMismatchException;

/**
 * A class representing a simple test program for an electronics inventory management system.
 */
public class TestCode {

    /**
     * The main method to run the test program.
     * @param args Command line arguments (not used)
     * 
     * The inilitializing of inventory has constant complexity,O(1),
     * complexity of takeInput method is based on user to stop.
     * So,the complexity of this method cant be evaluated. 
     */
    public static void main(String args[]){
        Inventory newInventory = new Inventory();
        takeInput(newInventory);
    }

    /**
     * Takes input from the user and interacts with the inventory management system.
     * @param newInventory The Inventory object to interact with
     * 
     * The complexity of switch statements has constant complexity,O(1),
     * printing the menu has contant, O(1) complexity,
     * the operations of inventory in worst case has O(mn) comlexity(m number of categories, n number of elements in a category).
     * The complexity of this method is depend on the user inputs to stop,so the complexity cant be calculated.
     */
    public static void takeInput(Inventory newInventory){
        Scanner scanner = new Scanner(System.in);
        int input = -1;

        while(input != 0){
            printMenu();
            System.out.print("Enter an option (0-9): ");

            try {
                input = scanner.nextInt();
                scanner.nextLine();
                switch (input) {
                    case 1:
                        newInventory.addDevice(scanner);
                        break;
                    case 2:
                        newInventory.removeDevice(scanner);
                        break;
                    case 3:
                        newInventory.updateDevice(scanner);
                        break;
                    case 4:
                        newInventory.listAllDevices();
                        break;
                    case 5:
                        newInventory.findCheapestDevice();
                        break;
                    case 6:
                        newInventory.listSortedDevices();
                        break;
                    case 7:
                        newInventory.calculateTotalPrice();
                        break;
                    case 8:
                        newInventory.restockDevice(scanner);
                        break;
                    case 9:
                        newInventory.exportReport();
                        break;
                    case 0:
                        System.out.println("Exiting...");
                        break;
                    default:
                        System.out.println("Invalid option.Please try again.");
                }
            }catch (InputMismatchException e){
                System.out.println("Invalid input.Please enter a number between 0 and 9.");
                scanner.nextLine();
            }
        }
        scanner.close();
    }

    /**
     * Prints the menu options for the inventory management system.
     * 
     * Printing of the menu has constant,O(1) complexity.
     */
    private static void printMenu(){
        System.out.println("-------------------------------------------------------------------------");
        System.out.println("Welcome to the Electronics Inventory Management System!");
        System.out.println("Please select an option:");
        System.out.println("1. Add a new device");
        System.out.println("2. Remove a device");
        System.out.println("3. Update device details");
        System.out.println("4. List all devices");
        System.out.println("5. Find the cheapest device");
        System.out.println("6. Sort devices by price");
        System.out.println("7. Calculate total inventory value");
        System.out.println("8. Restock a device");
        System.out.println("9. Export inventory report");
        System.out.println("0. Exit");
        System.out.println("-------------------------------------------------------------------------");
    }
}
