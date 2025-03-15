import java.util.LinkedList;

/**
 * Represents a directory in a file system.
 */
public class Directory extends FileSystemElement {
    private LinkedList<FileSystemElement> children;

    /**
     * Constructor to initialize a directory with a name and parent element.
     * @param name   The name of the directory.
     * @param parent The parent directory of the directory.
     */
    public Directory(String name, FileSystemElement parent) {
        super(name, parent);
        this.children = new LinkedList<>();
    }

    /**
     * Give the list of children elements of this directory.
     * @return The list of children elements.
     */
    public LinkedList<FileSystemElement> getChildren() {
        return children;
    }

    /**
     * Add a child element to this directory. 
     * @param child The child element to add.
     */
    public void addChild(FileSystemElement child) {
        children.add(child);
    }

    /**
     * Remove a child element from this directory.
     * @param child The child element to remove.
     */
    public void removeChild(FileSystemElement child) {
        children.remove(child);
    }
}
