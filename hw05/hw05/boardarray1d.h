#ifndef BOARDARRAY_1D
#define BOARDARRAY_1D
#include "abstractboard.h"
namespace Game
{
	class BoardArray1D : public AbstractBoard
	{
	public:
		BoardArray1D();
		BoardArray1D(const BoardArray1D& boardArrayObject);	//copy constructure
		virtual void print() const;
		virtual void readFromFile(const string fileName);
		virtual void writeToFile(const string fileName) const;
		virtual void reset();
		virtual void setSize(int size1,int size2);
		virtual int move(char m);
		virtual bool isSolved() const;
		virtual bool operator == (const BoardArray1D& first);
		BoardArray1D& operator = (const BoardArray1D& rightSide); //assign op
		virtual ~BoardArray1D();	//destructure
		virtual int get_space_i() { return space/size2;}
		virtual int get_space_j() { return space%size2;}
	private:
		int size1;
		int size2;
		int *board;
		int space;
	};
}

#endif 