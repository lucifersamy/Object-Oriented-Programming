#include <iostream>
#include "abstractboard.h"
#include "boardvector.h"
#include "boardarray2d.h"
#include "boardarray1d.h"

using namespace Game;
void driver ();
bool isValid (AbstractBoard* array[],int size);
int AbstractBoard::Number_Of_Boards = 0;
char AbstractBoard::last_Move = 'S';
int AbstractBoard::number_Of_Moves = 0;

int main()
{
	driver();
}


void driver ()
{
	string fileName;
	int input = 0;
	BoardVector testVector,assignVector;
	BoardArray1D testArray1D, assignArray1D;
	BoardArray2D testArray2D, assignArray2D;


	//for global function
	AbstractBoard* game[20];
	BoardVector vector_object1;
	BoardArray1D board1d_object2;
	BoardArray2D board2D_object3;

	while(input != 4){
		cout << "0 for vector board"<<endl;
		cout << "1 for 1D board"<<endl; 
		cout << "2 for 2D board"<<endl;
		cout << "3 for global function"<<endl;
		cout << "4 for quit"<<endl<<"num is: ";
		cin >> input;
		cout << endl;
		cout << "file name:"<< endl;
		cin >> fileName;
		switch(input){
		    case 0 :
		    	cout << "-------TESTİNG CLASS VECTOR FUNCTİONS AND OPERATORS---------"<<endl;
				testVector.readFromFile(fileName);
				testVector.print();
				cout << endl;
				cout << "assign vector for assign operator"<<endl;
				assignVector = testVector;
				assignVector.print();
				cout << endl;
				if(testVector == assignVector)
					cout << "== operator is working" << endl<<endl;
				cout << "Right Move"<<endl;
				testVector.move('R');
				testVector.print();
				cout << endl;
				cout << "Down Move"<<endl;
				testVector.move('D');
				testVector.print();
				cout << endl;
				cout << "Left Move"<<endl;
				testVector.move('L');
				testVector.print();
				cout << endl <<endl;
				cout << "Up Move"<<endl;
				testVector.move('U');
				testVector.print();
				cout << endl;
				cout << "board is writing to outputVector.txt file" << endl;
				testVector.writeToFile("outputVector.txt");
				cout << "board is after that reset"<<endl;
				testVector.reset();
				cout << endl;
				testVector.print();
				cout << endl<< endl;
				if(testVector.isSolved())
					cout<<"SOLVED!"<<endl<<endl;
		        break;
		    case 1 :
		    	cout << "-------TESTİNG CLASS 1D ARRRAY FUNCTİONS AND OPERATORS---------"<<endl;
		        testArray1D.readFromFile(fileName);
				testArray1D.print();
				cout << endl;
				cout << "assign 1D for assign operator"<<endl;
				assignArray1D = testArray1D;
				assignArray1D.print();
				cout << endl;
				if(testArray1D == assignArray1D)
					cout << "== operator is working" << endl<<endl;
				cout << "Right Move"<<endl;
				testArray1D.move('R');
				testArray1D.print();
				cout << endl;
				cout << "Down Move"<<endl;
				testArray1D.move('D');
				testArray1D.print();
				cout << endl;
				cout << "Left Move"<<endl;
				testArray1D.move('L');
				testArray1D.print();
				cout << endl <<endl;
				cout << "Up Move"<<endl;
				testArray1D.move('U');
				testArray1D.print();
				cout << endl;
				cout << "board is writing to outputArray1D.txt file" << endl;
				testArray1D.writeToFile("outputArray1D.txt");
				cout << "board is after that reset"<<endl;
				testArray1D.reset();
				cout << endl;
				testArray1D.print();
				cout << endl<< endl;
				if(testArray1D.isSolved())
					cout<<"SOLVED!"<<endl<<endl;
		        break;
		    case 2 :
		    	cout << "-------TESTİNG CLASS 2D ARRRAY FUNCTİONS AND OPERATORS---------"<<endl;
		        testArray2D.readFromFile(fileName);
				testArray2D.print();
				cout << endl;
				cout << "assign 2D for assign operator"<<endl;
				assignArray2D = testArray2D;
				assignArray2D.print();
				cout << endl;
				if(testArray2D == assignArray2D)
					cout << "== operator is working" << endl<<endl;
				cout << "Right Move"<<endl;
				testArray2D.move('R');
				testArray2D.print();
				cout << endl;
				cout << "Down Move"<<endl;
				testArray2D.move('D');
				testArray2D.print();
				cout << endl;
				cout << "Left Move"<<endl;
				testArray2D.move('L');
				testArray2D.print();
				cout << endl <<endl;
				cout << "Up Move"<<endl;
				testArray2D.move('U');
				testArray2D.print();
				cout << endl;
				cout << "board is writing to outputArray2D.txt file" << endl;
				testArray2D.writeToFile("outputArray2D.txt");
				cout << "board is after that reset"<<endl;
				testArray2D.reset();
				cout << endl;
				testArray2D.print();
				cout << endl<< endl;
				if(testArray2D.isSolved())
					cout<<"SOLVED!"<<endl<<endl;
		        break;
		    case 3 :
		    	vector_object1.readFromFile(fileName);
				board1d_object2.readFromFile(fileName);
				board2D_object3.readFromFile(fileName);
				game[0] = &vector_object1;
				game[1] = &board1d_object2;
				game[2]= &board2D_object3;
				if(isValid(game,3))
					cout << "true"<<endl;
		        break;
		    case 4 :
		     	cout << "exit"<<endl;
		        break;
		    default :
		        cout << "Invalid grade" << endl;
  		 }
	}
	
	
	
}

bool isValid (AbstractBoard* game[],int size)
{
	/*global içinde buraya gönderdiklerimi fonksiyonlarımla kullanabiliyorum*/

	game[0]->print();
	cout << endl;
	game[0]->move('R');
	game[0]->print();
	cout << endl;

	game[1]->print();
	cout << endl;
	game[1]->move('R');
	game[1]->print();
	cout << endl;

	game[2]->print();
	game[2]->move('R');
	cout << endl;
	game[2]->print();
	cout << endl;
	return true;
}