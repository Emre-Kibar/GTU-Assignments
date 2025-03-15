public class Person {
    private String name;
    private String surname;
    private String adress;
    private String phone;
    private int ID;

    public Person(){
        name = "None";
        surname = "None";
        adress = "None";
        phone = "None";
        ID = 0;
    }

    public Person(String Name, String Surname, String Adress, String Phone, int id){
        name = Name;
        surname = Surname;
        adress = Adress;
        phone = Phone;
        ID = id;
    }

    public String getName(){
        return name;
    }
    public String getSurname(){
        return surname;
    }
    public String getAdress(){
        return adress;
    }
    public String getPhone(){
        return phone;
    }
    public int getID(){
        return ID;
    }
}