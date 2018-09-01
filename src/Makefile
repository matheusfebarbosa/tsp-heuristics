#Author: Matheus Felipe Eduardo Barbosa

TP: main.o graph.o
	g++ main.o graph.o -o tp -std=c++1z -Wall -Wextra -pedantic
main.o: main.cpp
		g++ -c main.cpp -std=c++1z -Wall -Wextra -pedantic
graph.o: graph.cpp graph.h
		g++ -c graph.cpp -std=c++1z -Wall -Wextra -pedantic				
clean:
	rm *.o tp