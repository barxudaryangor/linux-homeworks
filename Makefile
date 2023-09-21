all: complexNum

complexNum: main.o complex.o
	g++ -o complexNum main.o complex.o
complex.o: complex.cpp complex.h
	g++ -c complex.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o complexNum
