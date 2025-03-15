import java.io.File;
import java.util.Scanner;

public class FileReader {
    //All orders,customers and operators is stored inside FileReader obejct.
    private Order[] allOrders = new Order[100];
    private Customer[] allCustomers = new Customer[100];
    private Operator[] allOperators = new Operator[100];
    private int ordersCount = 0;
    private int customersCount = 0;
    private int operatorsCount = 0;

    public void readFile(){
        try{
            File file = new File("content.txt");
            Scanner scanner = new Scanner(file);
            
            //If there is a line in the content.txt,it will continue to read.
            while(scanner.hasNextLine()){
                String line = scanner.nextLine();
                String[] parts = line.split(";", -1); // The line seperated to parts in terms of semicolons.

                //By using checkParts method,the validity of each part is checked.
                if(checkParts(parts) == 0){
                    continue;
                }

                try{
                    switch (parts[0]) {
                        case "order":
                            //If the first term of parts is order,firstly the parts size checked if it is correct for order.
                            //Then,if it is valid an order object created and this object added to allOrders array.
                            if (parts.length != 6) {
                                continue; 
                            }
                            
                            Order order = new Order(parts[1], Integer.parseInt(parts[2]), Integer.parseInt(parts[3]),
                                Integer.parseInt(parts[4]), Integer.parseInt(parts[5]));
                            
                            allOrders[ordersCount++] = order;
                            
                            break;
                        case "retail_customer":  
                            //If the first term of parts is retail_customer,
                            //firstly the parts size and duplicateID checked if it is correct for retail_customer.
                            //Then,if it is valid an retail_customer object created and this object added to allCustomers array.
                            if (parts.length != 7 || checkDuplicateID(allCustomers, Integer.parseInt(parts[5])) == 1) {
                                continue; 
                            }
                            
                            Retail_customer retailCustomer = new Retail_customer(parts[1], parts[2], parts[3], parts[4], 
                                Integer.parseInt(parts[5]), Integer.parseInt(parts[6]));
                        
                            retailCustomer.define_orders(allOrders);
                            allCustomers[customersCount++] = retailCustomer;
                        
                            break;
                        case "corporate_customer":
                            //If the first term of parts is corporate_customer,
                            //firstly the parts size and duplicateID checked if it is correct for corporate_customer.
                            //Then,if it is valid an corporate_customer object created and this object added to allCustomers array.       
                            if (parts.length != 8 || checkDuplicateID(allCustomers, Integer.parseInt(parts[5])) == 1) {
                                continue; 
                            }
                        
                            Corporate_customer corporateCustomer = new Corporate_customer(parts[1], parts[2], parts[3], 
                                parts[4], Integer.parseInt(parts[5]), Integer.parseInt(parts[6]), parts[7]);
                        
                            corporateCustomer.define_orders(allOrders);
                            allCustomers[customersCount++] = corporateCustomer;
                        
                            break;
                        case "operator":
                            //If the first term of parts is operator,
                            //firstly the parts size and duplicateID checked if it is correct for operator.
                            //Then,if it is valid an operator object created and this object added to allOperators array.
                            if (parts.length != 7 || checkDuplicateID(allCustomers, Integer.parseInt(parts[5])) == 1 
                                                    || checkDuplicateID(allOperators, Integer.parseInt(parts[5])) == 1) {
                                continue; 
                            }
                            
                            Operator operator = new Operator(parts[1], parts[2], parts[3], parts[4], 
                                Integer.parseInt(parts[5]), Integer.parseInt(parts[6]));
                        
                            operator.define_customers(allCustomers);
                            allOperators[operatorsCount++] = operator;
                        
                            break;
                        default:
                            continue;
                    }
                }catch(Exception e){
                    continue;
                }
            }

            scanner.close();
        }catch(Exception e){
            System.out.println("An exception occurred for fileReader class: " + e.getClass().getName());
            e.printStackTrace();
        }
    }

    public Order[] getAllOrders() {
        return allOrders;
    }

    public Customer[] getAllCustomers() {
        return allCustomers;
    }

    public Operator[] getAllOperators() {
        return allOperators;
    }

    public int getOrdersCount(){
        return ordersCount;
    }

    public int getCustomersCount(){
        return customersCount;
    }

    public int getOperatorsCount(){
        return operatorsCount;
    }

    private int checkParts(String[] partsToCheck){
        for (int i = 1; i < partsToCheck.length; i++) {
            try{
                //If status is greater than 3 or lower than zero that means it is invalid and line will be ignored.
                if("order".equals(partsToCheck[0]) && (Integer.parseInt(partsToCheck[4]) > 3 || Integer.parseInt(partsToCheck[4]) < 0)){
                    return 0;
                }else if("order".equals(partsToCheck[0]) && i == 4){ //If status is in correct border,then it wont checked.
                    continue;
                }

                //The integers must be positive,if they dont,this line will be ignored.
                int value = Integer.parseInt(partsToCheck[i]);
                if (value <= 0) {
                    return 0; 
                }
            }catch(Exception e){
                continue;  //If the part element is a string,then parseInt will cause exception and loop goes to next iteration.
            }
        }

        //The empty strings is checked,if a part element is empty,this line will be ignored.
        int hasEmptyString = 0;
        for (String part : partsToCheck) {
            if (part.trim().isEmpty()) {
                hasEmptyString = 1;
                break;
            }
        }
        //If a part element is empty or given size isnt within the border,this line will be ignored.
        if (hasEmptyString == 1 || partsToCheck.length < 6 || partsToCheck.length > 8) {
            return 0;
        }else{
            return 1;
        }
    }

    private <T extends Person> int checkDuplicateID(T[] array, int id) {
        //The given id will be searched through array if there is a match that means there is a duplication problem.
        //In this case,this line will be ignored.
        if (array != null) {
            for (T element : array) {
                if (element != null && element.getID() == id) {
                    return 1;
                }
            }
        }
        return 0;
    }
    
    
}
