import java.util.*;

/**
 * The Main class provides a command-line interface for interacting with a social network graph.
 */
public class Main{
    /**
     * The main method serves as the entry point for the application.
     * @param args Command-line arguments (not used).
     */
    public static void main(String[] args){
        SocialNetworkGraph graph = new SocialNetworkGraph();
        Scanner scanner = new Scanner(System.in);
        boolean exit = false;

        addDemo(graph);

        while(!exit){
            try{
                System.out.println("==== Social Network Analysis Menu ====");
                System.out.println("1. Add Person");
                System.out.println("2. Remove Person");
                System.out.println("3. Add Friendship");
                System.out.println("4. Remove Friendship");
                System.out.println("5. Find Shortest Path");
                System.out.println("6. Suggest Friends");
                System.out.println("7. Count Clusters");
                System.out.println("8. Exit");
                System.out.print("Please select an option: ");

                int option = scanner.nextInt();
                scanner.nextLine();

                switch(option){
                    case 1:
                        addPerson(graph, scanner);
                        break;
                    case 2:
                        removePerson(graph, scanner);
                        break;
                    case 3:
                        addFriendship(graph, scanner);
                        break;
                    case 4:
                        removeFriendship(graph, scanner);
                        break;
                    case 5:
                        findShortestPath(graph, scanner);
                        break;
                    case 6:
                        suggestFriends(graph, scanner);
                        break;
                    case 7:
                        graph.findClusters();
                        break;
                    case 8:
                        System.out.println("Exiting...");
                        exit = true;
                        break;
                    default:
                        System.out.println("Invalid option. Please try again.");
                        break;
                }
            }catch(InputMismatchException e){
                System.out.println("Invalid input. Please enter a number between 1 and 8.");
                scanner.nextLine();
            }
        }

        scanner.close();
    }

    /**
     * Adds demo data to the social network graph for demonstration purposes.
     * @param graph The social network graph to which demo data will be added.
     */
    private static void addDemo(SocialNetworkGraph graph){
        Person person1 = new Person("John Doe", 25, Arrays.asList("reading", "hiking", "cooking"));
        Person person2 = new Person("Jane Smith", 22, Arrays.asList("swimming", "cooking"));
        Person person3 = new Person("Alice Johnson", 27, Arrays.asList("hiking", "painting"));
        Person person4 = new Person("Bob Brown", 30, Arrays.asList("reading", "swimming"));
        Person person5 = new Person("Emily Davis", 28, Arrays.asList("running", "swimming"));
        Person person6 = new Person("Frank Wilson", 26, Arrays.asList("reading", "hiking"));

        System.out.println("---DEMO PART---\n");

        // Adding some people for demonstration using getters
        graph.addPerson(person1.getName(), person1.getAge(), person1.getHobbies());
        graph.addPerson(person2.getName(), person2.getAge(), person2.getHobbies());
        graph.addPerson(person3.getName(), person3.getAge(), person3.getHobbies());
        graph.addPerson(person4.getName(), person4.getAge(), person4.getHobbies());
        graph.addPerson(person5.getName(), person5.getAge(), person5.getHobbies());
        graph.addPerson(person6.getName(), person6.getAge(), person6.getHobbies());

        // Adding friendships for demonstration using getters
        graph.addFriendship(person1.getName(), person1.getTimestamp(), person2.getName(), person2.getTimestamp());
        graph.addFriendship(person1.getName(), person1.getTimestamp(), person3.getName(), person3.getTimestamp());
        graph.addFriendship(person2.getName(), person2.getTimestamp(), person4.getName(), person4.getTimestamp());
        graph.addFriendship(person5.getName(), person5.getTimestamp(), person6.getName(), person6.getTimestamp());

        // Finding shortest path for demonstration using getters
        graph.findShortestPath(person1.getName(), person1.getTimestamp(), person4.getName(), person4.getTimestamp());

        // Counting clusters for demonstration
        graph.findClusters();

        System.out.println("\n\n");
    }

    /**
     * Adds a person to the social network graph based on user input.
     * @param graph The social network graph to which the person will be added.
     * @param scanner The scanner object used to read user input.
     */
    private static void addPerson(SocialNetworkGraph graph, Scanner scanner){
        try{
            System.out.print("Enter name: ");
            String name = scanner.nextLine();

            System.out.print("Enter age: ");
            int age = scanner.nextInt();
            scanner.nextLine();

            System.out.print("Enter hobbies (separated by commas): ");
            String hobbiesInput = scanner.nextLine();
            List<String> hobbies = new ArrayList<>(Arrays.asList(hobbiesInput.split(",")));

            for(int i = 0; i < hobbies.size(); i++){
                hobbies.set(i, hobbies.get(i).trim());
            }

            graph.addPerson(name, age, hobbies);

        }catch(InputMismatchException e){
            System.out.println("Invalid input for age. Please enter a valid value.");
            scanner.nextLine();
        }
    }

