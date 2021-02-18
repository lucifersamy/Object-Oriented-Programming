#ifndef GTUVector_H
#define GTUVector_H

#include "gtucontainer.h"

namespace Container
{
	template <class T>
	class GTUVector : public GTUContainer<T>
	{
		
	public:
		GTUVector();
		bool empty() const override;
		int size() const override;
		int max_size() const override;
		void insert(T) override;
		void erase(T) override;
		void clear() override;
		T operator[] (int index);
		GTUIterator<T> begin() override;
		GTUIterator<T> end() override;
	};
}

#endif