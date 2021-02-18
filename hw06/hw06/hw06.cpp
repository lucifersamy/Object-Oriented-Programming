#include <iostream>
#include "gtucontainer.cpp"
#include "gtuset.cpp"
#include "gtuvector.cpp"

using namespace Container;


template <class T>
void printTest(GTUContainer<T> &test);

bool isNegative (int i);

template<class InputIterator, class UnaryPredicate>
InputIterator find_if (InputIterator first_e, InputIterator last_e, UnaryPredicate func);

template<class InputIterator, class T>
InputIterator find (InputIterator first_e, InputIterator last_e, const T& element);

template<class InputIterator, class Function>
Function for_each(InputIterator first_e, InputIterator last_e, Function func);

void print_mult_by_3 (int i);

int main()
{	
	/*I already used iterators in implementation*/
	GTUVector<int> testVector;
	cout << "-----------VECTOR TEST-----------" << endl; 
	cout << "insert 2\n";
	testVector.insert(2);
	printTest(testVector);
	cout << "insert 8\n";
	testVector.insert(8);
	printTest(testVector);
	cout << "clear test vector\n";
	testVector.clear();
	if(testVector.empty())
		cout << "test vector is empty\n";
	else
		cout << "test vector is not empty\n";
	cout << "insert 7\n";
	testVector.insert(7);
	printTest(testVector);
	cout << "insert 7 again\n";
	testVector.insert(7);
	printTest(testVector);
	cout << "insert -1\n";
	testVector.insert(-1);
	printTest(testVector);
	cout << "insert 9\n";
	testVector.insert(9);
	printTest(testVector);
	cout << "erase 7\n";
	testVector.erase(7);
	printTest(testVector);
	if(testVector.empty())
		cout << "test vector is empty\n";
	else
		cout << "test vector is not empty\n";
	cout << "size of test vector is: " << testVector.size()<<endl;
	cout << "capacity of test vector is: " << testVector.max_size()<<endl;

	cout << "\n\nGLOBAL FUNCTIONS"<<endl;
	cout << "find_if\n";
	GTUIterator<int> it = find_if (testVector.begin(), testVector.end(), isNegative);
  	cout << "The first negative value is " << *it << "\n\n";

	cout << "find\n";
  	cout<< "is 9 in vector?\n";
 	GTUIterator<int> it2 = find (testVector.begin(), testVector.end(), 9);
  	if (it2 == testVector.end())
    	cout  << "it is not founded in vector\n\n" ;	
 	else
   		cout <<  "it is founded in vector\n\n" ;


	cout << "for_each\n";
  	cout << "contains of vector that multiply by 3:\n";
  	for_each (testVector.begin(), testVector.end(), print_mult_by_3);
 	cout << "\n\n";



	GTUSet<int> testSet;
	cout << "\n\n-----------SET TEST-----------" << endl; 
	cout << "insert 2\n";
	testSet.insert(2);
	printTest(testSet);
	cout << "insert 8\n";
	testSet.insert(8);
	printTest(testSet);
	cout << "clear test vector\n";
	testSet.clear();
	if(testSet.empty())
		cout << "test vector is empty\n";
	else
		cout << "test vector is not empty\n";
	cout << "insert 7\n";
	testSet.insert(7);
	printTest(testSet);
	cout << "insert -1\n";
	testSet.insert(-1);
	printTest(testSet);
	cout << "insert 9\n";
	testSet.insert(9);
	printTest(testSet);
	cout << "erase 7\n";
	testSet.erase(7);
	printTest(testSet);
	if(testSet.empty())
		cout << "test vector is empty\n";
	else
		cout << "test vector is not empty\n";
	cout << "size of test vector is: " << testSet.size()<<endl;
	cout << "capacity of test vector is: " << testSet.max_size()<<endl;

	cout << "\n\nGLOBAL FUNCTIONS"<<endl;
	cout << "find_if\n";
	GTUIterator<int> it3 = find_if (testVector.begin(), testVector.end(), isNegative);
  	cout << "The first negative value is " << *it3 << "\n\n";

	cout << "find\n";
  	cout<< "is 9 in vector?\n";
 	GTUIterator<int> it4 = find (testVector.begin(), testVector.end(), 9);
  	if (it4 == testVector.end())
    	cout  << "it is not founded in vector\n" ;	
 	else
   		cout <<  "it is founded in vector\n" ;


	cout << "\nfor_each\n";
  	cout << "contains of vector that multiply by 3:\n";
  	for_each (testVector.begin(), testVector.end(), print_mult_by_3);
 	cout << "\n\n";

	try{
		cout << "insert 2\n";
		testSet.insert(2);
		printTest(testSet);
		cout << "trying inserting 2 again in a set. it can't. so it should throw exception\n\n";
		testSet.insert(2);
		printTest(testSet);
	}

	catch (const invalid_argument& what_arg) {
		cout << "Invalid argument: " << what_arg.what() << endl;
 	}
}


template <class T>
void printTest( GTUContainer<T> &test){
	for(auto it = test.begin(); it != test.end(); ++it)
		cout << *(it) << " ";
	cout << endl;
}

bool isNegative (int i) {
  return (i<0);
}

/*Returns an iterator to the first element in the range [first,last)
 for which pred returns true. If no such element is found, the function returns last.(cplusplus)*/
template<class InputIterator, class UnaryPredicate>
InputIterator find_if (InputIterator first_e, InputIterator last_e, UnaryPredicate func)
{
  while (first_e != last_e) {
    if (func(*first_e)) return first_e;
   		++first_e;
  }
  return last_e;
}

/*find : Returns an iterator to the first element in the range [first,last) 
that compares equal to val. If no such element is found, the function returns last.(cpluspus.com)*/
template<class InputIterator, class T>
InputIterator find (InputIterator first_e, InputIterator last_e, const T& element)
{
  while (first_e != last_e) {
    if (*first_e == element) return first_e;
   		++first_e;
  }
  return last_e;
}

void print_mult_by_3 (int i) {
  cout << i*3 << " ";
}
/*for each Applies function fn to each of the elements in the range [first,last).(cplusplus.com)*/
template<class InputIterator, class Function>
Function for_each(InputIterator first_e, InputIterator last_e, Function func)
{
  while (first_e != last_e) {
    func (*first_e);
    ++first_e;
  }
  return print_mult_by_3;
}
