X = -std=c++11 -fpermissive
######################################################
BI:	nodes.o graph.o bi.o
	g++ $(X)  nodes.o graph.o bi.o -o bi
######################################################
TST:	nodes.o graph.o tst.o
	g++ $(X)  nodes.o graph.o tst.o -o tst
######################################################
MAIN:		nodes.o graph.o main.o 
	g++ $(X) nodes.o graph.o main.o -o main
MAIN2:		nodes.o graph.o main_debug.o 
	g++ $(X) nodes.o graph.o main_debug.o -o main_debug
######################################################

nodes.o:	nodes.cpp nodes.hpp
	g++ $(X) -c nodes.cpp
graph.o:	graph.cpp graph.hpp
	g++ $(X) -c graph.cpp
####################
graphop.o: graphop.cpp graphop.hpp
	g++ $(X) -c graphop.cpp	
######################################################
######################################################	
bi.o:	bi.cpp
	g++ $(X) -c bi.cpp
tst.o:	tst.cpp
	g++ $(X) -c tst.cpp
main.o:	nodes.o graph.o main.cpp
	g++ $(X) -c main.cpp
main_debug.o:	nodes.o graph.o main_debug.cpp
	g++ $(X) -c main_debug.cpp
#########################################
#########################################
#########################################
CRITC:	graphop.o nodes.o graph.o critc.o 
	g++ $(X) graphop.o nodes.o graph.o critc.o -o critc  
critc.o:
	g++ $(X) critc.cpp -c critc
