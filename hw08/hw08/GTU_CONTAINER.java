/**
 *An abstract class Container
 * @param <E> Generic type of class
 */
public abstract class GTU_CONTAINER <E>{
    protected int capacity;
    protected int used;
    protected E [] data;

    /**
     * Test whether container is empty
     * @return true if container is empty, otherwise returns false
     */
    public abstract boolean empty();

    /**
     * Insert element to container
     * @param element that should be insert to container
     */
    public abstract void insert(E element);

    /**
     *finds container size
     * @return size
     */
    public abstract int size();

    /**
     * find container max size
     * @return container max size
     */
    public abstract int max_size();

    /**
     * erase the element
     * @param element that should be erased element
     */
    public abstract  void erase(E element);

    /**
     * clear all container
     */
    public abstract void clear();

    /**
     * find iterator to beginning
     * @return iterator to beginning
     */
    public abstract GTUIterator<E> iterator();

    /**
     * method that find the object in collection
     * @param o is the object that is checked is in already in collection
     * @return true if o is in already in collection, otherwise returns false
     */
    public abstract boolean contains(Object o);
}

