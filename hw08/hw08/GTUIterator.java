/**
 * an interface for iterator that has hasNext and next methods
 * @param <E> Generic type of class
 */
public interface GTUIterator <E> {
    public abstract boolean hasNext();
    public abstract E next();
}
