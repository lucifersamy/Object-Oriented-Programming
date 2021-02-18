#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <cmath>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

class NPuzzle
{
private:
	class Board
	{
	public:
		Board(int getsize);
		int totalNumberGetter(){return totalNumber;}
		void print() const;
		int readFromFile(const string fileName);
		void writeToFile(const string fileName) const;
		void reset();
		void setSize(const int sizefromUser);
		int move(const char m);
		bool isSolved() const;
		bool isSolvable(const int control[]) const;
		static char lastMove(const char move);
		static int numberOfMoves(const int isV);
		static int numberOfBoards();
		const int operator () (const int i ,const int j);
		bool operator == (const Board& board1);
		void operator = (const Board &B);
		inline int getsizeshuffle(){return board.size() * board[0].size();}
		friend istream& operator>>(istream& is, Board& myBoard){			
			myBoard.isFromFolder=1;
			auto i=0, j=0,flag1=1;
			auto indexBuffer=0;									
			string buffer;
			int temp[9][9];
			int size1,size2;

			do
			{	
				getline (is, buffer);	
				indexBuffer = 0;
				while(indexBuffer<buffer.size()){
					if(buffer.at(indexBuffer) == 'b'){
						temp[i][j] = -1;
						myBoard.space[0] = i;
						myBoard.space[1] = j;
					}
					else
						temp[i][j] = (buffer.at(indexBuffer)-48) * 10 + buffer.at(indexBuffer+1)-48;
										
					if(indexBuffer != 0)
						size2 = j+1;
					indexBuffer += 3;
					j++;
				}
				i++;
				j=0;
			}while(!is.eof());

			if(flag1){
				size1 = i-1;
				flag1 =0; 
			}

			myBoard.board.resize(size1);
			for(int j=0; j<size1; j++)
				myBoard.board[j].resize(size2);

			is.clear();
			is.seekg(0,ios::beg);

			i=0, j=0,flag1=1;
			do
			{	
				getline (is, buffer);	/// bu cpp ye uygun değil mi cidden?
				indexBuffer = 0;
				while(indexBuffer<buffer.size()){
					if(buffer.at(indexBuffer) == 'b'){
						myBoard.board[i][j] = -1;
						myBoard.space[0] = i;
						myBoard.space[1] = j;
					}
					else
						myBoard.board[i][j] = (buffer.at(indexBuffer)-48) * 10 + buffer.at(indexBuffer+1)-48;
										
					if(indexBuffer != 0)
						size2 = j+1;
					indexBuffer += 3;
					j++;
				}
				i++;
				j=0;
			}while(!is.eof());

			if(flag1){
				size1 = i-1;
				flag1 =0; 
			}
		
		}
		friend ostream& operator<<(ostream& os, const Board& myBoard){
			if(!myBoard.isFromFolder)
			{
				for(int i=0; i<myBoard.board.size(); i++)
				{
					for(int j=0; j< myBoard.board.size(); j++)
					{ 	
						if(myBoard.board[i][j] == myBoard.board.size()*myBoard.board.size() || myBoard.board[i][j] == -1)
							os<< "	";
						else
							os<< myBoard.board[i][j] << "	";
					}
					os<< endl;
				}
			}
			else
			{
				for(int i=0; i<myBoard.board.size(); i++)
				{
					for(int j=0; j<myBoard.board[0].size(); j++)
					{
						if(myBoard.board[i][j] == -1)
							os<<"bb	";
						if(myBoard.board[i][j] < 10 && myBoard.board[i][j] != -1)
							os<< 0 << myBoard.board[i][j] << "	";
						else if(myBoard.board[i][j] != -1)
							os<< myBoard.board[i][j] << "	";
					}
					os<< endl;
				}
			}
		}

	private:
		static int totalNumber;
		static char last_move;
		static int Number_Of_Boards;
		vector<vector <int> > board;

		//these datas for not represent they for just other functions like print
		bool isFromFolder;	
		vector<int> space;
	};
	vector<Board> gameBoard;

public:
	void menu(char **argv);
	void printReport();
	bool isBoardAlreadythere(Board newBoard);
	int moveForSolve(vector <vector<int>>  tempBoard, char m, vector <int> tempSpace);
	inline void print() const { gameBoard.back().print();} 
	inline void readFromFile(const string fileName){ (gameBoard.back().readFromFile(fileName)); }
	inline void writeToFile(const string fileName) const { (gameBoard.back().writeToFile(fileName)); }
	inline void setsize(const int sizefromUser) { (gameBoard.back().setSize(sizefromUser)); }
	bool shuffle(const int N);
	inline void reset(){ (gameBoard.back().reset()); }
	char moveRandom();
	inline int move(const char m) { (gameBoard.back().move(m));}
	inline int getSizeShuffle(){return gameBoard.back().getsizeshuffle();}
	inline int totalNumberG(){ return gameBoard.back().totalNumberGetter();}
	int solvePuzzle();

