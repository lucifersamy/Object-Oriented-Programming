#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <fstream>
#include <cstring>
using namespace std;

class NPuzzle
{
public:
	void printReport(const int moveCounter) const;
	void menu(char **argv);
	inline void print() const { gameBoard.print();} 
	inline void readFromFile(const string fileName){ (gameBoard.readFromFile(fileName)); }
	inline void writeToFile(const string fileName) const { (gameBoard.writeToFile(fileName)); }
	inline void setsize(const int sizefromUser) { (gameBoard.setSize(sizefromUser)); }
	inline bool isSolved() const {(gameBoard.isSolved());}
	inline int getSizeShuffle(){return gameBoard.getsizeshuffle();}
	inline int move(const char m) { (gameBoard.move(m));}
	inline bool shuffle(const int N){gameBoard.shuffle(N);}
	inline void reset(){ (gameBoard.reset()); }
	inline char moveRandom(){gameBoard.moveRandom();}
	inline int moveIntelligent(int whereBelongNumbers[][83]){ gameBoard.moveIntelligent(whereBelongNumbers);}
	inline int solvePuzzle(int whereBelongNumbers[][83]){gameBoard.solvePuzzle(whereBelongNumbers); }
private:
	class Board
	{
	public:
		void print() const;
		int readFromFile(const string fileName);
		char moveRandom();
		void writeToFile(const string fileName) const;
		bool shuffle(const int N);
		void reset();
		void setSize(const int sizefromUser);
		int move(const char m);
		bool isSolved() const;
		bool isSolvable(const int control[]) const;
		int solvePuzzle(int whereBelongNumbers[][83]);
		int moveIntelligent(int whereBelongNumbers[][83]);
		inline int getsizeshuffle(){return size1*size2;}
	private:
		int chooseMoveForIntellegent(int tempBoard[][10], char m, int tempSpace[]);
		int totalDistance(int tempBoard[][10], int whereBelongNumbers[][83] );
		void initializeTempBoard(int tempBoard[][10]);
		void initializeTempSpace(int tempSpace[]);
		int size;
		int size1;
		int size2;
		bool isFromFolder;
		int board[10][10];	
		int space[3];
	};
	Board gameBoard;
};

int main(const int argc, char **argv)
{	
	NPuzzle game;
	srand(time(NULL));
	game.menu(argv);	
}

