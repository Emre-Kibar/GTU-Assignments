public class Operator extends Person {
    private Customer[] customers = new Customer[100];
    private int wage;
    
    public Operator(){
        super();
        wage = 0;
    }
    
    public Operator(String Name, String Surname, String Adress, String Phone, int id, int Wage){
        super(Name, Surname, Adress, Phone, id);
        wage = Wage;
    }

    public int getWage(){
        return wage;
    }

    public void print_operator(){
        //The all datas stored within object is printed.
        System.out.printf("Name & Surname: %s %s\nAdress: %s\nPhone: %s\nID: %d\nWage: %d\n", 
            this.getName(), this.getSurname(), this.getAdress(), this.getPhone(),  this.getID(), wage); 
        this.print_customers();  
    }


    public void print_customers(){
        int hasCustomers = 0;
        System.out.println("------------------------");

        //The customers are printed in order and the customer type is determined using downcasting.
        for(int i = 0; i < customers.length; i++){
            if(customers[i] != null){
                hasCustomers = 1;
                String customerType = (customers[i] instanceof Retail_customer) ? "a retail customer" : "a corporate customer";
                System.out.printf("Customer #%d (%s):\n", i+1, customerType);
                customers[i].print_customer();
                System.out.println("------------------------");
            }
        }
        //If there isnt any customer,a convinient message printed.
        if(hasCustomers == 0){
            System.out.println("This operator doesn't have any customer.");
            System.out.println("------------------------");
        }
    }

    public void define_customers(Customer[] _Customers) {
        //The customers that matched with this operator's ID will be stored in the object's memory.
        int CustomersCount = 0;
        for (Customer customer : _Customers) {
            if (customer != null && customer.getOperator_ID() == this.getID()) {
                customers[CustomersCount++] = customer;
            }
        }
    }
}
