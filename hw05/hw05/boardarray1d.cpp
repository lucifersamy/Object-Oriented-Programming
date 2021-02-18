#include "boardarray1d.h"

namespace Game
{
	BoardArray1D :: BoardArray1D()
	{
		Number_Of_Boards++;
		board = new int[9];
	}

	BoardArray1D :: BoardArray1D(const BoardArray1D& boardArrayObject)
	{
		
		space = boardArrayObject.space;

		board = new int[size1*size2];
		for(int i = 0; i<3; ++i)
			board[i] = boardArrayObject.board[i];

		size1 = boardArrayObject.size1;
		size2 = boardArrayObject.size2;
	}

	void BoardArray1D :: readFromFile(const string fileName)
	{

		ifstream folder;

		auto i=0, j=0,flag1=1,x=0;
		auto indexBuffer=0;									
		string buffer;

		folder.open(fileName.c_str());
		do
		{
			getline (folder, buffer);	
			indexBuffer = 0;
			while(indexBuffer<buffer.size()){
				if(indexBuffer != 0)
					size2 = j+1;
				indexBuffer += 3;
				j++;
			}
			i++;
			j=0;
		}while(!folder.eof());

		if(flag1){
			size1 = i-1;
			flag1 =0; 
		}

		folder.close();
		i=0, j=0,flag1=1,x=0;
		indexBuffer=0;
		
		setSize(size1,size2);								

		folder.open(fileName.c_str());
		do
		{
			getline (folder, buffer);	
			indexBuffer = 0;
			while(indexBuffer<buffer.size()){
				if(buffer.at(indexBuffer) == 'b'){
					board[x] = -1;
					space = x;
				}
				else
					board[x] = (buffer.at(indexBuffer)-48) * 10 + (buffer.at(indexBuffer+1)-48);
			
				indexBuffer += 3;
				j++;
				x++;
			}
			i++;
			j=0;
		}while(!folder.eof());
	
		folder.close();

	}
	void BoardArray1D :: writeToFile(const string fileName) const
	{
		ofstream folder1;
		folder1.open(fileName.c_str());
		int x=0;
		for(int i=0; i<size1; i++)
		{
			for(int j=0; j<size2; j++)
			{	
				if(i == size1-1 && j == size2-1){
					if(board[x] == -1)
						folder1<<"bb";
					else if(board[x] < 10)
						folder1<< 0<< board[x];
					else
						folder1<<board[x];
				}
				else
				{
					if(board[x] == -1)
						folder1<<"bb	";
					else if(board[x] < 10)
						folder1<< 0 << board[x] << "	";
					else if(board[x] != -1)
						folder1<< board[x] << "	";
				}
				x++;
			}
			folder1 << endl;
		}
	}
	void BoardArray1D :: print() const
	{
		int x=0;
		for(int i=0; i<size1; i++)
		{
			for(int j=0; j<size2; j++)
			{	
				if(i == size1-1 && j == size2-1){
					if(board[x] == -1)
						cout<<"bb";
					else if(board[x] < 10)
						cout<< 0<< board[x];
					else
						cout<<board[x];
				}

				else
				{
					if(board[x] == -1)
						cout<<"bb	";
					else if(board[x] < 10)
						cout<< 0 << board[x] << "	";
					else if(board[x] != -1)
						cout<< board[x] << "	";
				}
				x++;
			}
			cout << endl;
		}
	}
	void BoardArray1D :: reset()
	{
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
		print();
		space=size1*size2-1;
	}
	void BoardArray1D :: setSize(int size1, int size2)
	{
		delete [] board;
		board = new int[size1*size2];
	}
	int BoardArray1D :: move(char m)
	{
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

	bool BoardArray1D :: isSolved() const
	{
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

	bool BoardArray1D :: operator == (const BoardArray1D& other)
	{
		for (int i = 0; i < size1*size2; ++i)
		{
			if(board[i] != other.board[i])
					return false;
		}
		return true ;
	}
	
	BoardArray1D& BoardArray1D :: operator = (const BoardArray1D& rightSide) //assign op
	{
		size1 = rightSide.size1;
		size2 = rightSide.size2;


		space = rightSide.space;

		board = new int[size1*size2];
		
		for (int i = 0; i < size1*size2; ++i)
		{
				board[i] = rightSide.board[i];
		}

		return *this;
	}

	BoardArray1D :: ~BoardArray1D(){
		delete [] board;
	}
}