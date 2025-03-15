import mySource.JavaSet;
import mySource.JavaVector;
import java.util.Iterator;
import java.util.Locale;
import java.util.Scanner;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

/**
 * JavaContainerTest class demonstrates the usage of JavaSet and JavaVector classes.
 * It performs operations like creating sets, adding elements, removing elements, and comparing sets.
 * The program takes user inputs, generates sets and vectors, compares their equality,
 * and writes the contents to files 'set.txt' and 'vector.txt'.
 */
public class JavaContainerTest {
    /**
     * The main method that serves as the entry point of the program.
     * It creates instances of JavaSet and JavaVector, performs operations, and handles user inputs.
     *
     * @param args The command-line arguments (not used in this program).
     */
    public static void main(String args[]){
        try{
            JavaSet<Integer> integerSet1 = new JavaSet<>();
            integerSet1.add(1);
            integerSet1.add(2);
            integerSet1.add(3);
            integerSet1.add(4);
            integerSet1.add(5);
            integerSet1.add(6);
            JavaSet<String> stringSet1 = new JavaSet<>();
            stringSet1.add("hello");
            stringSet1.add("i");
            stringSet1.add("am");
            stringSet1.add("emre");
            JavaVector<Double> doubleVector1 = new JavaVector<>();
            doubleVector1.add(1.2);
            doubleVector1.add(2.2);
            doubleVector1.add(3.2);
            doubleVector1.add(4.2);
            doubleVector1.add(1.2);
            doubleVector1.add(2.2);
            JavaVector<String> stringVector1 = new JavaVector<>();
            stringVector1.add("hello");
            stringVector1.add("world");
            stringVector1.add("hello");

            System.out.println("---Auto Generated Sets and Vectors To Check Equality---");
            System.out.printf("IntegerSet1 : %s\n", integerSet1);
            System.out.printf("StringSet1 : %s\n", stringSet1);
            System.out.printf("DoubleVector1 : %s\n", doubleVector1);
            System.out.printf("StringVector1 : %s\n\n", stringVector1);

            Scanner scanner = new Scanner(System.in).useLocale(Locale.US);
            int createdSize;
            while(true){
                try{
                    System.out.print("Enter the size for IntegerSet2(will be compared to IntegerSet1 for equality): ");
                    createdSize = scanner.nextInt();
                    break;
                }catch(java.util.InputMismatchException e){
                    System.out.println("Invalid input! Please enter an integer.");
                    scanner.next(); // Consume the invalid input
                }
            }

            JavaSet<Integer> integerSet2 = new JavaSet<>(createdSize);
            System.out.printf("Enter %d integers for IntegerSet2(will be compared to IntegerSet1 for equality): ", createdSize);
            for(int i = 0; i < createdSize; i++){
                try{
                    int valueInt = scanner.nextInt();
                    integerSet2.add(valueInt);
                }catch(java.util.InputMismatchException e){
                    System.out.println("Invalid input! Please enter an integer.");
                    scanner.next(); // Consume the invalid input
                }catch(IllegalStateException e){
                    System.out.println("Invalid input! " + e.getMessage());
                }
            }

            System.out.printf("IntegerSet2 : %s\n", integerSet2);
            if(integerSet1.equals(integerSet2)){
                System.out.print("IntegerSet1 and IntegerSet2 are equal.\n\n");
            }else{
                System.out.print("IntegerSet1 and IntegerSet2 are not equal.\n\n");
            }

            while(true){
                try{
                    System.out.print("Enter the size for StringSet2(will be compared to StringSet1 for equality): ");
                    createdSize = scanner.nextInt();
                    break;
                }catch(java.util.InputMismatchException e){
                    System.out.println("Invalid input! Please enter an integer.");
                    scanner.next(); // Consume the invalid input
                }
            }

            JavaSet<String> stringSet2 = new JavaSet<>(createdSize);
            System.out.printf("Enter %d strings for StringSet2(will be compared to StringSet1 for equality): ", createdSize);
            for(int i = 0; i < createdSize ; i++){
                try{
                    String valueString = scanner.next();
                    stringSet2.add(valueString);
                }catch(IllegalStateException e){
                    System.out.println("Invalid input! " + e.getMessage());
                }
            }

            System.out.printf("StringSet2 : %s\n", stringSet2);
            if(stringSet1.equals(stringSet2)){
                System.out.print("StringSet1 and StringSet2 are equal.\n\n");
            }else{
                System.out.print("StringSet1 and StringSet2 are not equal.\n\n");
            }

            while(true){
                try{
                    System.out.print("Please enter an integer to remove from IntegerSet2: ");
                    int valueInt = scanner.nextInt();
                    integerSet2.remove(valueInt);
                    System.out.printf("IntegerSet2 after removing %d: %s\n", valueInt, integerSet2);
                    break;
                }catch(IllegalStateException e){
                    System.out.println("Invalid input! " + e.getMessage());
                }catch(java.util.InputMismatchException e){
                    System.out.println("Invalid input! Please enter an integer.");
                    scanner.next(); // Consume the invalid input
                }
            }

            while(true){
                try{
                    System.out.print("Please enter an string to remove from StringSet2: ");
                    String valueString = scanner.next();
                    stringSet2.remove(valueString);
                    System.out.printf("StringSet2 after removing '%s': %s\n\n", valueString ,stringSet2);
                    break;
                }catch(IllegalStateException e){
                    System.out.println("Invalid input! " + e.getMessage());
                }
            }
            
            System.out.println("IntegerSet2 using Iterator:");
            Iterator<Integer> integerIterator  = integerSet2.getIterator();
            while (integerIterator.hasNext()) {
                System.out.print(integerIterator.next());
                if (integerIterator.hasNext()) {
                    System.out.print(", ");
                }else{
                    System.out.print("\n");
                }
            }

            System.out.println("StringSet2 using Iterator:");
            Iterator<String> stringIterator  = stringSet2.getIterator();
            while (stringIterator.hasNext()) {
                System.out.print(stringIterator.next());
                if (stringIterator.hasNext()) {
                    System.out.print(", ");
                }else{
                    System.out.print("\n\n");
                }
            }

            while(true){
                try{
                    System.out.print("Enter the size for DoubleVector2(will be compared to DoubleVector1 for equality): ");
                    createdSize = scanner.nextInt();
                    break;
                }catch(java.util.InputMismatchException e){
                    System.out.println("Invalid input! Please enter an integer.");
                    scanner.next(); // Consume the invalid input
                }
            }
            
            JavaVector<Double> doubleVector2 = new JavaVector<>(createdSize);
            System.out.printf("Enter %d doubles for DoubleVector2(will be compared to DoubleVector1 for equality): ", createdSize);
            for(int i = 0; i < createdSize; i++){
                try{
                    double valueDouble = scanner.nextDouble();
                    doubleVector2.add(valueDouble);
                }catch(java.util.InputMismatchException e){
                    System.out.println("Invalid input! Please enter an double.");
                    scanner.next(); // Consume the invalid input
                }catch(IllegalStateException e){
                    System.out.println("Invalid input! " + e.getMessage());
                }
            }

            System.out.printf("DoubleVector2 : %s\n", doubleVector2);
            if(doubleVector1.equals(doubleVector2)){
                System.out.print("DoubleVector1 and DoubleVector2 are equal.\n\n");
            }else{
                System.out.print("DoubleVector1 and DoubleVector2 are not equal.\n\n");
            }

            while(true){
                try{
                    System.out.print("Enter the size for StringVector2(will be compared to StringVector1 for equality): ");
                    createdSize = scanner.nextInt();
                    break;
                }catch(java.util.InputMismatchException e){
                    System.out.println("Invalid input! Please enter an integer.");
                    scanner.next(); // Consume the invalid input
                }
            }

            JavaVector<String> stringVector2 = new JavaVector<>(createdSize);
            System.out.printf("Enter %d strings for StringVector2(will be compared to StringVector1 for equality):", createdSize);
            for(int i = 0; i < createdSize; i++){
                try{
                    String valueString = scanner.next();
                    stringVector2.add(valueString);
                }catch(IllegalStateException e){
                    System.out.println("Invalid input! " + e.getMessage());
                }
            }

            System.out.printf("StringVector2 : %s\n", stringVector2);
            if(stringVector1.equals(stringVector2)){
                System.out.print("StringVector1 and StringVector2 are equal.\n\n");
            }else{
                System.out.print("StringVector1 and StringVector2 are not equal.\n\n");
            }

            while(true){
                try{
                    System.out.print("Please enter an double to remove from DoubleSet2: ");
                    Double valueDouble = scanner.nextDouble();
                    doubleVector2.remove(valueDouble);
                    System.out.printf("DoubleVector2 after removing %f: %s\n", valueDouble, doubleVector2);
                    break;
                }catch(IllegalStateException e){
                    System.out.println("Invalid input! " + e.getMessage());
                }catch(java.util.InputMismatchException e){
                    System.out.println("Invalid input! Please enter a double.");
                    scanner.next(); // Consume the invalid input
                }
            }

            while(true){
                try{
                    System.out.print("Please enter an string to remove from StringVector2: ");
                    String valueString = scanner.next();
                    stringVector2.remove(valueString);
                    System.out.printf("StringVector2 after removing '%s': %s\n\n", valueString ,stringVector2);
                    break;
                }catch(IllegalStateException e){
                    System.out.println("Invalid input! " + e.getMessage());
                }
            }

            System.out.println("DoubleVector2 using Iterator:");
            Iterator<Double> doubleIterator  = doubleVector2.getIterator();
            while (doubleIterator.hasNext()) {
                System.out.print(doubleIterator.next());
                if (doubleIterator.hasNext()) {
                    System.out.print(", ");
                }else{
                    System.out.print("\n");
                }
            }

            System.out.println("StringVector2 using Iterator:");
            stringIterator  = stringVector2.getIterator();
            while (stringIterator.hasNext()) {
                System.out.print(stringIterator.next());
                if (stringIterator.hasNext()) {
                    System.out.print(", ");
                }else{
                    System.out.print("\n");
                }
            }

            scanner.close();

            // Create a BufferedWriter to write text to the file
            BufferedWriter bufferedWriter1 = new BufferedWriter(new FileWriter("set.txt", true));
            BufferedWriter bufferedWriter2 = new BufferedWriter(new FileWriter("vector.txt", true));

            // Write the contents to the file
            bufferedWriter1.write(integerSet2.toString());
            bufferedWriter1.newLine();
            bufferedWriter1.write(stringSet2.toString());

            bufferedWriter2.write(doubleVector2.toString());
            bufferedWriter2.newLine();
            bufferedWriter2.write(stringVector2.toString());

            // Close the BufferedWriter to flush and close the underlying FileWriter
            bufferedWriter1.close();
            bufferedWriter2.close();

            System.out.println("The sets and vectors have been written to the file successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception e) {
            System.out.println("An unexpected error occurred: " + e.getMessage());
        }
        

    }
    
}
