package mySource;
import myInterface.JavaContainer;
import java.util.Iterator;

/**
 * The JavaSet class implements the JavaContainer interface, providing a set data structure
 * that holds elements of a specified type T. It supports addition, removal, and iteration over elements.
 *
 * @param <T> The type of elements in the set.
 */
public class JavaSet<T> implements JavaContainer<T> {
    private T[] elements;
    private int size;
    private int capacity;

    /**
     * Constructs a JavaSet with a default initial capacity of 10.
     */
    public JavaSet() {
        this(10);
    }

    /**
     * Constructs a JavaSet with the specified initial capacity.
     *
     * @param _capacity The initial capacity of the set.
     */
    @SuppressWarnings("unchecked")
    public JavaSet(int _capacity) {
        this.size = 0;
        this.capacity = _capacity;
        elements = (T[])new Object[this.capacity]; // initial capacity
    }

    /**
     * Adds an element to the set if it does not already exist.
     *
     * @param element The element to be added to the set.
     * @throws IllegalStateException If the element is already present in the set.
     */
    @Override
    @SuppressWarnings("unchecked")
    public void add(T element) {
        if (!isInside(element)) {
            if (size == capacity) {
                capacity = capacity * 2;
                T[] temp = elements;
                elements = (T[])new Object[capacity];
                for(int i=0; i < size ; i++){
                    elements[i] = temp[i];
                }
            }
            elements[size++] = element;
        }else{
            throw new IllegalStateException("You cannot add " + element +  " which is already in the set.");
        }
    }

    /**
     * Removes an element from the set.
     *
     * @param element The element to be removed from the set.
     * @throws IllegalStateException If the element isnt present in the set.
     */
    @Override
    public void remove(T element) {
        boolean isInclude = false;
        for (int i = 0; i < size; i++) {
            if (elements[i].equals(element)) {
                for(int j = i; j < size-1; j++){
                    elements[j] = elements[j+1];
                }
                isInclude = true;
                size--;
                break;
            }
        }
        if(isInclude == false){
            throw new IllegalStateException("You cannot remove " + element +  " which isnt in the set.");
        }
    }
    

    /**
     * Returns the size (number of elements) of the set.
     *
     * @return The size of the set.
     */
    @Override
    public int Size() {
        return size;
    }

    /**
     * Returns the current capacity of the set.
     *
     * @return The capacity of the set.
     */
    public int getCapacity(){
        return capacity;
    }
    
    /**
     * Returns an iterator over the elements in the set.
     *
     * @return An iterator for iterating over the elements in the set.
     */
    @Override
    public Iterator<T> getIterator() {
        return new JavaSetIterator();
    }

    /**
     * Returns a string representation of the set.
     *
     * @return A string representation of the set.
     */
    @Override
    public String toString() {
        StringBuilder result = new StringBuilder("elements=[");
        for (int i = 0; i < size; i++) {
            result.append(elements[i]);
            if (i < size - 1) {
                result.append(", ");
            }
        }
        result.append("], size=").append(size).append(", capacity=").append(capacity).append('}');
        return result.toString();
    }

    /**
     * Checks if the current set is equal to another object.
     *
     * @param obj The object to compare with the current set.
     * @return {@code true} if the sets are equal, {@code false} otherwise.
     */
    @Override
    @SuppressWarnings("unchecked")
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || this.getClass() != obj.getClass()) return false;
    
        JavaSet<T> javaSet = (JavaSet<T>) obj;
        if (this.size != javaSet.size) return false;
    
        // Check if all elements in this set are present in the other set
        for (var element : elements) {
            if(element == null) break;
            if (!javaSet.isInside(element)) {
                return false;
            }
        }
        return true;
    }
    

    /**
     * Checks if the specified element is already present in the set.
     *
     * @param searchedElement The element to check for existence in the set.
     * @return {@code true} if the element is found in the set, {@code false} otherwise.
     */
    private boolean isInside(T searchedElement) {
        for (var element : elements) {
            if(element == null) break;
            if (element != null && element.equals(searchedElement)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Iterator for JavaSet.
     */
    private class JavaSetIterator implements Iterator<T> {
        private int currentIndex = 0;
        
        /**
         * Checks if there are more elements in the set.
         *
         * @return {@code true} if there are more elements, {@code false} otherwise.
         */
        @Override
        public boolean hasNext() {
            return currentIndex < size;
        }
        
        /**
         * Retrieves the next element in the iteration.
         *
         * @return The next element in the iteration.
         * @throws IllegalStateException If there are no more elements in the set.
         */
        @Override
        public T next() {
            if (!hasNext()) {
                throw new IllegalStateException("No more elements in the set.");
            }
            return elements[currentIndex++];
        }
    }
}