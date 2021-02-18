/**
 *this is an abstract class for the game
 */
public abstract class AbstractBoard {
    public static int Number_Of_Boards = 0;
    public static int number_Of_Moves = 0;
    public static char last_Move = 'S';

    /**
     * toString method for the objects
     * @return like a string the object's board
     */
    @Override
    public abstract String toString();

    /**
     * Resets the board to the solution.
     */
    public abstract void reset();

    /**
     * Sets the board size to given values. The values are given as parameters
     * and there are no restrictions on the board size
     * @param size1 first value for set
     * @param size2 second value for set
     */
    public abstract void setSize(int size1, int size2);

    /**
     * Reads the board from the file given as function parameter.
     * @param fileName name of file to read
     */
    public abstract void readFromFile(String fileName);

    /**
     * Takes two indexes and returns the corresponding cell content
     * @param i  first index to check
     * @param j second index to check
     * @return the corresponding cell content
     */
    public abstract int cell(int i, int j);

    /**
     * check is the board is a solution
     * @return true if the board is a solution
     */
    public abstract boolean isSolved();

    /**
     * Makes a move according to the given char parameter
     * @param m is the move route
     * @return 0 if the move is not legal, otherwise 1
     */
    public abstract int move(char m);

    /**
     * writes the board to the file given as function parameter
     * @param fileName name of file to write
     */
    public abstract void writeToFile(String fileName);

    /**
     * Two boards are equal, if the boards are the same
     * @param otherObject object to compare
     * @return true if they are same, otherwise returns false
     */
    public abstract boolean Equals(AbstractBoard otherObject);

    /**
     * geting the space index i
     * @return space's i location
     */
    public abstract int getSpacei();

    /**
     * geting the space index j
     * @return space's j location
     */
    public abstract int getSpacej();

    /**
     * getting the size1
     * @return the size1
     */
    public abstract int getSize1();

    /**
     * getting the size2
     * @return the size2
     */
    public abstract int getSize2();

    /**
     * method that gives number of boards
     * @return number of created boards so far
     */
    public int NumberOfBoards() {
        return Number_Of_Boards;
    }

    /**
     *  method that gives the last move
     * @return the last move
     */
    public char lastMove() {
        return last_Move;
    }

    /**
     * method that gives number of total moves
     * @return the number of moves
     */
    public int NumberOfMoves() {
        return number_Of_Moves;
    }

}