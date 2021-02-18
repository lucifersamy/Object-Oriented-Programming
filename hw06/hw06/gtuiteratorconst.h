#ifndef GTU_ITERATOR_CONST_H
#define GTU_ITERATOR_CONST_H
#include <memory>

namespace Container{

template <typename T>
class GTUIteratorConst{
	public:

		GTUIteratorConst(T *current){
			data = current;
		}

		GTUIteratorConst& operator = (const GTUIteratorConst &other){
			if(&other == this)
				return *this;
			data = other.data;
			return *this;
		}

		const T& operator * () const{
			return *data;
		}

		const T* operator -> () const{
			return data;
		}

		bool operator == (const GTUIteratorConst &other) const{
			return this->data == other.data;	
		}

		bool operator != (const GTUIteratorConst &other) const{
			return !(*this==other);
		}

		GTUIteratorConst& operator ++ (){
			data++;
			return *this;
		}

		GTUIteratorConst& operator ++ (int ignoreMe){
			GTUIteratorConst temp = *this;
			data++;
			return temp;
		}

		GTUIteratorConst& operator -- (){
			data--;
			return *this;
		}

		GTUIteratorConst& operator -- (int ignorMe){
			GTUIteratorConst temp = *this;
			data--;
			return temp;
		}

	private:
		T* data;
	};
}

#endif