	friend istream& operator>>(istream& is, NPuzzle& puzzle){
		is >> puzzle.gameBoard.back();
    	return is;
	}
    friend ostream& operator<<(ostream& os, const NPuzzle& puzzle){ 
    	os << puzzle.gameBoard.back();
    	return os;
    }

};

int NPuzzle::Board::totalNumber = 0;
char NPuzzle::Board::last_move = 'S';
int NPuzzle::Board::Number_Of_Boards = 0;

NPuzzle::Board::Board(int getSize)	//constructure
{
	board.resize(getSize);
	for (int i = 0; i < getSize; ++i){
		for(int j=0; j< getSize; j++){
			board[i].push_back(-2);
		}
	}
	space.resize(3);
}

const int NPuzzle::Board::operator () (const int i, const int j)
{
	return (board[i][j]);
}
void NPuzzle::Board::operator = (const Board &B)
{
	board = B.board;

	totalNumber = B.totalNumber;
	last_move = B.last_move;
	isFromFolder = B.isFromFolder;
	space[0] = B.space[0];
	space[1] = B.space[1];
}

bool NPuzzle::Board::operator == (const Board& other)
{
	for (int i = 0; i < board.size(); ++i)
	{
		for (int j = 0; j < board[0].size(); ++j)
		{
			if(board[i][j] != other.board[i][j])
					return false;
		}
	}
	return true ;
}

int main(const int argc, char **argv)
{	
	NPuzzle game;
	srand(time(NULL));
	game.menu(argv);	
}

char NPuzzle::moveRandom()
{	
	int temp, moveIt=0;
	temp = rand()%4;

	if(temp == 0 ){
		moveIt = move('R');
	}
	if(temp == 1 ){
		moveIt = move('L');
	}
	if(temp == 2 ){
		moveIt = move('U');
	}
	if(temp == 3 ){
		moveIt = move('D');
	}

	return moveIt;
}
void NPuzzle::menu(char **argv)
{
	char getMove;
	int getSize;
	string buffer,fileName1,fileName2, fileName3;
	
	if(argv[1] == NULL)
	{
		do{
			cout << "Please enter the problem size" << endl ;
			cin >> getSize;
			}while(getSize<3 || getSize>9);
		Board b(getSize);
		gameBoard.push_back(b);
		setsize(getSize);

		cout << "Your initial random board is"<< endl;
		print();
	}
	else{
		Board b(9);
		gameBoard.push_back(b);

		ifstream folder;	/// << operator overload ile dosyadan okuma bu açıldığında dosyadan okunabiliyor
		string fileN = argv[1];
		folder.open(fileN.c_str());
		folder >> gameBoard.back();
		folder.close();

		print();
	}

	while(true)
	{
		if(gameBoard.back().isSolved())
		{
			cout << endl;
			cout << "Problem Solved!" << endl;
			cout <<"Total number of moves " << Board::numberOfMoves(3) << endl;
			exit(1);
		}
		cout << endl << "Your move:  ";
		cin >> getMove;

		if(getMove == 'Q')
			exit(1);
		if(getMove == 'T')
		{
			Board::numberOfMoves(1);
			printReport();
			print();
		}
		else if(getMove == 'R' || getMove == 'L' || getMove == 'D' || getMove == 'U'){  
			move(getMove); // choosen direction goes to move func
			cout <<	gameBoard.back();			// << operatörü kullanarak yazdırma
		}
		else if(getMove == 'S')
		{
			int num = getSizeShuffle();
			Board::numberOfMoves(1);
			reset();
			cout <<endl;
			while(!shuffle(num)){}
			print();
		}
		else if(getMove == 'O')
		{
			Board::numberOfMoves(1);
			cout << "file name: ";
			cin >> fileName2;
			readFromFile(fileName2);
			print();
		}
		else if(getMove == 'E')
		{
			Board::numberOfMoves(1);
			cout << "file name: ";
			cin >> fileName3;
			writeToFile(fileName3);
			print();
		}
		else if(getMove == 'V')
		{
			Board::numberOfMoves(0);
			Board::lastMove('S');
			solvePuzzle();
		}
	}
	
}