void NPuzzle::menu(char **argv)
{
	char getMove;
	int getSize, doesMove=0,totalNumber=0;
	string buffer,fileName1,fileName2, fileName3;
	char mostIntelligent;
	int whereBelongNumbers[2][83];

	if(argv[1] == NULL)
	{
		do{
			cout << "Please enter the problem size" << endl ;
			cin >> getSize;
			}while(getSize<3 || getSize>9);
			
		setsize(getSize);
		cout << "Your initial random board is"<< endl;
		print();
	}
	else{
		fileName1 = argv[1];
		readFromFile(fileName1);
		print();
	}
	while(true)
	{
		doesMove = 0;
		if(isSolved())
		{
			cout << endl;
			cout << "Problem Solved!" << endl;
			cout <<"Total number of moves " << totalNumber << endl;
			exit(1);
		}
		cout << endl << "Your move:  ";
		cin >> getMove;

		if(getMove == 'Q')
			exit(1);
		if(getMove == 'T')
		{
			totalNumber++;
			printReport(totalNumber);
			print();
		}
		else if(getMove == 'R' || getMove == 'L' || getMove == 'D' || getMove == 'U'){  
			doesMove = move(getMove); // choosen direction goes to move func
			print();							
		}
		else if(getMove == 'O')
		{
			totalNumber++;
			cout << "file name: ";
			cin >> fileName2;
			readFromFile(fileName2);
			print();
		}
		else if(getMove == 'E')
		{
			totalNumber++;
			cout << "file name: ";
			cin >> fileName3;
			writeToFile(fileName3);
			print();
		}
		else if(getMove == 'S')
		{
			int num = getSizeShuffle();
			totalNumber++;
			reset();
			cout <<endl;
			while(!shuffle(num)){}
			print();

		}
		else if(getMove == 'I')
		{
			totalNumber++; 
			mostIntelligent = moveIntelligent(whereBelongNumbers);
			move(mostIntelligent);
			cout << "Intelligent move chooses " << mostIntelligent << endl;
			print();
		}
		else if(getMove == 'V')
		{
			totalNumber++;
			totalNumber += solvePuzzle(whereBelongNumbers);
		}
		if(doesMove == 1)	//if move is legal total number of move counter increases
			totalNumber++; 

	}
}
void NPuzzle::Board::setSize(const int sizefromUser) 
{
	size = sizefromUser;
	size1 = sizefromUser;
	size2 = sizefromUser;
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
			temp = rand()%(size*size) + 1;

			for(int k=0; k<location; ++k)	//controling the current number(temp) is here in board 
			{								//if it is flag being 0
				if(control [k] == temp)		
					flag = 0;
			}
			if(spaceControl && temp == size*size)
			{
				space[0] = i;	//space location is protect in space array
				space[1] = j;
				spaceControl = 0;
			}

			if(flag)	//if current number is not exist in board it adds in board
			{		
				control[location] = temp;
				board[i][j] = temp;
				if(i == size-1 && j == size-1) //last element of board
				{		
					a = 1;
				}
				else if(j == size-1) // the condition of j is in the last cloumn
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
void NPuzzle::Board::print() const
{
	if(!isFromFolder)
	{
		for(int i=0; i<size1; i++)
		{
			for(int j=0; j<size2; j++)
			{ 	
				if(board[i][j] == size1*size2 || board[i][j] == -1)
					cout<< "	";
				else
					cout<< board[i][j] << "	";
				
			}
			cout<< endl;
		}
	}
	else
	{
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
}
void NPuzzle::printReport(const int moveCounter) const
{
	cout << moveCounter << " moves have been done.";
	if(isSolved())
		cout << " solution is found"<<endl;
	else
		cout << " solution is not found"<<endl<<endl;
}

int NPuzzle::Board::solvePuzzle(int whereBelongNumbers[][83])
{
	char currentMove;
	decltype(currentMove) previousMove;
	auto isTurnBack = 0,totalNumber=0;

	previousMove = moveIntelligent(whereBelongNumbers);
	
	while(!isSolved())
	{
		isTurnBack=0;
		while(!isTurnBack && !isSolved())
		{
			isTurnBack = 1;
			currentMove = moveIntelligent(whereBelongNumbers);
			/*this conditions are for stuck control if there is no stuck it does intellegent moves in a loop*/
			if(previousMove == 'R' && currentMove != 'L')
				isTurnBack = 0;
			if(previousMove == 'L' && currentMove != 'R')
				isTurnBack = 0;
			if(previousMove == 'D' && currentMove != 'U' )
				isTurnBack = 0;
			if(previousMove == 'U' && currentMove != 'D')
				isTurnBack = 0;

			if(!isTurnBack)
			{	
				totalNumber++;
				move(currentMove);
				previousMove = currentMove;
				print();
				cout<<endl;
			}
		}
		int counter=0,temp;
		int moveIt=0;
		/*if there is stuck it does random moves in 3 times */
		while(counter<3 && !isSolved())
		{
			moveIt=0;
			moveIt = moveRandom();

			if(moveIt)
			{
				print(); 
				cout<<endl;
				counter++;
				totalNumber++;
			}
		}
	}
	return totalNumber;
}
char NPuzzle::Board::moveRandom()
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
int NPuzzle::Board::moveIntelligent(int whereBelongNumbers[][83]){	//geldiği tarafa gitmesini engelle
	int tempBoard[10][10],tempSpace[3];
	int comparisoner[4] = {0,0,0,0};
	int control=0;
	/*intellegent move decide the which move is the best move in current situation ( kind of A* algorithm)*/
	/*it calculate for each move */
	/*calculation of error point in totalDistance an they protect the comprisoner array. if moveFunction said it is 
	an illegal move (0) comparisoner[i] should a number that bigger that possible(7000 is enough) */

	initializeTempSpace(tempSpace);
	initializeTempBoard(tempBoard);
	if(chooseMoveForIntellegent(tempBoard, 'R', tempSpace)){
		comparisoner[0] = totalDistance(tempBoard,whereBelongNumbers);
	}
	else
		comparisoner[0] = 7000;
	
	initializeTempSpace(tempSpace);
	initializeTempBoard(tempBoard);
	if(chooseMoveForIntellegent(tempBoard,'L', tempSpace)){
		comparisoner[1] = totalDistance(tempBoard, whereBelongNumbers);
	}
	else
		comparisoner[1] = 7000;

	initializeTempSpace(tempSpace);
	initializeTempBoard(tempBoard);
	if(chooseMoveForIntellegent(tempBoard,'U', tempSpace)){
		comparisoner[2] = totalDistance(tempBoard,whereBelongNumbers);
	}
	else
		comparisoner[2] = 7000;

	initializeTempSpace(tempSpace);
	initializeTempBoard(tempBoard);
	if(chooseMoveForIntellegent(tempBoard, 'D', tempSpace)){
		comparisoner[3] = totalDistance(tempBoard, whereBelongNumbers);
	}
	else
		comparisoner[3] = 7000;
	/*finding min inversion*/
	int minDist;
	int i=1;
	minDist = comparisoner[0];
	while(i<4){
		if(minDist > comparisoner[i])
		{
			minDist = comparisoner[i];
			control = i;
		}
		i++;
	}
	/*best intelligent move is returns*/
	if(control == 0)
		return 'R';
	
	if(control == 1)
		return 'L';
	
	if(control == 2)
		return 'U';

	if(control == 3)
		return 'D';
}

int NPuzzle::Board::totalDistance(int tempBoard[][10], int whereBelongNumbers[][83] )
{
	int totaldistance=0;
	int finalLocationOfi,finalLocationOfj;
	/*this function is for help the intelligent move. calculates how far the each number is
	 from where they should be. and collects those distances*/
	if(!isFromFolder){
		int number=1;
		while(number <= size1*size2)
		{
			if(number%size1 == 0){	//relation of final location between numbers
				finalLocationOfj = size1-1;
				finalLocationOfi = number/size1 - 1;
			}
			else{	
				finalLocationOfj = (number%size1) - 1;
				finalLocationOfi = number/size1;
			}
			
			for(int i=0; i<size1; ++i)
			{
				for(int j=0; j<size1; ++j)
				{
					if(tempBoard[i][j] == number)
					{	//how far the numbers from where it should be
						totaldistance += abs(i - finalLocationOfi);
						totaldistance += abs(j - finalLocationOfj);
					}
				}
			}
			number++;
		}
	}

	else{
		auto k=0,t=0,s=0;
		int num = 1;
		while(k < size1*size2)
		{
			if(tempBoard[t][s] != 0 && ( ((t+1)*(s+1))<(size1*size2 - 1) ) )
			{
				whereBelongNumbers[0][num] = t;
				whereBelongNumbers[1][num] = s;
				num++;
			}
			s++;
			if (s==size2)
			{
				s=0;
				t++;
			}
			k++;
		}
		int c=1;
		int flag =1;
		num=1;
		int count=0;
		while(count < size1*size2)
		{
			for(int i=0; i<size1; ++i)
			{
				for(int j=0; j<size2; ++j)
				{
					if(tempBoard[i][j]==-1 && flag){
						totaldistance += abs(i - (size1-1)) + abs(j - (size2-1));
						flag=0;
					}
					else if(tempBoard[i][j] == num)
					{
						totaldistance += abs(i - whereBelongNumbers[0][num]);
						totaldistance += abs(j - whereBelongNumbers[1][num]);
						num++;
					}
				}
			}
			
			count++;
		}
	}
	return totaldistance;
}
void NPuzzle::Board::initializeTempBoard(int tempBoard[][10])
{
	for (int i = 0; i < size1; ++i)	
	{
		for (int j = 0; j < size2; ++j)
		{
			tempBoard[i][j] = board[i][j];
		}
	}
}
void NPuzzle::Board::initializeTempSpace(int tempSpace[])
{
	for (int i = 0; i < 2; ++i)
		tempSpace[i] = space[i];
}
int NPuzzle::Board::chooseMoveForIntellegent(int tempBoard[][10], char m, int tempSpace[])
{
	int temp;
	/*swapping the empty cell with direction is choosen using i and j. for all directions*/
	/*if there is no room returns 0*/

	if(m == 'R'){	
		if(tempSpace[1]+1 == size2 || tempBoard[tempSpace[0]][tempSpace[1]+1] == 0)	
			return 0;
		else	
		{
			temp = tempBoard[tempSpace[0]][tempSpace[1]+1];
			tempBoard[tempSpace[0]][tempSpace[1]+1] = tempBoard[tempSpace[0]][tempSpace[1]];
			tempBoard[tempSpace[0]][tempSpace[1]] = temp;
			tempSpace[1]++;	
		}		
	}
	else if(m == 'L'){
		if(tempSpace[1]-1 == -1 || tempBoard[tempSpace[0]][tempSpace[1]-1] == 0)
			return 0;
		else
		{
			temp = tempBoard[tempSpace[0]][tempSpace[1]-1];
			tempBoard[tempSpace[0]][tempSpace[1]-1] = tempBoard[tempSpace[0]][tempSpace[1]];
			tempBoard[tempSpace[0]][tempSpace[1]] = temp;
			tempSpace[1]--;
		}
	}
	else if(m == 'U'){
		if(tempSpace[0]-1 == -1 || tempBoard[tempSpace[0]-1][tempSpace[1]] == 0)
			return 0;
		else{
			temp = tempBoard[tempSpace[0]-1][space[1]];
			tempBoard[tempSpace[0]-1][tempSpace[1]] = tempBoard[tempSpace[0]][tempSpace[1]];
			tempBoard[tempSpace[0]][tempSpace[1]] = temp;
			tempSpace[0]--;
		}
	}
	else if(m == 'D'){
		if(tempSpace[0]+1 == size1 || tempBoard[tempSpace[0]+1][tempSpace[1]] == 0)
			return 0;
		else
		{
			temp = tempBoard[tempSpace[0]+1][tempSpace[1]];
			tempBoard[tempSpace[0]+1][tempSpace[1]] = tempBoard[tempSpace[0]][tempSpace[1]];
			tempBoard[tempSpace[0]][tempSpace[1]] = temp;
			tempSpace[0]++;
		}
	}
	return 1;
}
bool NPuzzle::Board::shuffle(const int N)
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

	if(isSolved()) //if after the suffle board is the final solution
		return false;			//returns 0 and calling function again in main
	else
		return true;
}

void NPuzzle::Board::reset()
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
int NPuzzle::Board::move(const char m) 
{
	int temp;
	/*swapping the empty cell with direction is choosen using i and j. for all directions*/
	/*if there is no room returns 0*/

	if(m == 'R'){	
		if(space[1]+1 == size2 || board[space[0]][space[1]+1] == 0)	
			return 0;
		else	
		{
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
			temp = board[space[0]+1][space[1]];
			board[space[0]+1][space[1]] = board[space[0]][space[1]];
			board[space[0]][space[1]] = temp;
			space[0]++;
		}
	}
	return 1;
}
bool NPuzzle::Board::isSolved() const
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

bool NPuzzle::Board::isSolvable(const int control[]) const
{
	int controlSolvable=0;

	for(int i=0; i<(size*size); ++i) //counting inversion
	{								/*If we assume the tiles written out in a single row (1D Array) instead of being spread in N-rows (2D Array),
									 a pair of tiles (a, b) form an inversion if a appears before b but a > b. (geeksforgeeks)*/
		for(int j=i+1; j<(size*size); ++j)
		{
			if(control[i] > control[j] && control[j] != size*size && control[i] != size*size)
				controlSolvable++;
		}
	}
	
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
int NPuzzle::Board::readFromFile(const string fileName)
{
	ifstream folder;
	isFromFolder=1;

	auto i=0, j=0,flag1=1;
	auto indexBuffer=0;									
	string buffer;

	folder.open(fileName.c_str());
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
	else //if board is random initialized
	{	
		for(int i=0; i<size1; i++)
		{
			for(int j=0; j<size2; j++)
			{ 	
				if(i == size1-1 && j == size2-1){
					if(board[i][j] == -1 || board[i][j] == size1*size2 )
						folder1 << "bb";
					else if(board[i][j]>9)
						folder1 << board[i][j];
					else
						folder1 << 0 <<board[i][j];
				}

				else
				{
					if(board[i][j] == size1*size2 || board[i][j] == -1)
						folder1 << "bb	";
					else if(board[i][j] < 10)
						folder1<< 0 << board[i][j] << "	";
					else
						folder1 << board[i][j] << "	";
				}
			}
			folder1 << endl;
		}
	}
	folder1.close();
}

