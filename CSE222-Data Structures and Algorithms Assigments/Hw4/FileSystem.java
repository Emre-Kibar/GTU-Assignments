import java.util.Collections;
import java.util.LinkedList;

/**
 * The FileSystem class represents a file system management.
 */
public class FileSystem {
    private Directory root;

    /**
     * Constructs a new FileSystem with a root directory.
     */
    public FileSystem(){
        this.root = new Directory("root", null);
    }

    /**
     * Gets the root  of the file system.
     * @return The root.
     */
    public Directory getRoot(){
        return root;
    }
    
    /**
     * Changes the current directory based on the given path.
     * @param path The path input to change directory.
     * @return The new current directory.
     */
    public Directory changeDirectory(String path){
        path = path.replaceAll("^/|/$", "");
        if (path.isEmpty()) {
            return root;
        }

        String[] directories = path.split("/");
        Directory currentDirectory = root;

        for(int i = 0; i < directories.length; i++){
            boolean found = false;

            for(FileSystemElement element : currentDirectory.getChildren()){
                if(element instanceof Directory && element.getName().equals(directories[i])){
                    currentDirectory = (Directory) element;
                    found = true;
                    break;
                }
            }
            if (!found) {
                return null;
            }
        }
        return currentDirectory;
    }
    
    /**
     * Lists the contents of the directory.
     * @param currentDir The directory whose contents are to be listed.
     */
    public void listContents(Directory currentDir){
        LinkedList<FileSystemElement> children = currentDir.getChildren();

        if(children.isEmpty()){
            System.out.println("There are no files or directories in the current directory.");
            return;
        }
        for(FileSystemElement child : children){
            if(child instanceof Directory){
                System.out.println("* " + child.getName() + "/");
            }else{
                System.out.println(child.getName());
            }
        }
    }

    /**
     * Creates a new file in the current directory.
     * @param name The name of the file to be created.
     * @param currentDirectory The directory in which the file will be created.
     */
    public void createFile(String name, Directory currentDirectory){
        File newFile = new File(name, currentDirectory);
        currentDirectory.addChild(newFile);
    }

    /**
     * Creates a new directory in the current directory.
     * @param name The name of the directory to be created.
     * @param currentDirectory The directory in which the directory will be created.
     */
    public void createDirectory(String name, Directory currentDirectory){
        Directory newDirectory = new Directory(name, currentDirectory);
        currentDirectory.addChild(newDirectory);
    }

    /**
     * Deletes the specified file from the parent directory.
     * @param name The name of the file to be deleted.
     * @param parent The parent directory from which the file will be deleted.
     */
    public void deleteFile(String name, Directory parent){
        LinkedList<FileSystemElement> children = parent.getChildren();
        for(FileSystemElement element : children){
            if(element instanceof File && element.getName().equals(name)){
                children.remove(element);
                System.out.println("File deleted: " + name);
                return;
            }
        }
    }

    /**
     * Deletes the specified directory and its contents recursively.
     * @param name The name of the directory to be deleted.
     * @param parent The parent directory from which the directory will be deleted.
     */
    public void deleteDirectory(String name, Directory parent){
        LinkedList<FileSystemElement> children = parent.getChildren();
        for(FileSystemElement element : children){
            if(element instanceof Directory && element.getName().equals(name)){
                deleteDirectoryRecursive((Directory) element);
                children.remove(element);
                System.out.println("Directory deleted: " + name);
                return;
            }
        }
    }

    /**
     * Helper method to delete a directory recursively.
     * @param directory The directory to remove recursively.
     */ 
    private void deleteDirectoryRecursive(Directory directory) {
        LinkedList<FileSystemElement> children = directory.getChildren();
        for(FileSystemElement element : children){
            if(element instanceof Directory){
                deleteDirectoryRecursive((Directory) element);
            }
            children.remove(element);
        }
    }

    /**
     * Moves the specified file or directory to the target directory.
     * @param currentDirectory The current directory containing the file or directory to be moved.
     * @param name The name of the file or directory to be moved.
     * @param selecteDirectory The target directory to which the file or directory will be moved.
     * @return true if the operation is successful, false otherwise.
     */
    public boolean moveElement(Directory currentDirectory, String name, Directory selecteDirectory){
        LinkedList<FileSystemElement> children = currentDirectory.getChildren();
        FileSystemElement selectedElement = null;
        for(FileSystemElement child: children){
            if(child.getName().equals(name)){
                selectedElement = child;
                break;
            }
        }

        if(selectedElement == null){
            System.out.println("Error! The selected element to move is not found.");
            return false;
        }

        int index = children.indexOf(selectedElement);
        if(index != -1){
            FileSystemElement removedElement = children.remove(index);
            LinkedList<FileSystemElement> selectedChildren = selecteDirectory.getChildren();
            selectedChildren.add(removedElement);
            removedElement.setParent(selecteDirectory);
        }

        return true;
    }