int NPuzzle::solvePuzzle()
{
	int i = 0;
	while(true){
		auto Rboard = gameBoard[i], Lboard = gameBoard[i], Uboard = gameBoard[i], Dboard = gameBoard[i];

		if(Rboard.move('R') == 1){
			if(isBoardAlreadythere(Rboard)){
				gameBoard.push_back(Rboard);
				gameBoard.back().print();
				cout << endl;
				if(gameBoard.back().isSolved()){
					gameBoard.back().print();
					cout << "Problem Solved!" << endl;
					exit(1);
				}
			}

		}
		if(Lboard.move('L') == 1){
			if(isBoardAlreadythere(Lboard)){
				gameBoard.push_back(Lboard);
				gameBoard.back().print();
				cout << endl;
				if (gameBoard.back().isSolved()){
					gameBoard.back().print();
					cout << "Problem Solved!" << endl;
					exit(1);
				}
			}
		}
		
		if(Uboard.move('U') == 1){
			if(isBoardAlreadythere(Uboard)){
				gameBoard.push_back(Uboard);
				gameBoard.back().print();
				cout << endl;
				if (gameBoard.back().isSolved()){
					gameBoard.back().print();
					cout << "Problem Solved!" << endl;
					exit(1);
				}
			}
		}

		if(Dboard.move('D') == 1){
			if(isBoardAlreadythere(Dboard)){
				gameBoard.push_back(Dboard);
				gameBoard.back().print();
				cout << endl;
				if (gameBoard.back().isSolved()){
					gameBoard.back().print();
					cout << "Problem Solved!" << endl;
					exit(1);
				}
			}
		}
		i++;
	}

}
bool NPuzzle::isBoardAlreadythere(Board newBoard)
{
	for(int i=0; i<gameBoard.size(); i++){
		if(gameBoard[i] == newBoard){
			return false;
		}
	}
	return true;
}

void NPuzzle::Board::reset()
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
		cout << endl;
	}
	board[board.size()-1][board[0].size()-1] = -1;
	print();
	space[0]=board.size()-1;
	space[1]=board[0].size()-1;
	//gameBoard.back().resize(0)
}
bool NPuzzle::shuffle(const int N)
{

	int randomMove;
	int moveCount=1;
	int isIllegal;
	while(moveCount <= N)
	{
		isIllegal = 1;
		randomMove = rand()%4;//random numbers for random moves

		if(randomMove == 0)	//0 is used for Right move
			isIllegal = move('R');
		
		else if(randomMove == 1)	//1 is used for Left move
			isIllegal = move('L');
		
		else if(randomMove == 2)	//2 is used for Up move
			isIllegal = move('U');
		
		else if(randomMove == 3)	//3 is used for Down move
			isIllegal = move('D');
		
		if(isIllegal != 0)	//if move is legal movecount is increasing
			moveCount++;
	}

	if(gameBoard.back().isSolved()) //if after the suffle board is the final solution
		return false;			//returns 0 and calling function again in main
	else
		return true;
}

int NPuzzle::Board::move(const char m) 
{
	int temp;
	/*swapping the empty cell with direction is choosen using i and j. for all directions*/
	/*if there is no room returns 0*/

	if(m == 'R'){
		if(space[1]+1 == board[0].size() || board[space[0]][space[1]+1] == 0)	
			return 0;
		else	
		{
			lastMove('R');
			numberOfMoves(1);
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
			lastMove('L');
			numberOfMoves(1);
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
			lastMove('U');
			numberOfMoves(1);
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
			lastMove('D');
			numberOfMoves(1);
			temp = board[space[0]+1][space[1]];
			board[space[0]+1][space[1]] = board[space[0]][space[1]];
			board[space[0]][space[1]] = temp;
			space[0]++;
		}
	}
	return 1;
}
void NPuzzle::printReport()
{
	cout <<  totalNumberG() << " moves have been done.";
	if(gameBoard.back().isSolved())
		cout << " solution is found"<<endl;
	else
		cout << " solution is not found"<<endl<<endl;
}

int NPuzzle::Board::numberOfMoves(int isV)
{
	if(isV == 1)
		totalNumber++;
	else if(isV == 3){}
	else 
		totalNumber = 0;

	return totalNumber;
}

char NPuzzle::Board::lastMove(char move)
{	
	last_move = move;
	return last_move;
}

int NPuzzle::Board::numberOfBoards()
{
	Number_Of_Boards++;
	return Number_Of_Boards;
}

