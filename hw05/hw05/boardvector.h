#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H
#include "abstractboard.h"
#include <vector>

namespace Game
{
	class BoardVector : public AbstractBoard
	{
	public:
		BoardVector();
		virtual void print() const;
		virtual void readFromFile(const string fileName);
		virtual void writeToFile(const string fileName) const;
		virtual void reset();
		virtual void setSize(int size1,int size2);
		virtual int move(char m);
		virtual bool isSolved() const;
		virtual int operator() (int i, int j) const;
		virtual bool operator == (const BoardVector& first) ;
		virtual ~BoardVector() {};
		virtual int get_space_i() { return space[0];}
		virtual int get_space_j() { return space[1];}
	private:
		vector<vector <int> > board;
		vector<int> space;
	};
}

#endif 