X = -std=c++11 -fpermissive

all:	nodes.o graph.o bi.o
	g++ $(X)  nodes.o graph.o bi.o -o bi

nodes.o:	nodes.cpp
	g++ $(X) -c nodes.cpp
graph.o:	graph.cpp nodes.o
	g++ $(X) -c graph.cpp
bi.o:	bi.cpp graph.o
	g++ $(X) -c bi.cpp