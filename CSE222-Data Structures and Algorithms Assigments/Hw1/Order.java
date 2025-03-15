public class Order {
    private String product_name;
    private int count;
    private int total_price;
    private int status;
    private int customer_ID;

    public Order(String productName, int Count, int totalPrice, int Status, int customerID){
        product_name = productName;
        count = Count;
        total_price = totalPrice;
        status = Status;
        customer_ID = customerID;
    }

    public String getProductName(){
        return product_name;
    }

    public int getCustomer_ID(){
        return customer_ID;
    }

    public void print_order(){
        //The all datas stored within object is printed and status is converted to correct string form.
        System.out.printf(" Product Name: %s - Count: %d - Total Price: %d - ", product_name, count, total_price);
        switch(status){
            case 0 :
                System.out.printf("Status: %s.\n", "Initialized");
                break;
            case 1 :
                System.out.printf("Status: %s.\n", "Processing");
                break;
            case 2 :
                System.out.printf("Status: %s.\n", "Completed");
                break;
            case 3 :
                System.out.printf("Status: %s.\n", "Cancelled");
                break;
        }
        
    }
}
