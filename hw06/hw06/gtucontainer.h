#ifndef GTU_CONTAINER_H
#define GTU_CONTAINER_H
#include "gtuiterator.h"
#include "gtuiteratorconst.h"
#include <vector>
#include <set>
#include <memory>	
#include <iostream>
using namespace std;

namespace Container
{
	template<class T>
	class GTUContainer
	{
		public:
			GTUContainer()
			{	}
			virtual ~GTUContainer()
			{	}
			virtual bool empty() const = 0;
			virtual int size() const = 0;  
			virtual int max_size() const = 0;
			virtual void insert(T) = 0; 
			virtual void erase(T) = 0;
			virtual void clear() = 0;
			virtual GTUIterator<T> begin() = 0;
			virtual GTUIterator<T> end() = 0;
		protected:
			int _capacity, _used;
			shared_ptr<T> _data; 
	};
}

#endif


