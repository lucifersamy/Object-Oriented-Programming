#include "boardvector.h"

namespace Game
{
	BoardVector::BoardVector()
	{
		Number_Of_Boards++;
		space.resize(3);
		Number_Of_Boards++;
	} 
	
	void BoardVector::print() const
	{
		for(int i=0; i<board.size(); i++)
		{
			for(int j=0; j<board[0].size(); j++)
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

	void BoardVector::readFromFile(const string fileName)
	{	
		ifstream folder;
		
		auto i=0, j=0,flag1=1;
		auto indexBuffer=0;									
		string buffer;
		int size1,size2;
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

		setSize(size1,size2);

		folder.open(fileName.c_str());
		i=0, j=0,flag1=1,indexBuffer=0;
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

	void BoardVector::writeToFile(const string fileName) const
	{
		ofstream folder1;
		folder1.open(fileName.c_str());

		for(int i=0; i<board.size(); i++)
		{
			for(int j=0; j<board[0].size(); j++)
			{	
				if(i == board.size()-1 && j == board[0].size()-1){
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
		folder1.close();
	}

	void BoardVector::reset()
	{
		auto a=1;	
		for (int i = 0; i < board.size(); ++i)
		{
			for (int j = 0; j < board[0].size(); ++j)
			{
				if(board[i][j] != 0)
				{
					board[i][j] = a;
					a++;
				}
				
			}
		}
		board[board.size()-1][board[0].size()-1] = -1;
		print();
		space[0]=board.size()-1;
		space[1]=board[0].size()-1;
		//gameBoard.back().resize(0)
	}

	void BoardVector::setSize(int size1,int size2)
	{

		board.resize(size1);
		for(int j=0; j<size1; j++)
			board[j].resize(size2);

	}

	int BoardVector::move(char m)
	{
		int temp;
		/*swapping the empty cell with direction is choosen using i and j. for all directions*/
		/*if there is no room returns 0*/

		if(m == 'R'){
			if(space[1]+1 == board[0].size() || board[space[0]][space[1]+1] == 0)	
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
			if(space[0]+1 == board.size() || board[space[0]+1][space[1]] == 0)
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

	bool BoardVector::isSolved() const
	{
		int a=1;
		//is board final solution
		for(int i=0; i<board.size(); ++i)
		{
			for(int j=0; j<board[0].size(); ++j)
			{
				if((i == board.size()-1 && j == board[0].size()-1 )){}
				else if(board[i][j] == 0){}
				else if(board[i][j]!= a)
					return false;
				else
					a++;		
			}
		}

		return true;
	}

	int BoardVector::operator() (int i, int j) const
	{
		return (board[i][j]);
	}

	bool BoardVector::operator == (const BoardVector& other) 
	{
		for (int i = 0; i < board.size(); ++i)
		{
			for (int j = 0; j < board[0].size(); ++j)
			{
				if(operator()(i,j) != other.operator()(i,j))
						return false;
			}
		}
		
		return true ;
	}

}

