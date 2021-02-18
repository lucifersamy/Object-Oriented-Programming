exe: hw05.o
	g++ -o exe abstractboard.o boardvector.o boardarray1d.o boardarray2d.o hw05.o

hw05.o : hw05.cpp abstractboard.o boardvector.o boardarray1d.o boardarray2d.o 
	g++ -c hw05.cpp -std=c++11

abstractboard.o : abstractboard.cpp
	g++ -c abstractboard.cpp -std=c++11

boardvector.o : abstractboard.o boardvector.cpp
	g++ -c boardvector.cpp -std=c++11

boardarray1d.o : abstractboard.o boardarray1d.cpp
	g++ -c boardarray1d.cpp -std=c++11

boardarray2d.o : abstractboard.o boardarray2d.cpp
	g++ -c boardarray2d.cpp -std=c++11

clean:
		rm *.o exe
