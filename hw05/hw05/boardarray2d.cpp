#include "boardarray2d.h"

namespace Game
{
	BoardArray2D :: BoardArray2D ()
	{
		Number_Of_Boards++;
		space = new int[3];

		board = new int*[9];
		for(int i = 0; i < 9; ++i)
			board[i] = new int[9];

	}

	BoardArray2D :: BoardArray2D(const BoardArray2D& boardArrayObject)	//copy constructor
	{

		space = new int[3];
		for(int i = 0; i<3; ++i)
			space[i] = boardArrayObject.space[i];

		size1 = boardArrayObject.size1;
		size2 = boardArrayObject.size2;

		board = new int*[size1];
		for(int i = 0; i < size1; ++i)
			board[i] = new int[size2];

		for (int i = 0; i < size1; ++i)
		{
			for(int j = 0; j < size2; ++j)
			{
				board[i][j] = boardArrayObject.board[i][j];
			}
		}
	}

	BoardArray2D ::  ~BoardArray2D ()
	{
		delete [] space;

		for(int i = 0; i < size1; ++i)
		{
			delete [] board[i];
		}
		delete [] board;
	}

	BoardArray2D& BoardArray2D :: operator = (const BoardArray2D& rightSide)
	{
		size1 = rightSide.size1;
		size2 = rightSide.size2;

		for(int i = 0; i<3; ++i)
			space[i] = rightSide.space[i];
		
		for (int i = 0; i < size1; ++i)
		{
			for(int j = 0; j < size2; ++j)
			{
				board[i][j] = rightSide.board[i][j];
			}
		}

		return *this;
	}

	void BoardArray2D::print() const{
		for(int i=0; i<size1; i++)
		{
			for(int j=0; j<size2; j++)
			{
				if(board[i][j] == -1)
					cout<<"bb	";
				if(board[i][j] < 10 && board[i][j] != -1)
					cout<< 0 << board[i][j] << "	";
				else if(board[i][j] != -1)
					cout<< board[i][j] << "	";
			}
			cout<< endl;
		}
	}

	void BoardArray2D::readFromFile(const string fileName)
	{
		ifstream folder;

		auto i=0, j=0,flag1=1;
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
	
		i=0, j=0,flag1=1;
		indexBuffer=0;
		
		setSize(size1,size2);
		
		folder.open(fileName.c_str());
		do
		{
			getline (folder, buffer);
			indexBuffer = 0;
			while(indexBuffer<buffer.size()){
				if(buffer.at(indexBuffer) == 'b'){
					board[i][j] = -1;
					space[0] = i;
					space[1] = j;
				}
				else
					board[i][j] = (buffer.at(indexBuffer)-48) * 10 + buffer.at(indexBuffer+1)-48;

				indexBuffer += 3;
				j++;
			}
			i++;
			j=0;
		}while(!folder.eof());

		folder.close();
	}

	void BoardArray2D::writeToFile(const string fileName) const
	{
		ofstream folder1;
		folder1.open(fileName.c_str());
		for(int i=0; i<size1; i++)
		{
			for(int j=0; j<size2; j++)
			{	
				if(i == size1-1 && j == size2-1){
					if(board[i][j] == -1)
						folder1<<"bb";
					else if(board[i][j] < 10)
						folder1<< 0<< board[i][j];
					else
						folder1<<board[i][j];
				}

				else
				{
					if(board[i][j] == -1)
						folder1<<"bb	";
					else if(board[i][j] < 10)
						folder1<< 0 << board[i][j] << "	";
					else if(board[i][j] != -1)
						folder1<< board[i][j] << "	";
				}
			}
			folder1 << endl;
		}
	}

	void BoardArray2D::reset()
	{
		auto a=1;	
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
			cout << endl;
		}
		board[size1-1][size2-1] = -1;
		print();
		space[0]=size1-1;
		space[1]=size2-1;
	}
	void BoardArray2D::setSize(int size1, int size2)
	{
		for(int i = 0; i < 9; ++i)
		{
			delete [] board[i];
		}
		delete [] board;
		board = new int*[size1];
		for(int i = 0; i < size1; ++i)
			board[i] = new int[size2];

	}

	int BoardArray2D::move(char m)
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

	bool BoardArray2D::isSolved() const
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

	int BoardArray2D::operator () (int i, int j) const
	{
		return (board[i][j]);
	}

	bool BoardArray2D::operator == (const BoardArray2D& other) 
	{
		for (int i = 0; i < size1; ++i)
		{
			for (int j = 0; j < size2; ++j)
			{
				if(operator()(i,j) != other.operator()(i,j))
						return false;
			}
		}
		if(size1 == other.size1 && size2 == other.size2)
			return true ;
		else
			return false;
	}

}