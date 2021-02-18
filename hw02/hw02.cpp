#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <fstream>
#include <cstring>
using namespace std;

const int ARRAYSIZE = 83;
const int BOARDSIZE = 10;

void initializeBoard(int board[][BOARDSIZE], int control[], int space[], int size);					
/*this is the function initilizing a random board*/
inline void boardPrinter(int board[][BOARDSIZE],int size1, int size2, int isFromFolder);   							
/* this is the function printing the board*/
inline int isFinish(int board[][BOARDSIZE],int size1, int size2, int isFromFolder);																																		
/*this is the function checking is the board final position and if it is it returns 1, else 0*/ 
int isSolvable(int control[],int space[], int size);													
/*this is the function controlling is the random board solvable or not. if it is it returns 1, else 0 */
int moveFunction(int board[][BOARDSIZE],int size1, int size2, char move, int space[]);						//güncel
/*this is the function that is the make move the empty cell to direction that takes from user. if move is legal returns 1 else 0*/
int shuffleFunction(int board[][BOARDSIZE],int control[],int space[], int size1, int size2,int isFromFolder);					
/*this is the function that takes the board to the final solution, and makes size*size random moves to shuffle the board*/
int totalDistance(int board[][BOARDSIZE], int size1, int size2, int isFromFolder, int whereBelongNumbers[][ARRAYSIZE]);
/*this is the function that total distance that mean total of distance of each number from current location between where it belongs actualy. 
and it returns the total distance(cost)*/
char intelligentMove(int board[][BOARDSIZE], int space[], int size1, int size2, int isFromFolder, int whereBelongNumbers[][ARRAYSIZE]);
/*this is the function that what is the most intellegent move possible and returns it*/
inline void initializeTempBoard(int board[][BOARDSIZE], int size1, int size2, int tempBoard[][BOARDSIZE]);	
/*this is the function copy a 2d array*/
inline void initializeSpace(int space[], int tempSpace[]);
/*this is the function copy an array*/
inline void loadFile(int board[][BOARDSIZE], int size1, int size2, int isFromFolder);
/*this is the function that load the current board in file	*/
int puzzleSolver(int board[][BOARDSIZE], int space[], int size1, int size2, int isFromFolder, int whereBelongNumbers[][ARRAYSIZE]);
/*this is the function that solving puzzle intellegent moves and if there is stuck it does some random moves and again intellegent moves when user take the V*/