    /**
     * Removes a person from the social network graph based on user input.
     * @param graph The social network graph from which the person will be removed.
     * @param scanner The scanner object used to read user input.
     */
    private static void removePerson(SocialNetworkGraph graph, Scanner scanner){
        try{
            System.out.print("Enter name: ");
            String name = scanner.nextLine();

            System.out.print("Enter timestamp (yyyy-MM-dd HH:mm:ss): ");
            String date = scanner.nextLine();

            graph.removePerson(name, date);

        }catch(InputMismatchException e){
            System.out.println("Invalid input for timestamp. Please enter a valid value.");
            scanner.nextLine();
        }
    }

    /**
     * Adds a friendship between two people in the social network graph based on user input.
     * @param graph The social network graph to which the friendship will be added.
     * @param scanner The scanner object used to read user input.
     */
    private static void addFriendship(SocialNetworkGraph graph, Scanner scanner){
        try{
            System.out.print("Enter name for first person: ");
            String name1 = scanner.nextLine();
            System.out.print("Enter timestamp for first person (yyyy-MM-dd HH:mm:ss): ");
            String date1 = scanner.nextLine();

            System.out.print("Enter name for second person: ");
            String name2 = scanner.nextLine();
            System.out.print("Enter timestamp for second person (yyyy-MM-dd HH:mm:ss): ");
            String date2 = scanner.nextLine();

            graph.addFriendship(name1, date1, name2, date2);

        }catch(InputMismatchException e){
            System.out.println("Invalid input for adding friendship. Please enter a valid value.");
            scanner.nextLine();
        }
    }

    /**
     * Removes a friendship between two people in the social network graph based on user input.
     * @param graph The social network graph from which the friendship will be removed.
     * @param scanner The scanner object used to read user input.
     */
    private static void removeFriendship(SocialNetworkGraph graph, Scanner scanner){
        try {
            System.out.print("Enter name for first person: ");
            String name1 = scanner.nextLine();
            System.out.print("Enter timestamp for first person (yyyy-MM-dd HH:mm:ss): ");
            String date1 = scanner.nextLine();

            System.out.print("Enter name for second person: ");
            String name2 = scanner.nextLine();
            System.out.print("Enter timestamp for second person (yyyy-MM-dd HH:mm:ss): ");
            String date2 = scanner.nextLine();

            graph.removeFriendship(name1, date1, name2, date2);

        }catch(InputMismatchException e){
            System.out.println("Invalid input for removing friendship. Please enter a valid value.");
            scanner.nextLine();
        }
    }

    /**
     * Finds and prints the shortest path between two people in the social network graph based on user input.
     * @param graph The social network graph in which the shortest path will be found.
     * @param scanner The scanner object used to read user input.
     */
    private static void findShortestPath(SocialNetworkGraph graph, Scanner scanner){
        try{
            System.out.print("Enter name for first person: ");
            String name1 = scanner.nextLine();
            System.out.print("Enter timestamp for first person (yyyy-MM-dd HH:mm:ss): ");
            String date1 = scanner.nextLine();

            System.out.print("Enter name for second person: ");
            String name2 = scanner.nextLine();
            System.out.print("Enter timestamp for second person (yyyy-MM-dd HH:mm:ss): ");
            String date2 = scanner.nextLine();

            String path = graph.findShortestPath(name1, date1, name2, date2);
            System.out.println(path);
        }catch(InputMismatchException e){
            System.out.println("Invalid input for finding shortest path. Please enter a valid value.");
            scanner.nextLine();
        }
    }

    /**
     * Suggests friends for a person in the social network graph based on user input.
     * @param graph The social network graph in which friends will be suggested.
     * @param scanner The scanner object used to read user input.
     */
    private static void suggestFriends(SocialNetworkGraph graph, Scanner scanner){
        try{
            System.out.print("Enter name: ");
            String name = scanner.nextLine();
            System.out.print("Enter timestamp (yyyy-MM-dd HH:mm:ss): ");
            String date = scanner.nextLine();
            System.out.print("Enter maximum number of friends to suggest: ");
            int friendCount = scanner.nextInt();

            graph.suggestFriends(name, date, friendCount);

        }catch(InputMismatchException e){
            System.out.println("Invalid input for suggesting friends. Please enter a valid value.");
            scanner.nextLine();
        }
    }
}
