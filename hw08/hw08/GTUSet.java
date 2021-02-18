/**
 * It is GTUSet container as a Set
 * @param <E> Generic type of class
 */
public class GTUSet <E> extends GTU_CONTAINER <E> {
    /**
     * No parameter constructor
     */
    public GTUSet()
    {
        this.capacity = 10;
        this.used = 0;
        this.data = (E[]) new Object[this.capacity];
    }

    /**
     *
     * @return true if the set has no element, otherwise returns false
     */
    public boolean empty()
    {
        if(this.used != 0)
            return false;
        return true;
    }

    /**
     * method that finds max size
     * @return maximum size
     */
    public int max_size()
    {
        return 200000;
    }

    /**
     * method that gives used size
     * @return the current used size
     */
    public int size()
    {
        return this.used;
    }

    /**
     * method that add an element to set
     * @param element that is an T type element for adding to set
     * @throws IllegalArgumentException exception for if element is already in set
     */
    public void insert(E element) throws IllegalArgumentException  {
        boolean flag = true;

        for(int i = 0;i < this.used;i++)
        {
            if(this.data[i] == element)
            {
                flag = false;
            }
        }

        if(this.used >= this.capacity && flag) {
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
        else if(flag)
        {
            this.data[this.used] = element;
            this.used++;
        }
        if(!flag)
            throw new IllegalArgumentException("error occured");
    }

    /**
     * erase an element from set
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
     * method that clears all set
     */
    public void clear()
    {
        this.used = 0;
        this.data = null;
    }

    /**
     * method that find the object in set
     * @param o is the object that is checked is in already in set
     * @return true if o is in already in set, otherwise returns false
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
     * find iterator to beginning
     * @return iterator to beginning
     */
    @Override
    public GTUIterator<E> iterator() {
        return new GtuSetIterator<>();
    }

    /**
     * this is an inner class for iterator
     * @param <E> Generic type of class
     */
    public class GtuSetIterator <E> implements GTUIterator <E>
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
