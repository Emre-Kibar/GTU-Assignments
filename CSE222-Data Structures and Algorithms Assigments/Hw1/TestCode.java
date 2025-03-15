import java.util.Scanner;

public class TestCode {
    public static void main(String args[]){
        try{
            //I am reading the content.txt by creating a FileRead object and calling its readFile method.
            FileReader testObj = new FileReader();
            testObj.readFile();

            takeInput(testObj); //After reading the file,asking input from user.         
        }catch(Exception e){
            System.out.println("Please enter an positive integer value for ID.");
            System.out.println("An exception occurred testCode class: " + e.getClass().getName());
        }   
    }

    private static void takeInput(FileReader testObject) throws Exception{
        Scanner scanner = new Scanner(System.in);

        //Taking the integer value as input,if it isnt an integer or positive then throws exception.
        System.out.println("Please enter an ID...");
        int inputID = scanner.nextInt();

        if(inputID <= 0){
            scanner.close();
            throw new Exception();
        }

        //First searching the inputID within the customers array,If it is found that means given input is customer and it is printed.
        int isIDFound = 0;

        Customer[] all_Customer = testObject.getAllCustomers();
        int customers_count = testObject.getCustomersCount(); 
        for(int i = 0; i < customers_count; i++){
            if(all_Customer[i].getID() == inputID){
                isIDFound = 1;
                System.out.println("***  Customer Screen  ***");
                System.out.println("------------------------");
                all_Customer[i].print_customer();
                System.out.println("------------------------");
                break;
            }
        }   

        //If inputID isnt found within the customers,the inputID is searched through operators,if it is found,matching operator is printed.
        if(isIDFound == 0){
            Operator[] all_Operator = testObject.getAllOperators();
            int operators_count = testObject.getOperatorsCount();   
            for(int i = 0; i < operators_count; i++){
                if(all_Operator[i].getID() == inputID){
                    isIDFound = 1;
                    System.out.println("***  Operator Screen  ***");
                    System.out.println("------------------------");
                    all_Operator[i].print_operator();
                    break;
                }
            }
        }

        //If inputID isnt found within customers or operators,then the inputID isnt available.So,an error message printed.
        if(isIDFound == 0){
            System.out.println("------------------------");
            System.out.printf("No operator/customer was found with ID %d. Please try again.\n", inputID);
            System.out.println("------------------------");
        }

        scanner.close();
    }

}

