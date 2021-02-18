#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include <string>
#include <iostream>
#include <fstream>
using std::string;
using namespace std;

namespace Game
{
	class AbstractBoard
	{
	public:
		AbstractBoard(){}
		virtual void print() const  = 0;
		virtual void readFromFile(const string fileName) = 0;
		virtual void writeToFile(const string fileName) const = 0;
		virtual void reset() = 0;
		virtual void setSize(int size1,int size2) = 0;
		virtual int move(char m) = 0;
		virtual bool isSolved() const = 0;
		virtual int operator () (int i, int j) const;
		virtual bool operator == (const  AbstractBoard& first); 
		static int NumberOfBoards() { return Number_Of_Boards; }
		static char lastMove() { return last_Move; }	
		static int numberOfMoves() { return number_Of_Moves; } 
		virtual ~AbstractBoard(){}
		virtual int get_space_i() {}
		virtual int get_space_j() {}
	protected:
		static int Number_Of_Boards;
		static char last_Move;
		static int number_Of_Moves; 
	};
}

#endif