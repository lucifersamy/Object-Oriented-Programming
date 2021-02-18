#ifndef GTUSet_H
#define GTUSet_H

#include "gtucontainer.h"

namespace Container
{
	template <class T>
	class GTUSet : public GTUContainer<T>
	{
		
	public:
		GTUSet();
		bool empty() const override;
		int size() const override;
		int max_size() const override;
		void insert(T) override;
		void erase(T) override;
		void clear() override;
		GTUIterator<T> begin() override;
		GTUIterator<T> end() override;
	};
}

#endif