public class Corporate_customer extends Customer {
    private String company_name;
    
    public Corporate_customer(String Name, String Surname, String Adress, String Phone, int id, int operatorID, String companyName){
        super(Name, Surname, Adress, Phone, id, operatorID);
        company_name = companyName;
    }

    @Override
    public void print_customer(){
        //The all datas stored within object is printed.
        System.out.printf("Name & Surname: %s %s\nAdress: %s\nPhone: %s\nID: %d\nOperator ID: %d\nCompany name: %s\n", 
            this.getName(), this.getSurname(), this.getAdress(), this.getPhone(),  this.getID(), this.getOperator_ID(), company_name);
        this.print_orders();
    }
}
