######################################################
######################################################
MAIN:	graphop.o nodes.o graph.o main.o 
	g++ -fpermissive -std=c++11 graphop.o nodes.o graph.o main.o -o main 
	rm *.o 
graphop.o: graphop.cpp graphop.hpp
	reset
	g++ -c graphop.cpp	
nodes.o:	nodes.cpp nodes.hpp
	g++ -c nodes.cpp
graph.o:	graph.cpp graph.hpp
	g++ -c graph.cpp
##Parte do Arthur###
BFS.o:	BFS.cpp BFS.hpp
	g++ -c BFS.cpp
queue.o:	queue.cpp queue.hpp
	g++ -c queue.cpp
####################
main.o:	main.cpp
	g++ -c main.cpp
######################################################
######################################################	