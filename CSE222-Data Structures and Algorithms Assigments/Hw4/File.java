/**
 * Represents a file in a file system.
 */
public class File extends FileSystemElement {
    /**
     * Constructor to initialize a file with a name and parent element.
     * @param name   The name of the file.
     * @param parent The parent directory of the file.
     */
    public File(String name, FileSystemElement parent) {
        super(name, parent);
    }
}
