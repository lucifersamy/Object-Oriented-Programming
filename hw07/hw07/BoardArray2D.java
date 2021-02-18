import java.io.*;
import java.io.IOException;

/**
 * this class is the extends of an AbstractBoard for the game
 * it is has the data 2D array
 */
public class BoardArray2D extends AbstractBoard {
    private int[][] board;
    private int[] space;
    private int size1;
    private int size2;

    /**
     * no parameter constructor
     */
   public BoardArray2D ()
    {
        Number_Of_Boards++;
        space = new int[3];
        int[][] board = new int[9][9];
    }
    public boolean Equals(AbstractBoard otherObject) {
        BoardArray2D newObj = (BoardArray2D) otherObject;
        if(size1 != newObj.size1 || size2 != newObj.size2)
            return false;
        for (int i = 0; i < size1; ++i)
        {
            for (int j = 0; j < size2; ++j)
            {
                if(board[i][j] != newObj.board[i][j])
                    return false;
            }
        }
        if(size1 == newObj.size1 && size2 == newObj.size2)
            return true ;
        else
            return false;
    }

    /**
     * getting the size1
     * @return the size1
     */
    public int getSize1()
    {
        return size1;
    }
    /**
     * getting the size2
     * @return the size2
     */
    public int getSize2()
    {
        return size2;
    }
    /**
     * toString method for the objects
     * @return like a string the object's board
     */
    public String toString()
    {
        String boardStr = "";

        for (int i = 0; i < size1; i++) {
            for (int j = 0; j < size2; j++) {
                if (board[i][j] == -1) {
                   boardStr += "bb ";
                }
                if (board[i][j] < 10 && board[i][j] != -1) {
                    boardStr += String.valueOf(0);
                    boardStr += String.valueOf(board[i][j]);
                    boardStr += " ";
                } else if (board[i][j] != -1) {
                    boardStr += String.valueOf(board[i][j]);
                    boardStr += " ";
                }
            }
            boardStr += "\n";
        }
        return boardStr;
    }

     /**
     * Takes two indexes and returns the corresponding cell content
     * @param i  first index to check
     * @param j second index to check
     * @return the corresponding cell content
     */
    public int cell (int i, int j)
    {

        return (board[i][j]);
    }
    /**
     * Sets the board size to given values. The values are given as parameters
     * and there are no restrictions on the board size
     * @param size1 first value for set
     * @param size2 second value for set
     */
    public void setSize(int size1, int size2)
    {
        board = new int[size1][size2];
        space = new int[2];
    }
    /**
     * Resets the board to the solution.
     */
    public void reset()
    {
        int a=1;
        for (int i = 0; i < size1; ++i)
        {
            for (int j = 0; j < size2; ++j)
            {
                if(board[i][j] != 0)
                {
                    board[i][j] = a;
                    a++;
                }
            }
        }
        board[size1-1][size2-1] = -1;
        space[0]=size1-1;
        space[1]=size2-1;
    }
    /**
     * geting the space index i
     * @return space's i location
     */
    public int getSpacei(){
        return space[0];
    }

    /**
     * geting the space index j
     * @return space's j location
     */
    public int getSpacej(){
        return space[1];
    }
     /**
     * check is the board is a solution
     * @return true if the board is a solution
     */
    public boolean isSolved()
    {
        int a=1;
        //is board final solution
        for(int i=0; i<size1; ++i)
        {
            for(int j=0; j<size2; ++j)
            {
                if((i == size1-1 && j == size2-1 )){}
                else if(board[i][j] == 0){}
                else if(board[i][j]!= a)
                    return false;
                else
                    a++;
            }
        }
        return true;
    }

    /**
     * Reads the board from the file given as function parameter.
     * @param fileName name of file to read
     */
    public void readFromFile(String fileName) {

        int i = 0, j = 0, flag1 = 1;
        int indexBuffer = 0;
        String buffer = new String();

        try {
            FileReader folder = new FileReader(fileName);
            BufferedReader br = new BufferedReader(folder);
            while ((buffer = br.readLine()) != null){
                indexBuffer = 0;
                while (indexBuffer < buffer.length() ) {
                    if (indexBuffer != 0)
                        size2 = j + 1;
                    indexBuffer += 3;
                    j++;
                }
                i++;
                j = 0;
            }

            if (flag1 == 1) {
                size1 = i ;
                flag1 = 0;
            }
            folder.close();

            i = 0;
            j = 0;
            flag1 = 1;
            indexBuffer = 0;
            setSize(size1,size2);

            folder = new FileReader(fileName);
            br = new BufferedReader(folder);

            while ((buffer = br.readLine()) != null) {
                indexBuffer = 0;
                while (indexBuffer < buffer.length()) {
                    if (buffer.charAt(indexBuffer) == 'b') {
                        board[i][j] = -1;
                        space[0] = i;
                        space[1] = j;
                    } else
                        board[i][j] = (buffer.charAt(indexBuffer) - 48) * 10 + buffer.charAt(indexBuffer + 1) - 48;

                    indexBuffer += 3;
                    j++;
                }
                i++;
                j = 0;
            }
            folder.close();
        }
        catch(IOException e) {

            System.out.println("An error occurred.");
            System.exit(1);
        }
    }

    /**
     * writes the board to the file given as function parameter
     * @param fileName name of file to write
     */
    public void writeToFile(String fileName)
    {
        try {
            FileWriter myWriter = new FileWriter(fileName);
            myWriter.write(toString());
            myWriter.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    /**
     * Makes a move according to the given char parameter
     * @param m is the move route
     * @return 0 if the move is not legal, otherwise 1
     */
    public int move(char m)
    {
        int temp;
        /*swapping the empty cell with direction is choosen using i and j. for all directions*/
        /*if there is no room returns 0*/

        if(m == 'R'){
            if(space[1]+1 == size2 || board[space[0]][space[1]+1] == 0)
                return 0;
            else
            {
                last_Move = 'R';
                number_Of_Moves++;
                temp = board[space[0]][space[1]+1];
                board[space[0]][space[1]+1] = board[space[0]][space[1]];
                board[space[0]][space[1]] = temp;
                space[1]++;
            }
        }
        else if(m == 'L'){
            if(space[1]-1 == -1 || board[space[0]][space[1]-1] == 0)
                return 0;
            else
            {
                last_Move = 'L';
                number_Of_Moves++;
                temp = board[space[0]][space[1]-1];
                board[space[0]][space[1]-1] = board[space[0]][space[1]];
                board[space[0]][space[1]] = temp;
                space[1]--;
            }
        }
        else if(m == 'U'){
            if(space[0]-1 == -1 || board[space[0]-1][space[1]] == 0)
                return 0;
            else{
               last_Move = 'U';
                number_Of_Moves++;
                temp = board[space[0]-1][space[1]];
                board[space[0]-1][space[1]] = board[space[0]][space[1]];
                board[space[0]][space[1]] = temp;
                space[0]--;
            }
        }
        else if(m == 'D'){
            if(space[0]+1 == size1 || board[space[0]+1][space[1]] == 0)
                return 0;
            else
            {
                last_Move = 'D';
                number_Of_Moves++;
                temp = board[space[0]+1][space[1]];
                board[space[0]+1][space[1]] = board[space[0]][space[1]];
                board[space[0]][space[1]] = temp;
                space[0]++;
            }
        }
        return 1;
    }

}
