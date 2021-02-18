#include "gtuset.h"

namespace Container
{
	template<class T>
	GTUSet<T>::GTUSet(){
		this->_capacity = 1;
		this->_used = 0;
		shared_ptr<T> temp(new T[this->_capacity], default_delete<T[]>());
		this->_data = temp;
	}

	template<class T>
	bool GTUSet<T>::empty() const{	
		if(this->_used != 0)
			return false;
		return true;
	}

	template<class T>
	GTUIterator<T> GTUSet<T>::begin(){
			return (this->_data).get();
	}
	
	template<class T>
	GTUIterator<T>  GTUSet<T>::end(){
			return (this->_data).get() + this->_used;
	}


	template<class T>
	int GTUSet<T>::size() const{
		return(this->_used);
	}

	template<class T>
	int GTUSet<T>::max_size() const{
		return 200000;
	}

	/*Insert element, throws exception std::bad_pafram if there is a problem with insersion*/
	template<class T>
	void GTUSet<T>::insert(T element){	
	
		T * temp_ptr = this->_data.get();
		/*if element is already exist in set*/
		for(int i = 0 ; i < this -> _used ; ++i , ++temp_ptr){	
			if(*temp_ptr == element){	
				throw invalid_argument("This element already exists");	
			}
		}
		/*if element is not exist it inserts the set and update new elements informations*/
		shared_ptr<T> tmp_shared_ptr = this->_data;

		shared_ptr<T> c_shared (new T [this->_used+1],default_delete<T[]>());

		this->_data = c_shared;

		for(int i=0 ; i < this->_used ; ++i)
			this->_data.get()[i] = tmp_shared_ptr.get()[i];
		
		this->_data.get()[this->_used] = element;
		this->_used++;	
	}

	template<class T>
	void GTUSet<T>::erase(T element){
		int current_used=0;
		T * temp(new T [this->_used]);
		/*finding element, deleting and shifting other elements previous index*/
		for(int i=0,j=0 ; i < this->_used; ++i,++j){
				if(element == this->_data.get()[i])
					--j;
				else{
					++current_used;
					temp[j] = this->_data.get()[i];
				}
		}
		/*cleaning*/
		shared_ptr<T> c_shared (new T [current_used],default_delete<T[]>());

		this->_data = c_shared;
		this->_used = current_used;

		for(int i=0 ; i < current_used ; ++i)
			this->_data.get()[i] = temp[i];

	}

	template<class T>
	void GTUSet<T>::clear(){
		this->_used = 0;
		this->_data = nullptr;
	}
}