//constructureda size1 size2 olmayacak mı benim ilk başta size1 sizem yok ki 

#ifndef BOARDARRAY_2D
#define BOARDARRAY_2D
#include "abstractboard.h"

namespace Game
{
	class BoardArray2D : public AbstractBoard
	{
	public:
		BoardArray2D();
		BoardArray2D(const BoardArray2D& boardArrayObject);	//copy constructure
		virtual void print() const;
		virtual void readFromFile(const string fileName);
		virtual void writeToFile(const string fileName) const;
		virtual void reset();
		virtual void setSize(int size1,int size2);
		virtual int move(char m);
		virtual bool isSolved() const;
		virtual int operator () (int i, int j) const;
		virtual bool operator == (const BoardArray2D& first) ;
		BoardArray2D& operator = (const BoardArray2D& rightSide);
		virtual ~BoardArray2D();	//destructure
		virtual int get_space_i() { return space[0];}
		virtual int get_space_j() { return space[1];}
	private:
		int size1;
		int size2;
		int **board;	
		int *space;
	};
}

#endif 