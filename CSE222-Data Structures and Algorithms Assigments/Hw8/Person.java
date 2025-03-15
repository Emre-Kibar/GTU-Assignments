import java.text.SimpleDateFormat;
import java.util.*;

/**
 * Represents a person with a name, age, hobbies, and a timestamp of creation.
 */
public class Person {
    private String name;
    private int age;
    private List<String> hobbies;
    // The timestamp held as String because instead of formating every input date, take input as String and compare the dates as String.
    private String timestamp;  

    // Define a formatter to format the date and time as desired
    private static final SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    /**
     * Constructs a new Person with the given name, age, and hobbies.
     * The timestamp is set to the current date and time.
     *
     * @param name The name of the person.
     * @param age The age of the person.
     * @param hobbies The list of hobbies of the person.
     */
    public Person(String name, int age, List<String> hobbies){
        this.name = name;
        this.age = age;
        this.hobbies = new ArrayList<>(hobbies);
        this.timestamp = formatter.format(new Date());  // Format the current date and time and store it as a string
    }

    /**
     * Gets the name of the person.
     * @return The name of the person.
     */
    public String getName(){
        return name;
    }

    /**
     * Gets the age of the person.
     * @return The age of the person.
     */
    public int getAge(){
        return age;
    }

    /**
     * Gets the list of hobbies of the person.
     * @return A new list containing the hobbies of the person.
     */
    public List<String> getHobbies(){
        return new ArrayList<>(hobbies);
    }

    /**
     * Gets the timestamp of when the person was created.
     * @return The timestamp of the person.
     */
    public String getTimestamp(){
        return timestamp;
    }

    /**
     * Sets the name of the person.
     * @param name The new name of the person.
     */
    public void setName(String name){
        this.name = name;
    }

    /**
     * Sets the age of the person.
     * @param age The new age of the person.
     */
    public void setAge(int age){
        this.age = age;
    }

    /**
     * Sets the list of hobbies of the person.
     * @param hobbies The new list of hobbies of the person.
     */
    public void setHobbies(List<String> hobbies){
        this.hobbies = new ArrayList<>(hobbies);
    }

    /**
     * Sets the timestamp of the person.
     * @param timestamp The new timestamp of the person.
     */
    public void setTimestamp(String timestamp){
        this.timestamp = timestamp;
    }

    /**
     * Returns a string representation of the person, including their name and timestamp.
     * @return A string representation of the person.
     */
    @Override
    public String toString(){
        return name + " (Timestamp: " + timestamp + ")";
    }
}
