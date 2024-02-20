all: first second

first: first.cpp shared_array.cpp shared_array.h
	g++ -pthread -o first first.cpp shared_array.cpp

second: second.cpp shared_array.cpp shared_array.h
	g++ -pthread -o second second.cpp shared_array.cpp

clean:
	rm -f first second