    /**
     * Searches for a file or directory with the specified name in the file system.
     * @param name The name of the file or directory to search for.
     */
    public void search(String name){
        String path = searchRecursive(name, root);
        if(path == null){
            System.out.println("File or directory not found: " + name);
        }else{
            System.out.println("Found at: " + path);
        }
    }

    /**
     * Helper method to perform recursive search.
     * @param name Name of the directory which is wanted.
     * @param currentDirectory The directory which the recursive process will made.
     * @return Returns the path of searched element.
     */
    private String searchRecursive(String name, Directory currentDirectory){
        if(currentDirectory.getName().equals(name)){
            return getCurrentPath(currentDirectory);
        }

        for(FileSystemElement element : currentDirectory.getChildren()){
            if(element instanceof Directory){
                String path = searchRecursive(name, (Directory) element);
                if(path != null){
                    return path;
                }
            }else if(element.getName().equals(name)){
                return getCurrentPath(element);
            }
        }
        return null;
    }

    /**
     * Gets the absolute path of a file or directory.
     * @param element The file or directory for which the path is to be obtained.
     * @return The absolute path of the file or directory.
     */
    public String getCurrentPath(FileSystemElement element){
        StringBuilder path = new StringBuilder();
        FileSystemElement current = element;
        
        if(current.getParent() == null){
            path.insert(0, "/");
            return path.toString();
        }
        
        while (current.getParent() != null) {
            path.insert(0, current.getName());
            path.insert(0, "/");
            current = current.getParent();
        }
        return path.toString();
    }

    /**
     * Prints the directory tree starting from the specified directory.
     * @param currentDirectory The directory from which the directory tree will be printed.
     */
    public void printDirectoryTree(Directory currentDirectory){
        printDirectoryTreeRecursive(currentDirectory, currentDirectory);
    }
    
    /**
     * Helper method to print the directory tree recursively.
     * Prints the current directory with '*' and indicates it as the current directory if it matches the realCurrent directory.
     * @param current The current directory being processed.
     * @param realCurrent The directory considered as the current directory.
     * @return The number of tabs appended for indentation.
     */
    private int printDirectoryTreeRecursive(Directory current, Directory realCurrent){
        if(current == root){
            if(current == realCurrent)
                System.out.println("* " + current.getName() + "/" + " (Current Directory)");
            else
                System.out.println("* " + current.getName() + "/");
            return 1;
        }else{
            int tabsCount = printDirectoryTreeRecursive((Directory) current.getParent(), realCurrent);
            StringBuilder tabs = new StringBuilder();
            for(int i = 0; i < tabsCount; i++){
                tabs.append("\t");
            }

            if(current == realCurrent){
                System.out.println(tabs.toString() + "* " + current.getName() + "/" + " (Current Directory)");
                listContentswithTabs(current, tabsCount + 1);
            }else{
                System.out.println(tabs.toString() + "* " + current.getName() + "/");
            }

            return tabsCount + 1;
        }
    }

    /**
     * Prints the contents of the specified directory with appropriate indentation.
     * Directories are indicated with '*' prefix.
     * @param dir The directory whose contents are to be printed.
     * @param tabsCount The number of tabs to be used for indentation.
     */
    private void listContentswithTabs(Directory dir, int tabsCount){
        LinkedList<FileSystemElement> children = dir.getChildren();
        StringBuilder tabs = new StringBuilder();
        for (int i = 0; i < tabsCount; i++) {
            tabs.append("\t");
        }
        for (FileSystemElement child : children) {
            if(child instanceof Directory)
                System.out.println(tabs.toString() + "* " + child.getName());
            else
                System.out.println(tabs.toString()  + child.getName());
        }
    }
    
    /**
     * Sorts the contents of the specified directory by their creation dates in ascending order.
     * @param currentDirectory The directory whose contents are to be sorted.
     */
    public void sortContentsByDateCreated(Directory currentDirectory) {
        Collections.sort(currentDirectory.getChildren(), 
                            (first, second) -> first.getDateCreated().compareTo(second.getDateCreated()));
    }

    /**
     * Lists the contents of the specified directory along with their creation dates.
     * @param directory The directory whose contents are to be listed with creation dates.
     */
    public void listContentswithTime(Directory directory){
        LinkedList<FileSystemElement> children = directory.getChildren();
        for(FileSystemElement child : children){
            if(child instanceof Directory){
                System.out.println("* " + child.getName() + "\t" + child.getDateCreated());
            }else{
                System.out.println(child.getName() + "\t" + child.getDateCreated());
            }
        }
    }

}