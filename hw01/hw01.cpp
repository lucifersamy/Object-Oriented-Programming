#include <iostream>
#include <cstdlib> 
#include <ctime> 
using namespace std;


void initializeBoard(int board[][10], int control[82], int space[3], int size);
/*this is the function initilizing a random board*/
void boardPrinter(int board[][10], int size);
/* this is the function printing the board*/
int isFinish(int board[][10],int size);
/*this is the function checking is the board final position and if it is it returns 1, else 0*/ 
int isSolvable(int control[],int space[], int size);
/*this is the function controlling is the random board solvable or not. if it is it returns 1, else 0 */
int moveFunction(int board[][10],int size, char move, int space[3]);
/*this is the function that is the make move the empty cell to direction that takes from user. if move is legal returns 1 else 0*/
int shuffleFunction(int board[][10],int control[],int space[], int size);
/*this is the function that takes the board to the final solution, and makes size*size random moves to shuffle the board*/
int totalDistance(int board[][10], int size);
/*this is the function that total distance that mean total of distance of each number from current location between where it belongs actualy. 
and it returns the total distance(cost)*/
char intelligentMove(int board[][10], int space[], int size, char move);
/*this is the function that what is the most intellegent move possible and returns it*/
void initializeTempBoard(int board[][10], int size, int tempBoard[][10]);
/*this is the function copy a 2d array*/
void initializeSpace(int space[3], int size, int tempSpace[3]);
/*this is the function copy an array*/

