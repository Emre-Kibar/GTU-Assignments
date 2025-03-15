import java.sql.Timestamp;

/**
 * Abstract class representing a FileSystemElement, such as a file or directory.
 */
public abstract class FileSystemElement {
    private String name;
    private Timestamp dateCreated;
    private FileSystemElement parent;

    /**
     * Constructor to initialize a FileSystemElement with a name and parent element.
     * @param name   The name of the FileSystemElement.
     * @param parent The parent FileSystemElement.
     */
    public FileSystemElement(String name, FileSystemElement parent) {
        this.name = name;
        this.dateCreated = new Timestamp(System.currentTimeMillis());
        this.parent = parent;
    }

    /**
     * Setter method for the name of the FileSystemElement.
     * @param name The name to set.
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Getter method for the name of the FileSystemElement.
     * @return The name of the file system element.
     */
    public String getName() {
        return name;
    }

    /**
     * Setter method for the creation date of the FileSystemElement.
     * @param dateCreated The creation date to set.
     */
    public void setDateCreated(Timestamp dateCreated) {
        this.dateCreated = dateCreated;
    }

    /**
     * Getter method for the creation date of the file system element.
     * @return The creation date of the FileSystemElement.
     */
    public Timestamp getDateCreated() {
        return dateCreated;
    }

    /**
     * Setter method for the parent of the file system element.
     * @param parent The parent FileSystemElement to set.
     */
    public void setParent(FileSystemElement parent) {
        this.parent = parent;
    }

    /**
     * Getter method for the parent of the FileSystemElement.
     * @return The parent file system element.
     */
    public FileSystemElement getParent() {
        return parent;
    }
}
