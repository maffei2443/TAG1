X = -std=c++11 -fpermissive

all:	nodes.o graph.o bi.o
	g++ $(X)  nodes.o graph.o bi.o -o bi

nodes.o:	nodes.cpp nodes.hpp
	g++ $(X) -c nodes.cpp
graph.o:	nodes.cpp graph.hpp
	g++ $(X) -c graph.cpp
bi.o:	bi.cpp
	g++ $(X) -c bi.cpp