void NPuzzle::Board::setSize(const int sizefromUser) 
{
	isFromFolder = 0;
	int control[83];
	auto i=0, j=0, a=0;
	int flag=1, location=0;
	int spaceControl=1;
	decltype(flag) temp;

	do{
		//controller array is a 1d array and keeping board
		a=0;
		i=0, j=0, a=0;
		flag=1;
		location=0;
		spaceControl=1;
		while(!a) 
		{
			flag=1;
			temp = rand()%(sizefromUser*sizefromUser) + 1;

			for(int k=0; k<location; ++k)	//controling the current number(temp) is here in board 
			{								//if it is flag being 0
				if(control [k] == temp)		
					flag = 0;
			}
			if(spaceControl && temp == sizefromUser*sizefromUser)
			{
				space[0] = i;	//space location is protect in space array
				space[1] = j;
				spaceControl = 0;
			}

			if(flag)	//if current number is not exist in board it adds in board
			{		
				control[location] = temp;
				board[i][j] = temp;
				if(i == sizefromUser-1 && j == sizefromUser-1) //last element of board
				{		
					a = 1;
				}
				else if(j == sizefromUser-1) // the condition of j is in the last cloumn
				{
					location++;
					j = 0;
					i++;
				}
				else	//other elements
				{
					location++;
					j++;
				}
			}
		}
		}while(!isSolvable(control) || isSolved());		
}
bool NPuzzle::Board::isSolvable(const int control[]) const
{
	int controlSolvable=0;

	for(int i=0; i<(board.size()); ++i) //counting inversion
	{								/*If we assume the tiles written out in a single row (1D Array) instead of being spread in N-rows (2D Array),
									 a pair of tiles (a, b) form an inversion if a appears before b but a > b. (geeksforgeeks)*/
		for(int j=i+1; j<(board.size()); ++j)
		{
			if(control[i] > control[j] && control[j] != (board.size()) && control[i] != (board.size()))
				controlSolvable++;
		}
	}
	int size = sqrt(board.size());
	if(size%2 == 1)	//checking solvability for odd sizes if inversion is even problem is solvable
	{	
		if(controlSolvable%2 == 0)
			return true;
		else
			return false;
	}
	
	if(size%2 == 0)	//checking solvability for even sizes
	{
		if(controlSolvable%2 == 0 && (size-space[0])%2 == 1)	//inversion number is even and pozition space from bottom is odd
			return true;											//problem is solvable
		else if(controlSolvable%2 == 1 && (size-space[0])%2 == 0)	//inversion number is odd and pozition space from bottom is even
			return true;												//problem is solvable
		else 	//any other options problem is unsolvable
			return false;	
	}
}
void NPuzzle::Board::print() const
{

	if(!isFromFolder)
	{
		for(int i=0; i<board.size(); i++)
		{
			for(int j=0; j< board.size(); j++)
			{ 	
				if(board[i][j] == board.size()*board.size() || board[i][j] == -1)
					cout<< "	";
				else
					cout<< board[i][j] << "	";
			}
			cout<< endl;
		}
	}
	else
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
}

bool NPuzzle::Board::isSolved() const
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

int NPuzzle::Board::readFromFile(const string fileName)
{
	ifstream folder;
	isFromFolder=1;
	auto i=0, j=0,flag1=1;
	auto indexBuffer=0;									
	string buffer;
	int temp[9][9];
	int size1,size2;
	folder.open(fileName.c_str());
	do
	{	
		getline (folder, buffer);	/// bu cpp ye uygun değil mi cidden?
		indexBuffer = 0;
		while(indexBuffer<buffer.size()){
			if(buffer.at(indexBuffer) == 'b'){
				temp[i][j] = -1;
				space[0] = i;
				space[1] = j;
			}
			else
				temp[i][j] = (buffer.at(indexBuffer)-48) * 10 + buffer.at(indexBuffer+1)-48;
								
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

	board.resize(size1);
	for(int j=0; j<size1; j++)
		board[j].resize(size2);

	folder.open(fileName.c_str());
	i=0, j=0,flag1=1;
	do
	{	
		getline (folder, buffer);	/// bu cpp ye uygun değil mi cidden?
		indexBuffer = 0;
		while(indexBuffer<buffer.size()){
			if(buffer.at(indexBuffer) == 'b'){
				board[i][j] = -1;
				space[0] = i;
				space[1] = j;
			}
			else
				board[i][j] = (buffer.at(indexBuffer)-48) * 10 + buffer.at(indexBuffer+1)-48;
								
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
}
void NPuzzle::Board::writeToFile(const string fileName) const
{
	ofstream folder1;
	folder1.open(fileName.c_str());
	/*printing current board in file for each condition like being bigger than 9*/
	if(isFromFolder){//if board is from file
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
	}
	else //if board is random initialized
	{	
		for(int i=0; i<board.size(); i++)
		{
			for(int j=0; j<board[0].size(); j++)
			{ 	
				if(i == board.size()-1 && j == board[0].size()-1){
					if(board[i][j] == -1 || board[i][j] == board.size()*board[0].size() )
						folder1 << "bb";
					else if(board[i][j]>9)
						folder1 << board[i][j];
					else
						folder1 << 0 <<board[i][j];
				}

				else
				{
					if(board[i][j] == board.size()*board[0].size() || board[i][j] == -1)
						folder1 << "bb	";
					else if(board[i][j] < 10)
						folder1 << 0 << board[i][j] << "	";
					else
						folder1 << board[i][j] << "	";
				}
			}
			folder1 << endl;
		}
	}
	folder1.close();
}