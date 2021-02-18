#include "gtuvector.h"

namespace Container
{
	template<class T>
	GTUVector<T>::GTUVector(){
		this->_capacity = 1;
		this->_used = 0;
		shared_ptr<T> temp(new T[this->_capacity], default_delete<T[]>());
		this->_data = temp;
	}

	template<class T>
	bool GTUVector<T>::empty() const{	
		if(this->_used != 0)
			return false;
		return true;
	}

	template<class T>
	GTUIterator<T> GTUVector<T>::begin(){
		return (this->_data).get();
	}

	template<class T>
	GTUIterator<T> GTUVector<T>::end(){
		return (this->_data).get() + this->_used;
	}

	template<class T>
	int GTUVector<T>::size() const{
		return(this->_used);
	}

	template<class T>
	int GTUVector<T>::max_size() const{
		return 2000000;
	}

	template<class T>
	T GTUVector<T>::operator[] (int index)
	{
		if (index >= this->_used) 
	    { 
	        cout << "Array index out of bound, exiting"; 
	        exit(0); 
	    } 
	    return this->_data[index]; 
	}
	/*Insert element and update new elements informations*/
	template<class T>
	void GTUVector<T>::insert(T element){	

		shared_ptr<T> tmp_shared_ptr = this->_data;
		shared_ptr<T> c_shared (new T [this->_used+1],default_delete<T[]>());

		this->_data = c_shared;
		for(int i=0 ; i < this->_used ; ++i)
			this->_data.get()[i] = tmp_shared_ptr.get()[i];
		
		this->_data.get()[this->_used] = element;
		this->_used++;	
	}

	/*finding element, deleting and shifting other elements previous index*/
	template<class T>
	void GTUVector<T>::erase(T element){	
		int current_used=0;
		T * temp(new T [this->_used]);

		for(int i=0,j=0 ; i < this->_used; ++i,++j){
				if(element ==this->_data.get()[i])
					--j;
				else{
					++current_used;
					temp[j] = this->_data.get()[i];
				}
		}

		shared_ptr<T> c_shared (new T [current_used],default_delete<T[]>());

		this->_data = c_shared;
		this->_used = current_used;

		for(int i=0 ; i < current_used ; ++i)
			this->_data.get()[i] = temp[i];
	}

	template<class T>
	void GTUVector<T>::clear(){
		this->_used = 0;
		this->_data = nullptr;
	}
}


