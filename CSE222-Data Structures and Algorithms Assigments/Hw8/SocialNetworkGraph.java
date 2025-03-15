import java.util.*;

/**
 * The SocialNetworkGraph class represents a social network as a graph structure.
 * It supports adding and removing persons, managing friendships, finding the shortest path,
 * suggesting friends, and finding clusters of connected persons.
 */
public class SocialNetworkGraph{
    Map<String, Person> people = new HashMap<>();
    Map<Person, List<Person>> friendships = new HashMap<>();

    /**
     * Adds a person to the social network graph.
     * @param name    The name of the person.
     * @param age     The age of the person.
     * @param hobbies A list of hobbies of the person.
     */
    public void addPerson(String name, int age, List<String> hobbies){
        Person person = new Person(name, age, hobbies);
        people.put(name, person);
        friendships.put(person, new ArrayList<>());
        System.out.println("Person added: " + person);
    }

    /**
     * Removes a person from the social network graph.
     * @param name The name of the person to remove.
     * @param date The timestamp of the person to remove.
     */
    public void removePerson(String name, String date){
        // Search the desired person.
        if(people.containsKey(name)){
            Person person = people.get(name);

            // If the timestamp is correct with the found person,that means it is correct person.
            if(person.getTimestamp().equals(date)){
                // Remove the person from both people and friendships maps and also remove it from friendship list from the friends.
                people.remove(name);
                friendships.remove(person);
                for(List<Person> friends : friendships.values()){
                    if(friends.contains(person)){
                        friends.remove(person);
                    }
                }
                System.out.println("Person removed: " + name + " (Timestamp: " + date + ")");
            }else{
                System.out.println("No person found with the given timestamp.");
            }
        }else{
            System.out.println("No person found with the given name.");
        }
    }

    /**
     * Adds a friendship between two persons in the social network graph.
     * @param name1 The name of the first person.
     * @param date1 The timestamp of the first person.
     * @param name2 The name of the second person.
     * @param date2 The timestamp of the second person.
     */
    public void addFriendship(String name1, String date1, String name2, String date2){
        // Find the selected names from people map.
        Person person1 = people.get(name1);
        Person person2 = people.get(name2);

        if(person1 != null && person2 != null){
            // If selected people found then check their timestamps.
            if(person1.getTimestamp().equals(date1) && person2.getTimestamp().equals(date2)){
                // Add the people to their friendship lists.
                friendships.get(person1).add(person2);
                friendships.get(person2).add(person1);
                System.out.println("Friendship added between " + person1.getName() + " and " + person2.getName());
            }else{
                System.out.println("Timestamps do not match for the provided persons.");
            }
        }else{
            System.out.println("One or both persons not found in the network.");
        }
    }

    /**
     * Removes a friendship between two persons in the social network graph.
     * @param name1 The name of the first person.
     * @param date1 The timestamp of the first person.
     * @param name2 The name of the second person.
     * @param date2 The timestamp of the second person.
     */
    public void removeFriendship(String name1, String date1, String name2, String date2){
        // Get the people with selected names.
        Person person1 = people.get(name1);
        Person person2 = people.get(name2);

        if(person1 != null && person2 != null){
            // If selected names is valid then compare their timestamps.
            if(person1.getTimestamp().equals(date1) && person2.getTimestamp().equals(date2)){
                // Remove the people from their from friendship lists.
                boolean removed1 = friendships.get(person1).remove(person2);
                boolean removed2 = friendships.get(person2).remove(person1);

                if(removed1 && removed2){
                    System.out.println("Friendship removed between " + person1.getName() + " and " + person2.getName());
                }else{
                    System.out.println("Friendship is not found between " + person1.getName() + " and " + person2.getName());
                }
            }else{
                System.out.println("Timestamps don't match for the provided persons.");
            }
        } else {
            System.out.println("One or both persons not found in the network.");
        }
    }

    /**
     * Finds the shortest path between two persons in the social network graph.
     * @param name1 The name of the first person.
     * @param date1 The timestamp of the first person.
     * @param name2 The name of the second person.
     * @param date2 The timestamp of the second person.
     * @return A string representation of the shortest path.
     */
    public String findShortestPath(String name1, String date1, String name2, String date2){
        // Retrieve the starting and ending persons from the map
        Person start = people.get(name1);
        Person end = people.get(name2);

        // Check if both persons are found in the network
        if(start == null || end == null){
            System.out.println("ERROR! One or both persons not found in the network.");
            return "No path found.";
        }

        // Check if the timestamps match the provided persons
        if(!start.getTimestamp().equals(date1) || !end.getTimestamp().equals(date2)){
            System.out.println("ERROR! Timestamps do not match for the provided persons.");
            return "No path found.";
        }

        // Initialize the BFS traversal
        Map<Person, Person> prev = new HashMap<>();
        Queue<Person> queue = new LinkedList<>();
        Set<Person> visited = new HashSet<>();
        queue.add(start);
        visited.add(start);

        // Perform BFS to find the shortest path
        while(!queue.isEmpty()){
            Person current = queue.poll();
            if(current.equals(end)){
                // If the end person is found, reconstruct the path
                return formatPath(reconstructPath(prev, start, end));
            }

            // Traverse the friends of the current person
            for(Person friend : friendships.get(current)){
                if(!visited.contains(friend)){
                    queue.add(friend);
                    visited.add(friend);
                    prev.put(friend, current); // By holding predecessor, the path will be created.
                }
            }
        }

        // If no path is found
        System.out.println("No path found between " + name1 + " and " + name2);
        return "No path found.";
    }

