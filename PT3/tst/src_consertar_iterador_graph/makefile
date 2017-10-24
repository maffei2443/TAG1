X = -std=c++11
######################################################
BI:	nodes.o graph.o bi.o
	g++ $(X)  nodes.o graph.o bi.o -o bi
######################################################
TST:	nodes.o graph.o tst.o
	g++ $(X)  nodes.o graph.o tst.o -o tst
######################################################
MAIN:	nodes.o graph.o critcpath.o graphop.o main.o 
	g++ $(X) graphop.o critcpath.o nodes.o graph.o main.o -o main  
critcpath.o:	critcpath.cpp critcpath.hpp
	g++ $(X) -c critcpath.cpp
nodes.o:	nodes.cpp nodes.hpp
	g++ $(X) -c nodes.cpp
graph.o:	graph.cpp graph.hpp
	g++ $(X) -c graph.cpp
##Parte do Arthur###
BFS.o:	BFS.cpp BFS.hpp
	g++ $(X) -c BFS.cpp
####################
graphop.o: graphop.cpp graphop.hpp
	g++ $(X) -c graphop.cpp	
main.o:	main.cpp
	g++ $(X) -c main.cpp
######################################################
######################################################	
bi.o:	bi.cpp
	g++ $(X) -c bi.cpp
tst.o:	tst.cpp
	g++ $(X) -c tst.cpp
#########################################
#########################################
#########################################
CRITC:	graphop.o nodes.o graph.o critc.o 
	g++ $(X) graphop.o nodes.o graph.o critc.o -o critc  
critc.o:
	g++ $(X) critc.cpp -c critc