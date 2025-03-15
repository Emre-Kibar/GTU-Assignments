public class Customer extends Person {
    private Order[] orders = new Order[100];
    private int operator_ID;

    public Customer(){
        super();
        operator_ID = 0;
    }

    public Customer(String Name, String Surname, String Adress, String Phone, int id, int operatorID){
        super(Name, Surname, Adress, Phone, id);
        operator_ID = operatorID;
    }

    public int getOperator_ID(){
        return operator_ID;
    }

    public void print_customer(){
        //The all datas stored within object is printed.
        System.out.printf("Name & Surname: %s %s\nAdress: %s\nPhone: %s\nID: %d\nOperator ID: %d\n", 
            this.getName(), this.getSurname(), this.getAdress(), this.getPhone(),  this.getID(), operator_ID);
        this.print_orders();
    }

    public void print_orders(){
        //The orders are printed in order.
        int hasOrders = 0;
        for(int i = 0; i < orders.length; i++){
            if(orders[i] != null){
                hasOrders = 1;
                System.out.printf("Order #%d ==> ", i+1);
                orders[i].print_order();
            }
        }
        //If there isnt any orders,a convinient message printed.
        if(hasOrders == 0){
            System.out.println("This customer doesn't have any order.");
        }
    }

    public void define_orders(Order[] Orders) {
        //The orders that matched with this customer's ID will be stored in the object's memory.
        int OrdersCount = 0;
        for (Order order : Orders) {
            if (order != null && order.getCustomer_ID() == this.getID()) {
                orders[OrdersCount++] = order;
            }
        }
    }

}