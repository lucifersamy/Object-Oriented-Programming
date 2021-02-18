#ifndef GTUITERATOR_H
#define GTUITERATOR_H
#include <memory>

namespace Container{

template <typename T>
class GTUIterator{
public:

	GTUIterator(T *current) {
		_new = current;
	}

	GTUIterator& operator = (const GTUIterator &other) {
		_new = other._new;
		return *this;
	}
	// indirection operator overload
	T& operator * () const {
		return *_new;
	}
	// arrow member operator overload
	T* operator -> () const {
		return _new;
	}
	// is equal operator (checks if two are the same)
	bool operator == (const GTUIterator &other) const{
		return this->_new == other._new;	
	}
	// opposite of is equal operator
	bool operator != (const GTUIterator &other) const{
		return !(*this==other);
	}
	// address increment (prefix)
	GTUIterator& operator ++ (){
		_new++;
		return *this;
	}
	// address increment (postfix)
	GTUIterator& operator ++ (int ignoreable){
		GTUIterator tmp = *this;
		_new++;
		return tmp;
	}
	// address decrement (prefix)
	GTUIterator& operator -- (){
		_new--;
		return *this;
	}
	// address decrement (postfix)
	GTUIterator& operator -- (int ignoreable){
		GTUIterator tmp = *this;
		_new--;
		return tmp;
	}
	// basic getter
	T* getCurrent() const{
		return _new;
	}
private:
	// data member
	T* _new;
};
}

#endif