int main(const int argc, const char **argv){
	int size;
	decltype(size) size1, size2;
	auto isFromFolder=0,flag = 1, doesMove=0, totalNumber=0;
	int board[BOARDSIZE][BOARDSIZE],control[ARRAYSIZE], space[3],whereBelongNumbers[2][ARRAYSIZE];
	string buffer,fileName2,fileName3;
	char move;
	char mostIntelligent;
	ifstream folder2;
	ifstream folder3;
	srand(time(NULL));

	if(argv[1] == NULL){
		do{
			cout << "Please enter the problem size" << endl ;
			cin >> size;
			}while(size<3 || size>9);
		size1 = size;
		size2 = size;
		cout << "Your initial random board is"<< endl;
		do{
			initializeBoard(board,control,space,size);
			}while(!isSolvable(control,space,size) || isFinish(board,size1,size2,isFromFolder));

		boardPrinter(board,size1,size2,isFromFolder);
	} 
	else
	{	
		isFromFolder=1;	//if new board is will be board isFromFolder turning 1
		auto i=0, j=0,flag1=1;
		auto indexBuffer=0;									
		string buffer1;
		fileName3 = argv[1];
		folder3.open(fileName3.c_str());
		do
		{
			getline (folder3, buffer1);	/// bu cpp ye uygun değil mi cidden?
			indexBuffer = 0;
			while(indexBuffer<buffer1.size()){
				if(buffer1.at(indexBuffer) == 'b'){
					board[i][j] = -1;
					space[0] = i;
					space[1] = j;
				}
				else
					board[i][j] = (buffer1.at(indexBuffer)-48) * 10 + buffer1.at(indexBuffer+1)-48;
									
				if(indexBuffer != 0)
					size2 = j+1;
				indexBuffer += 3;
				j++;
			}
			i++;
			j=0;
		}while(!folder3.eof());
		if(flag1){
			size1 = i-1;
			flag1 =0; 
		}
		folder3.close();

		boardPrinter(board,size1,size2,isFromFolder); 
	}

	while(true){
		doesMove = 0;
		if(isFinish(board,size1,size2,isFromFolder) ) ///T den dolayı güncelleme gelcek mi
		{
			cout << endl;
			cout << "Problem Solved!" << endl
			<<"Total number of moves " << totalNumber << endl;
			break;
		}

		cout << endl << "Your move:  ";
		cin >> move;

		if(move == 'Q')
			break;
		if(move == 'T')
		{
			totalNumber++;
			cout << totalNumber << " moves have been done.";
			if(isFinish(board,size1,size2,isFromFolder))
				cout << " solution is found"<<endl;
			else
				cout << " solution is not found";
		}
		if(move == 'E')
		{	//waiting for  file name
			totalNumber++;
			loadFile(board,size1, size2,isFromFolder);
			boardPrinter(board,size1,size2,isFromFolder); 

		}
		if(move == 'Y')
		{
			totalNumber++;
			isFromFolder=1;	//if new board is will be board isFromFolder turning 1
			int i=0, j=0;
			int indexBuffer=0;									
			
			do{
				cout << "file name: ";	////file name txt li mi vercek????????????????????????????
				cin >> fileName2;
			}while(folder2.fail());

			folder2.open(fileName2.c_str());
			do
			{
				getline (folder2, buffer);	/// bu cpp ye uygun değil mi cidden?
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
			}while(!folder2.eof());
			if(flag){
				size1 = i-1;
				flag =0; 
			}

			boardPrinter(board,size1,size2,isFromFolder); 
		}

		else if(move == 'I')
		{
			totalNumber++; 
			mostIntelligent = intelligentMove(board,space,size1,size2,isFromFolder,whereBelongNumbers);
			moveFunction(board,size1,size2,mostIntelligent,space);
			cout << "Intelligent move chooses " << mostIntelligent << endl;
			boardPrinter(board,size1,size2,isFromFolder);
		}
		else if(move == 'S')
		{
			while(!shuffleFunction(board,control, space,size1,size2,isFromFolder)){}
			boardPrinter(board,size1,size2,isFromFolder);
			totalNumber++;
		}
		else if(move == 'V')
		{	
			totalNumber++;
			totalNumber += puzzleSolver(board,space,size1,size2, isFromFolder, whereBelongNumbers);
			
		}
		if(move == 'R' || move == 'L' || move == 'D' || move == 'U'){  
			doesMove = moveFunction(board, size1,size2, move, space); // choosen direction goes to move func
			boardPrinter(board,size1,size2,isFromFolder);							// if move is illegal program want a new move
		}
		if(doesMove == 1)	//if move is legal total number of move counter increases
			totalNumber++; //bura da çek edilecek
		
	}
	
	folder2.close();
}
int moveFunction(int board[][BOARDSIZE],int size1, int size2, char move, int space[3]){
	int temp;
	/*swapping the empty cell with direction is choosen using i and j. for all directions*/
	/*if there is no room returns 0*/

	if(move == 'R'){	
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
	else if(move == 'L'){
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
	else if(move == 'U'){
		if(space[0]-1 == -1 || board[space[0]-1][space[1]] == 0)
			return 0;
		else{
			temp = board[space[0]-1][space[1]];
			board[space[0]-1][space[1]] = board[space[0]][space[1]];
			board[space[0]][space[1]] = temp;
			space[0]--;
		}
	}
	else if(move == 'D'){
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

void initializeBoard(int board[][BOARDSIZE],int control[], int space[3], int size){
	auto i=0, j=0, a=0;
	int flag=1, location=0;
	int spaceControl=1;
	decltype(flag) temp;
	//controller array is a 1d array and keeping board
	while(!a){
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
}

inline void boardPrinter(int board[][BOARDSIZE],int size1, int size2,int isFromFolder){
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

inline int isFinish(int board[][BOARDSIZE], int size1, int size2, int isFromFolder){	//checking the puzzle is solved
	int a=1;
	//is board final solution
	for(int i=0; i<size1; ++i)
	{
		for(int j=0; j<size2; ++j)
		{
			if((i == size1-1 && j == size2-1 )){}
			else if(board[i][j] == 0){}
			else if(board[i][j]!= a)
				return 0;
			else
				a++;		
		}
	}
	return 1;
}


int isSolvable(int control[],int space[], int size){
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
	
	if(size%2 == 1){	//checking solvability for odd sizes if inversion is even problem is solvable
		if(controlSolvable%2 == 0)
			return 1;
		else
			return 0;
	}
	
	if(size%2 == 0){	//checking solvability for even sizes
		if(controlSolvable%2 == 0 && (size-space[0])%2 == 1)	//inversion number is even and pozition space from bottom is odd
			return 1;											//problem is solvable
		else if(controlSolvable%2 == 1 && (size-space[0])%2 == 0)	//inversion number is odd and pozition space from bottom is even
			return 1;												//problem is solvable
		else 	//any other options problem is unsolvable
			return 0;	
	}
}

int shuffleFunction(int board[][BOARDSIZE],int control[],int space[], int size1, int size2,int isFromFolder){
	auto a=1;
	int randomMove;
	//takes the board to the final solution in here
	
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
	boardPrinter(board,size1,size2,isFromFolder);
	space[0]=size1-1;
	space[1]=size2-1;
	cout << endl;

	int moveCount=1;
	int isIllegal;
	while(moveCount <= size1*size2)
	{
		isIllegal = 1;
		randomMove = rand()%4;//random numbers for random moves

		if(randomMove == 0)	//0 is used for Right move
			isIllegal = moveFunction(board,size1, size2, 'R', space);
		
		else if(randomMove == 1)	//1 is used for Left move
			isIllegal = moveFunction(board,size1,size2, 'L', space);
		
		else if(randomMove == 2)	//2 is used for Up move
			isIllegal = moveFunction(board,size1,size2,'U', space);
		
		else if(randomMove == 3)	//3 is used for Down move
			isIllegal = moveFunction(board,size1, size2, 'D', space);
		
		if(isIllegal != 0)	//if move is legal movecount is increasing
			moveCount++;
	}

	if(isFinish(board,size1,size2,isFromFolder)) //if after the suffle board is the final solution
		return 0;			//returns 0 and calling function again in main
	else
		return 1;
}

char intelligentMove(int board[][BOARDSIZE], int space[], int size1, int size2, int isFromFolder, int whereBelongNumbers[][ARRAYSIZE]){	//geldiği tarafa gitmesini engelle
	int tempBoard[10][10],tempSpace[3];
	int comparisoner[4] = {0,0,0,0};
	int control=0;
	/*intellegent move decide the which move is the best move in current situation ( kind of A* algorithm)*/
	/*it calculate for each move */
	/*calculation of error point in totalDistance an they protect the comprisoner array. if moveFunction said it is 
	an illegal move (0) comparisoner[i] should a number that bigger that possible(7000 is enough) */

	initializeSpace(space, tempSpace);
	initializeTempBoard(board, size1, size2,tempBoard);
	if(moveFunction(tempBoard, size1,size2, 'R', tempSpace)){
		comparisoner[0] = totalDistance(tempBoard, size1,size2, isFromFolder,whereBelongNumbers);
	}
	else
		comparisoner[0] = 7000;
	
	initializeSpace(space, tempSpace);
	initializeTempBoard(board, size1, size2, tempBoard);
	if(moveFunction(tempBoard, size1, size2, 'L', tempSpace)){
		comparisoner[1] = totalDistance(tempBoard, size1,size2, isFromFolder,whereBelongNumbers);
	}
	else
		comparisoner[1] = 7000;

	initializeSpace(space, tempSpace);
	initializeTempBoard(board, size1, size2, tempBoard);
	if(moveFunction(tempBoard, size1,size2, 'U', tempSpace)){
		comparisoner[2] = totalDistance(tempBoard, size1,size2, isFromFolder,whereBelongNumbers);
	}
	else
		comparisoner[2] = 7000;

	initializeSpace(space, tempSpace);
	initializeTempBoard(board, size1, size2, tempBoard);
	if(moveFunction(tempBoard, size1,size2,'D', tempSpace)){
		comparisoner[3] = totalDistance(tempBoard, size1,size2, isFromFolder, whereBelongNumbers);
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

int totalDistance(int board[][BOARDSIZE], int size1, int size2, int isFromFolder, int whereBelongNumbers[][ARRAYSIZE]){
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
					if(board[i][j] == number)
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
			if(board[t][s] != 0 && ( ((t+1)*(s+1))<(size1*size2 - 1) ) )
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
					if(board[i][j]==-1 && flag){
						totaldistance += abs(i - (size1-1)) + abs(j - (size2-1));
						flag=0;
					}
					else if(board[i][j] == num)
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
} /*array coppier functions*/
inline void initializeTempBoard(int board[][BOARDSIZE], int size1, int size2, int tempBoard[][10]){
	for (int i = 0; i < size1; ++i)	
	{
		for (int j = 0; j < size2; ++j)
		{
			tempBoard[i][j] = board[i][j];
		}
	}
}
inline void initializeSpace(int space[], int tempSpace[]){
	for (int i = 0; i < 2; ++i)
	{
		tempSpace[i] = space[i];
	}
}
int puzzleSolver(int board[][BOARDSIZE], int space[], int size1, int size2, int isFromFolder, int whereBelongNumbers[][ARRAYSIZE]){
	char currentMove;
	decltype(currentMove) previousMove;
	auto isTurnBack = 0,totalNumber=0;
	previousMove = intelligentMove(board,space,size1,size2,isFromFolder,whereBelongNumbers);
	moveFunction(board,size1,size2,previousMove,space);
	
	while(!isFinish(board,size1,size2,isFromFolder))
	{
		isTurnBack=0;
		while(!isTurnBack && !isFinish(board,size1,size2,isFromFolder))
		{
			isTurnBack = 1;
			currentMove = intelligentMove(board, space, size1, size2,isFromFolder, whereBelongNumbers);
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
				moveFunction(board,size1,size2,currentMove,space);
				previousMove = currentMove;
				boardPrinter(board,size1,size2,isFromFolder);
				cout<<endl;
			}
		}
		int counter=0,temp;
		int moveIt=0;
		/*if there is stuck it does random moves in 3 times */
		while(counter<3 && !isFinish(board,size1,size2,isFromFolder))
		{
			moveIt=0;
			temp = rand()%4 + 1;
			if(temp == 1 ){
				moveIt = moveFunction(board,size1,size2,'R',space);
			}
			if(temp == 2 ){
				moveIt = moveFunction(board,size1,size2,'L',space);

			}
			if(temp == 3 )
				moveIt = moveFunction(board,size1,size2,'U',space);

			if(temp == 4 )
				moveIt = moveFunction(board,size1,size2,'D',space);

			if(moveIt)
			{
				boardPrinter(board,size1,size2,isFromFolder); 
				cout<<endl;
				counter++;
				totalNumber++;
			}
		}
	}
	return totalNumber;
}

inline void loadFile(int board[][BOARDSIZE], int size1, int size2, int isFromFolder){
	ofstream folder1;
	string fileName1;
	cout << "file name: ";
	cin >> fileName1;
	folder1.open(fileName1.c_str());
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