    /**
     * Reconstructs the path from the BFS traversal.
     * @param prev  The map of predecessors from the BFS traversal.
     * @param start The starting person.
     * @param end   The ending person.
     * @return A list of persons representing the path.
     */
    private List<Person> reconstructPath(Map<Person, Person> prev, Person start, Person end){
        List<Person> path = new LinkedList<>();
        // Traverse the predecessors map from end to start
        for(Person at = end; at != null; at = prev.get(at)){
            path.add(at);
        }
        // Reverse the path to get the correct order from start to end
        Collections.reverse(path);
        return path;
    }

    /**
     * Formats the path as a string.
     * @param path The list of persons representing the path.
     * @return A string representation of the path.
     */
    private String formatPath(List<Person> path){
        if(path.isEmpty()){
            return "No path found.";
        }
        StringBuilder pathStr = new StringBuilder();
        // Build the path string with the names of the persons
        for(Person person : path){
            if(pathStr.length() > 0){
                pathStr.append("-> ");
            }
            pathStr.append(person.getName());
        }
        return "Shortest path: " + pathStr.toString();
    }

    /**
     * Suggests friends for a person in the social network graph.
     * @param name        The name of the person for whom to suggest friends.
     * @param date        The timestamp of the person for whom to suggest friends.
     * @param friendCount The maximum number of friends to suggest.
     */
    public void suggestFriends(String name, String date, int friendCount){
        // Validate the given input.
        Person person = people.get(name);
        if (person == null) {
            System.out.println("Person not found in the network.");
            return;
        }
        if (!person.getTimestamp().equals(date)) {
            System.out.println("Timestamp does not match for the provided person.");
            return;
        }

        Map<Person, Double> potentialFriends = new HashMap<>(); // Map to store people and their scores
        Set<Person> currentFriends = new HashSet<>(friendships.get(person)); // Get the current friends the input person to not suggest them as friend.

        // Calculate scores for each person in the network
        for(Person other : people.values()){
            // If other is given input or other is already a friend ignore that step.
            if (other.equals(person) || currentFriends.contains(other)) {
                continue;
            }

            // Calculate the number of common friends
            Set<Person> commonFriends = new HashSet<>(friendships.get(person));
            commonFriends.retainAll(friendships.get(other)); // Only remains common friends
            int mutualFriendCount = commonFriends.size();

            // Calculate the number of common hobbies
            Set<String> commonHobbies = new HashSet<>(person.getHobbies());
            commonHobbies.retainAll(other.getHobbies());    // Only remains common hobies
            int commonHobbyCount = commonHobbies.size();

            // Calculate the score for friendship
            double score = mutualFriendCount * 1 + commonHobbyCount * 0.5;
            potentialFriends.put(other, score);
        }

        // Sort the potential friends by their scores in descending order
        List<Map.Entry<Person, Double>> sortedPeople = new ArrayList<>(potentialFriends.entrySet());
        sortedPeople.sort((a, b) -> Double.compare(b.getValue(), a.getValue()));

        // Display the top N suggested friends with the score breakdown
        System.out.println("Top " + friendCount + " suggested friends for " + name + ":");
        for(int i = 0; i < Math.min(friendCount, sortedPeople.size()); i++){
            Map.Entry<Person, Double> entry = sortedPeople.get(i);
            Person suggestedFriend = entry.getKey();
            double score = entry.getValue();
            System.out.println(suggestedFriend.getName() + " (Score: " + score + ")");
        }
    }

    /**
     * Finds and prints clusters of connected persons in the social network graph.
     */
    public void findClusters(){
        Set<Person> visited = new HashSet<>();
        List<Set<Person>> clusters = new ArrayList<>();

        // Go through every person within the people, if it isnt visited create a cluster for it 
        // and find the cluster of that unvisited person even it has no friend. 
        for(Person person : people.values()){
            if(!visited.contains(person)){
                Set<Person> cluster = new HashSet<>();
                bfs(person, visited, cluster); // By using breath-first search create the clusters.
                clusters.add(cluster);
            }
        }

        // Print the cluster count and cluster elements.
        System.out.println("Counting clusters in the social network...");
        System.out.println("Number of clusters found: " + clusters.size());
        for (int i = 0; i < clusters.size(); i++) {
            System.out.println("Cluster " + (i + 1) + ":");
            printCluster(clusters.get(i));
        }
    }

    /**
     * Performs a breadth-first search (BFS) to find all connected persons starting from a given person.
     * @param start    The starting person.
     * @param visited  A set of visited persons.
     * @param cluster  A set of connected persons forming a cluster.
     */
    private void bfs(Person start, Set<Person> visited, Set<Person> cluster){
        // Initilaze the queue and sets with starting person.
        Queue<Person> queue = new LinkedList<>();
        queue.add(start);
        visited.add(start);
        cluster.add(start);

        while(!queue.isEmpty()){
            Person current = queue.poll(); // Take the first person in the queue.

            // Go through the every friend of selected person and add them to the queue for the next step of queue.
            for(Person friend : friendships.get(current)){
                if(!visited.contains(friend)){
                    queue.add(friend);
                    visited.add(friend); // Sign the processsed person as visited.
                    cluster.add(friend); // Create clusters by adding visited person.
                }
            }
        }
    }

    /**
     * Prints the details of a cluster.
     * @param cluster The set of persons forming the cluster.
     */
    private void printCluster(Set<Person> cluster) {
        for (Person person : cluster) {
            System.out.println(person.getName() + "---" + person.getTimestamp());
        }
    }
}
