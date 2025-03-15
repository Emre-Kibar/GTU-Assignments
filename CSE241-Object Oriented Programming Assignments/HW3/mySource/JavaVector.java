package mySource;
import myInterface.JavaContainer;
import java.util.Iterator;

/**
 * JavaVector class implementing JavaContainer interface.
 *
 * @param <T> Type of elements in the vector.
 */
public class JavaVector<T> implements JavaContainer<T> {
    private T[] elements;
    private int size;
    private int capacity;

    /**
     * Constructs a JavaVector with a default initial capacity of 10.
     */
    public JavaVector() {
        this(10);
    }

    /**
     * Constructs a JavaVector with the specified initial capacity.
     *
     * @param capacity The initial capacity of the vector.
     */
    @SuppressWarnings("unchecked")
    public JavaVector(int capacity) {
        this.size = 0;
        this.capacity = capacity;
        elements = (T[])new Object[this.capacity]; // initial capacity
    }

    /**
     * Adds an element to the vector.
     *
     * @param element The element to be added.
     */
    @Override
    @SuppressWarnings("unchecked")
    public void add(T element) {
        if (size == capacity) {
            capacity = capacity * 2;
            T[] temp = elements;
            elements = (T[])new Object[capacity];
            for(int i=0; i < size ; i++){
                elements[i] = temp[i];
            }
        }
        elements[size++] = element;
    }

    /**
     * Removes the specified element from the vector.
     *
     * @param element The element to be removed.
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
     * Returns the size of the vector.
     *
     * @return The size of the vector.
     */
    @Override
    public int Size() {
        return size;
    }

    /**
     * Returns the capacity of the vector.
     *
     * @return The capacity of the vector.
     */
    public int getCapacity(){
        return capacity;
    }

    /**
     * Returns an iterator over the elements in the vector.
     *
     * @return An iterator.
     */
    @Override
    public Iterator<T> getIterator() {
        return new JavaVectorIterator();
    }

    /**
     * Returns a string representation of the vector.
     *
     * @return A string representation of the vector.
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
     * Checks if the vector is equal to another object.
     *
     * @param obj The object to compare with the vector.
     * @return {@code true} if the vector is equal to the object, {@code false} otherwise.
     */
    @Override
    @SuppressWarnings("unchecked")
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        JavaVector<T> javaVector = (JavaVector<T>) obj;
        if (this.size != javaVector.size) return false;
        for(int i=0; i < size; i++){
            if (!elements[i].equals(javaVector.elements[i])) {
                return false;
            }
        }
        return true;
    }

    /**
     * Iterator for iterating over the elements in the JavaVector.
     */
    private class JavaVectorIterator implements Iterator<T> {
        private int currentIndex = 0;
        
        /**
         * Checks if there are more elements in the vector.
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
         * @throws IllegalStateException If there are no more elements in the vector.
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