int main(){
	int size;
	int board[10][10],control[82], space[3];
	srand(time(NULL));

	do{
		cout << "Please enter the problem size" << endl ;
		cin >> size;
	}while(size<3 || size>9);
	
	cout << "Your initial random board is"<< endl;
	do{
		initializeBoard(board,control,space,size);
		}while(!isSolvable(control,space,size) || isFinish(board,size));

	boardPrinter(board,size); 

	char move;
	int totalNumber=0;
	int doesMove=0;
	char mostIntelligent;
	while(true){
		doesMove = 0;
		if(isFinish(board,size))
		{
			cout << endl;
			cout << "Problem Solved!"<<endl 
			<<"Total number of moves " << totalNumber << endl;
			break;
		}

		cout << endl << "Your move:  ";
		cin >> move;
		if(move == 'Q')
			break;

		else if(move == 'I')
		{
			totalNumber++; 
			mostIntelligent = intelligentMove(board,space,size,move);
			moveFunction(board,size,mostIntelligent,space);
			cout << "Intelligent move chooses " << mostIntelligent << endl;
			boardPrinter(board,size);
		}
		else if(move == 'S')
		{
			while(!shuffleFunction(board,control, space,size)){}
			boardPrinter(board,size);
			totalNumber++;
		}
		if(move == 'R' || move == 'L' || move == 'D' || move == 'U'){  
			doesMove = moveFunction(board, size, move, space); // choosen direction goes to move func
			boardPrinter(board,size);							// if move is illegal program want a new move
		}
		if(doesMove == 1)	//if move is legal total number of move counter increases
			totalNumber++; 
		
	}

}
int moveFunction(int board[][10],int size, char move, int space[3]){
	int temp;
	/*swapping the empty cell with direction is choosen using i and j. for all directions*/
	/*if there is no room returns 0*/
	if(move == 'R'){	
		if(space[1]+1 == size)	
			return 0;
		else	
		{	//
			temp = board[space[0]][space[1]+1];
			board[space[0]][space[1]+1] = board[space[0]][space[1]];
			board[space[0]][space[1]] = temp;
			space[1]++;	
		}		
	}
	else if(move == 'L'){
		if(space[1]-1 == -1)
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
		if(space[0]-1 == -1)
			return 0;
		else{
			temp = board[space[0]-1][space[1]];
			board[space[0]-1][space[1]] = board[space[0]][space[1]];
			board[space[0]][space[1]] = temp;
			space[0]--;
		}
	}
	else if(move == 'D'){
		if(space[0]+1 == size)
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

void initializeBoard(int board[][10],int control[82], int space[3], int size){
	int i=0, j=0, a=0;
	int flag=1, temp, location=0;
	int spaceControl=1;

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

void boardPrinter(int board[][10],int size){
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			if(board[i][j] == size*size )
				cout<< "	";
			else
				cout<< board[i][j] << "	";
		}
		cout<< endl;
	}
}

int isFinish(int board[][10], int size){	//checking the puzzle is solved
	int a=1;
	//is board final solution
	for(int i=0; i<size; ++i)
	{
		for(int j=0; j<size; ++j)
		{
			if(board[i][j] != a)
				return 0;
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

int shuffleFunction(int board[][10],int control[],int space[], int size){
	int a=1;
	int randomMove;
	//takes the board to the final solution in here
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			board[i][j] = a;
			if(board[i][j] != size * size)
				cout << board[i][j] << "	";
			a++;
		}
		cout << endl;
	}
	space[0]=size-1;
	space[1]=size-1;
	cout << endl;

	int moveCount=1;
	int isIllegal;
	while(moveCount <= size*size)
	{
		isIllegal = 1;
		randomMove = rand()%4;//random numbers for random moves

		if(randomMove == 0)	//0 is used for Right move
			isIllegal = moveFunction(board,size, 'R', space);
		
		else if(randomMove == 1)	//1 is used for Left move
			isIllegal = moveFunction(board,size, 'L', space);
		
		else if(randomMove == 2)	//2 is used for Up move
			isIllegal = moveFunction(board,size, 'U', space);
		
		else if(randomMove == 3)	//3 is used for Down move
			isIllegal = moveFunction(board,size, 'D', space);
		
		if(isIllegal != 0)	//if move is legal movecount is increasing
			moveCount++;
	}

	if(isFinish(board,size)) //if after the suffle board is the final solution
		return 0;			//returns 0 and calling function again in main
	else
		return 1;
}

char intelligentMove(int board[][10], int space[], int size, char move){	//geldiği tarafa gitmesini engelle
	int tempBoard[10][10],tempSpace[3];
	int comparisoner[4] = {0,0,0,0};
	int control=0;
	/*intellegent move decide the which move is the best move in current situation ( kind of A* algorithm)*/
	/*it calculate for each move */
	/*calculation of error point in totalDistance an they protect the comprisoner array. if moveFunction said it is 
	an illegal move (0) comparisoner[i] should a number that bigger that possible(7000 is enough) */
	initializeSpace(space, 3, tempSpace);
	initializeTempBoard(board, size, tempBoard);
	if(moveFunction(tempBoard, size, 'R', tempSpace)){
		comparisoner[0] = totalDistance(tempBoard, size);
	}
	else
		comparisoner[0] = 7000;
	
	initializeSpace(space, 3, tempSpace);
	initializeTempBoard(board, size, tempBoard);
	if(moveFunction(tempBoard, size, 'L', tempSpace)){
		comparisoner[1] = totalDistance(tempBoard, size);
	}
	else
		comparisoner[1] = 7000;

	initializeSpace(space, 3, tempSpace);
	initializeTempBoard(board, size, tempBoard);
	if(moveFunction(tempBoard, size, 'U', tempSpace)){
		comparisoner[2] = totalDistance(tempBoard, size);
	}
	else
		comparisoner[2] = 7000;

	initializeSpace(space, 3, tempSpace);
	initializeTempBoard(board, size, tempBoard);
	if(moveFunction(tempBoard, size, 'D', tempSpace)){
		comparisoner[3] = totalDistance(tempBoard, size);
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

int totalDistance(int board[][10], int size){
	int number=1;
	int totaldistance=0;
	int finalLocationOfi,finalLocationOfj;
	/*this function is for help the intelligent move. calculates how far the each number is
	 from where they should be. and collects those distances*/
	while(number <= size*size)
	{
		if(number%size == 0){	//relation of final location between numbers
			finalLocationOfj = size-1;
			finalLocationOfi = number/size - 1;
		}
		else{	
			finalLocationOfj = (number%size) - 1;
			finalLocationOfi = number/size;
		}
		
		for(int i=0; i<size; ++i)
		{
			for(int j=0; j<size; ++j)
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
	return totaldistance;
} /*array coppier functions*/
void initializeTempBoard(int board[][10], int size, int tempBoard[][10]){
	for (int i = 0; i < size; ++i)	
	{
		for (int j = 0; j < size; ++j)
		{
			tempBoard[i][j] = board[i][j];
		}
	}
}
void initializeSpace(int space[3], int size, int tempSpace[3]){
	for (int i = 0; i < 2; ++i)
	{
		tempSpace[i] = space[i];
	}
}
