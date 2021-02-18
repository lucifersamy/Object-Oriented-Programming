exe: hw06.o gtucontainer.o gtuset.o gtuvector.o gtuiterator.o gtuiteratorconst.o
	g++ -o exe gtucontainer.o gtuset.o gtuvector.o hw06.o gtuiterator.o gtuiteratorconst.o

hw06.o : hw06.cpp gtucontainer.o gtuset.o gtuvector.o gtuiterator.o gtuiteratorconst.o
	g++ -c hw06.cpp -std=c++11

gtucontainer.o : gtucontainer.cpp
	g++ -c gtucontainer.cpp -std=c++11

gtuset.o : gtuset.cpp gtuset.h gtucontainer.o
	g++ -c gtuset.cpp -std=c++11

gtuvector.o : gtuvector.cpp gtuvector.h gtucontainer.o
	g++ -c gtuvector.cpp -std=c++11

gtuiterator.o : gtuiterator.cpp gtuiterator.h gtucontainer.o
	g++ -c gtuiterator.cpp -std=c++11

gtuiteratorconst.o : gtuiteratorconst.cpp gtuiteratorconst.h gtucontainer.o
	g++ -c gtuiteratorconst.cpp -std=c++11

clean:
		rm *.o exe
