/**
 * It is GTUSet container as a Vector
 * @param <E> Generic type of class
 */
public class GTUVector  <E> extends GTU_CONTAINER <E> {
    /**
     *  No parameter constructor
     */
    public GTUVector()
    {
        this.capacity = 10;
        this.used = 0;
        this.data = (E[]) new Object[this.capacity];
    }

    /**
     * Test whether container is empty
     * @return true if vector is empty otherwise returns false
     */
    public boolean empty(){
        if(this.used != 0)
            return false;
        return true;
    }

    /**
     * method that add an element to vector
     * @param element that is an T type element for adding to vector
     */
    public void insert(E element){

        if(this.used >= this.capacity){
            E[] temp = (E[]) new Object[this.capacity];
            for (int i = 0; i < used; ++i) {
                temp[i] = this.data[i];
            }
            this.capacity *= 2;
            this.data = (E[]) new Object[this.capacity];
            int i = 0;
            for (i = 0; i < used; ++i) {
                this.data[i] = temp[i];
            }
            this.data[this.used] = element;
            this.used++;
        }
        else{
            this.data[this.used] = element;
            this.used++;
        }
    }

    /**
     *method that finds max size
     * @return maximum size
     */
    public int max_size()
    {
        return 200000;
    }

    /**
     * method that finds size
     * @return size
     */
    public int size()
    {
        return this.used;
    }

    /**
     * erase an element from vector
     * @param element is the item of that should be erase
     */
    public void erase(E element)
    {
        int location = 0;
        for(int i=0; i<used; ++i)
        {
            if(element == data[i])
            {
                location = i;
            }
        }

        for(int j = location; j<=used; j++)
        {
            data[j] = data[j+1];
        }
        this.used--;

    }

    /**
     * method that clears all vector
     */
    public void clear()
    {
        this.used = 0;
        this.data = null;
    }

    /**
     * find iterator to beginning
     * @return iterator to beginning
     */
    @Override
    public GTUIterator<E> iterator() {
        return new GtuVectorIterator<>();
    }

    /**
     * method that find the object in vector
     * @param o is the object that is checked is in already in vector
     * @return true if o is in already in vector, otherwise returns false
     */
    public boolean contains(Object o)
    {
        for(int i=0; i<used; ++i)
        {
            if(data[i] == o)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * his is an inner class for iterator
     * @param <E>  Generic type of class
     */
    public class GtuVectorIterator <E> implements GTUIterator <E>
    {
        private int current_position = 0;

        /**
         * method is find iteration has more elements.
         * @return true if the iteration has more elements, otherwise returns false
         */
        @Override
        public boolean hasNext() {
            if(current_position < used)
                return true;
            else
                return false;
        }

        /**
         * find the next element in the iteration
         * @return the next element in the iteration.
         */
        @Override
        public E next() {
            E temp=(E) data[current_position];
            current_position++;
            return  temp;
        }
    }


}
