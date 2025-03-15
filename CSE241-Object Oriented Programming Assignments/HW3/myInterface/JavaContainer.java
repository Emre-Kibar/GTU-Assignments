package myInterface;
import java.util.Iterator;

/**
 * The JavaContainer interface defines a basic contract for classes that represent a container
 * for elements of type T. Containers allow elements to be added, removed, and iterated over.
 *
 * @param <T> The type of elements that the container holds.
 */
public interface JavaContainer<T> {
    /**
     * Adds an element to the container.
     *
     * @param element The element to be added to the container.
     */
    public void add(T element);

    /**
     * Removes an element from the container.
     *
     * @param element The element to be removed from the container.
     */
    public void remove(T element);

    /**
     * Returns the number of elements in the container.
     *
     * @return The size of the container.
     */
    public int Size();

    /**
     * Returns an iterator over the elements in the container.
     *
     * @return An iterator for iterating over the elements in the container.
     */
    public Iterator<T> getIterator();
}
