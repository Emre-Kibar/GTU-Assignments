import java.util.Scanner;
import java.util.LinkedList;

/**
 * Main class to management of file system.
 */
public class Main {
    private static FileSystem fs = new FileSystem();
    private static Scanner scanner = new Scanner(System.in);
    private static Directory currentDirectory;

    /**
     * The main method to start the file system management.
     * @param args Command-line arguments.
     */
    public static void main(String args[]){
        currentDirectory = fs.getRoot();

        while(true){
            System.out.println("\nCurrent Directory: " + fs.getCurrentPath(currentDirectory));
            System.out.println("===== File System Management Menu =====");
            System.out.println("1. Change directory");
            System.out.println("2. List directory contents");
            System.out.println("3. Create file/directory");
            System.out.println("4. Delete file/directory");
            System.out.println("5. Move file/directory");
            System.out.println("6. Search file/directory");
            System.out.println("7. Print directory tree");
            System.out.println("8. Sort contents by date created");
            System.out.println("9. Exit");
            System.out.print("Please select an option: ");

            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    changeDirectory();
                    break;
                case 2:
                    listDirectoryContents();
                    break;
                case 3:
                    createFileOrDirectory();
                    break;
                case 4:
                    deleteFileOrDirectory();
                    break;
                case 5:
                    moveFileOrDirectory();
                    break;
                case 6:
                    searchFileOrDirectory();
                    break;
                case 7:
                    printDirectoryTree();
                    break;
                case 8:
                    sortContentsByDateCreated();
                    break;
                case 9:
                    System.out.println("Exiting...");
                    System.exit(0);
                default:
                    System.out.println("Invalid option.");
            }
        }
    }

    /**
     * Change the current directory according to given absoloute path.
     */
    private static void changeDirectory(){
        System.out.println("Listing the contents of " + fs.getCurrentPath(currentDirectory) + ":");
        System.out.print("Enter new directory path: ");
        String newPath = scanner.nextLine();

        Directory newCurrentDirectory = fs.changeDirectory(newPath);
        if (newCurrentDirectory != null) {
            currentDirectory = newCurrentDirectory;
            System.out.println("Directory changed to: " + fs.getCurrentPath(currentDirectory));
        } else {
            System.out.println("Invalid path to change: " + newPath);
        }
    }
    
    /**
     * List the contents of the current directory.
     */
    private static void listDirectoryContents(){
        System.out.println("Listing the contents of " + fs.getCurrentPath(currentDirectory) + ":");
        fs.listContents(currentDirectory);
    }

    /**
     * Create a new file or directory based on user input.
     */
    private static void createFileOrDirectory(){
        System.out.println("Current Directory: " + fs.getCurrentPath(currentDirectory));
        System.out.print("Create file or directory(f/d): ");
        String type = scanner.next();
        scanner.nextLine();

        String name;
        switch(type){
            case "f":
                System.out.print("Enter a name for file: ");
                name = scanner.nextLine();
                fs.createFile(name, currentDirectory);
                System.out.println("File created: " + name);
                break;
            case "d":
                System.out.print("Enter a name for directory: ");
                name = scanner.nextLine();
                fs.createDirectory(name, currentDirectory);
                System.out.println("Directory created: " + name);
                break;
            default:
                System.out.println("Invalid option.");
        }
    }

    /**
     * Delete a file or directory based on user input.
     */
    private static void deleteFileOrDirectory(){
        System.out.println("Current Directory: " + fs.getCurrentPath(currentDirectory));
        System.out.print("Enter name for a file/directory to delete: ");
        String name = scanner.nextLine();

        boolean isFound = false;
        LinkedList<FileSystemElement> children = currentDirectory.getChildren();
        for(FileSystemElement element : children){
            if(element.getName().equals(name)){
                if(element instanceof File)
                    fs.deleteFile(name, currentDirectory);
                else if(element instanceof Directory)
                    fs.deleteDirectory(name, currentDirectory);
            
                isFound = true;
            }
        }

        if(!isFound){
            System.out.println("Error! Selected file to delete in not found.");
            return;
        }
        
    }

    /**
     * Move a file or directory to another directory based on user input.
     */
    private static void moveFileOrDirectory() {
        System.out.println("Current Directory: " + fs.getCurrentPath(currentDirectory));
        System.out.print("Enter the name of the file or directory to move: ");
        String name = scanner.nextLine();
        System.out.print("Enter new directory path: ");
        String path = scanner.nextLine();
        
        Directory selectedDirectory = fs.changeDirectory(path);
        if(selectedDirectory != null){
            boolean isMoved = fs.moveElement(currentDirectory, name, selectedDirectory);

            if(isMoved){
                System.out.println("File moved: " + name + " to " + path);
            }else{
                System.out.println("Move operation is unsuccessful.");
            }

        }else{
            System.out.println("Invalid path to change.");
        }
    }

    /**
     * Search for a file or directory based on user input.
     */
    private static void searchFileOrDirectory(){
        System.out.print("Search query: ");
        String name = scanner.nextLine();
        fs.search(name);
    }

    /**
     * Print the directory tree of currentDirectory starting from the root.
     */
    private static void printDirectoryTree(){
        System.out.println("Path to current directory from root:");
        fs.printDirectoryTree(currentDirectory);
    }

    /**
     * Sort the contents of the current directory by creation date of files.
     */
    private static void sortContentsByDateCreated(){
        System.out.println("Sorted contents of " + fs.getCurrentPath(currentDirectory) + " by date created:");
        fs.sortContentsByDateCreated(currentDirectory);
        fs.listContentswithTime(currentDirectory);
    }
}