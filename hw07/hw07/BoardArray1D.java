import java.io.BufferedReader;
import java.io.FileReader;
import java.io.*;
import java.io.IOException;

/**
 * this class is the extends of an AbstractBoard for the game
 * it is has the data 1D array
 */
public class BoardArray1D extends AbstractBoard{
    private int size1;
    private int size2;
    private int []board;
    private int space;

    /**
     * no parameter constructor
     */
    public BoardArray1D()
    {
        Number_Of_Boards++;
        board = new int[9];
    }

    /**
     * toString method for the objects
     * @return like a string the object's board
     */
    public String toString()
    {
        String boardStr = "";

        int x=0;
        for(int i=0; i<size1; i++) {
            for (int j = 0; j < size2; j++) {
                if (i == size1 - 1 && j == size2 - 1) {
                    if (board[x] == -1)
                        boardStr += "bb";
                    else if (board[x] < 10) {
                        boardStr += String.valueOf(0);
                        boardStr += String.valueOf(board[x]);
                    } else {
                        boardStr += String.valueOf(board[x]);
                    }
                } else {
                    if (board[x] == -1)
                        boardStr += "bb ";
                    else if (board[x] < 10) {
                        boardStr += String.valueOf(0);
                        boardStr += String.valueOf(board[x]);
                        boardStr += " ";
                    } else if (board[x] != -1) {
                        boardStr += String.valueOf(board[x]);
                        boardStr += " ";
                    }
                    x++;
                }
            }
            boardStr += "\n";
        }
        return boardStr;
    }

    /**
     * Makes a move according to the given char parameter
     * @param m is the move route
     * @return 0 if the move is not legal, otherwise 1
     */
    public int move(char m) {
        int temp;
        /*swapping the empty cell with direction is choosen using i and j. for all directions*/
        /*if there is no room returns 0*/

        if(m == 'R'){
            if( (space+1)%size2 == 0 || board[space+1] == 0)
                return 0;

            else
            {
                last_Move = 'R';
                number_Of_Moves++;
                temp = board[space];
                board[space] = board[space+1];
                board[space+1] = temp;
                space++;
            }
        }

        else if(m == 'L'){
            if((space)%size2 == 0 || board[space-1] == 0)
                return 0;
            else
            {
                last_Move = 'L';
                number_Of_Moves++;
                temp = board[space];
                board[space] = board[space-1];
                board[space-1] = temp;
                space--;
            }
        }
        else if(m == 'U'){
            if(board[space-size2] == 0 || space < size2)
                return 0;
            else{
                last_Move = 'U';
                number_Of_Moves++;
                int tempSpace = space;
                temp = board[space];
                board[space] = board[space-size2];
                board[space-size2] = temp;
                space = tempSpace - size2;
            }
        }
        else if(m == 'D'){
            if(board[space+size2] == 0 || space > (size1*size2-size1))
                return 0;
            else
            {
                last_Move = 'D';
                number_Of_Moves++;
                int tempSpace = space;
                temp = board[space];
                board[space] = board[space+size2];
                board[space+size2] = temp;
                space = tempSpace + size2;
            }
        }
        return 1;
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
     * check is the board is a solution
     * @return true if the board is a solution
     */
    public boolean isSolved(){
        int a=1,x=0;
        for(int i=0; i<size1; ++i)
        {
            for(int j=0; j<size2; ++j)
            {
                if((i == size1-1 && j == size2-1 )){}
                else if(board[x] == 0){}
                else if(board[x]!= a)
                    return false;
                else
                    a++;
                x++;
            }
        }
        return true;
    }

    /**
     * geting the space index i
     * @return space's i location
     */
    public int getSpacei(){
        if(size2 != 0)
          return space/size2;
        else
            return 0;
    }

    /**
     * getting the space index j
     * @return space's j location
     */
    public int getSpacej(){
        if(size2 != 0)
            return space%size2;
        else
            return 0;
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
     * getting the size1
     * @return the size2
     */
    public int getSize2()
    {
        return size2;
    }

    /**
     * Reads the board from the file given as function parameter.
     * @param fileName name of file to read
     */
    public void readFromFile(String fileName)
    {
        int i=0, j=0,flag1=1,x=0;
        int indexBuffer=0;
        String buffer;

        try {
            FileReader folder = new FileReader(fileName);
            BufferedReader br = new BufferedReader(folder);
            while ((buffer = br.readLine()) != null) {
                indexBuffer = 0;
                while (indexBuffer < buffer.length()) {
                    if (indexBuffer != 0)
                        size2 = j + 1;
                    indexBuffer += 3;
                    j++;
                }
                i++;
                j = 0;
            }

            if (flag1 == 1) {
                size1 = i;
                flag1 = 0;
            }

            folder.close();
            i = 0;
            j = 0;
            flag1 = 1;
            x = 0;
            indexBuffer = 0;

            setSize(size1,size2);

            folder = new FileReader(fileName);
            br = new BufferedReader(folder);

            while ((buffer = br.readLine()) != null){
                indexBuffer = 0;
                while (indexBuffer < buffer.length()) {
                    if (buffer.charAt(indexBuffer) == 'b') {
                        board[x] = -1;
                        space = x;
                    } else
                        board[x] = (buffer.charAt(indexBuffer) - 48) * 10 + (buffer.charAt(indexBuffer + 1) - 48);

                    indexBuffer += 3;
                    j++;
                    x++;
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
     * Two boards are equal, if the boards are the same
     * @param otherObject object to compare
     * @return true if they are same, otherwise returns false
     */
    public boolean Equals(AbstractBoard otherObject){
        BoardArray1D compareObj = (BoardArray1D) otherObject;
        if(size1 != compareObj.size1 || size2 != compareObj.size2)
            return false;
        for (int i = 0; i < size1*size2; ++i)
        {
            if(board[i] != compareObj.board[i])
                return false;
        }
        return true ;
    }

    /**
     * Takes two indexes and returns the corresponding cell content
     * @param i  first index to check
     * @param j second index to check
     * @return the corresponding cell content
     */
    public int cell (int i, int j)
    {
        int d;
        d =  (board[(i*size2)+j]);
        return d;
    }

    /**
     * Resets the board to the solution.
     */
    public void reset(){
        int a=1;
        for (int i = 0; i < size1*size2; ++i)
        {
            if(board[i] != 0)
            {
                board[i] = a;
                a++;
            }
        }

        board[size1*size2-1] = -1;
        space=size1*size2-1;
    }

    /**
     * Sets the board size to given values. The values are given as parameters
     * and there are no restrictions on the board size
     * @param size1 first value for set
     * @param size2 second value for set
     */
    public void setSize(int size1, int size2)
    {
        board = new int[size1*size2];
    }

}
