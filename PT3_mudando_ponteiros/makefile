######################################################
TESTE:	nodes.o graph.o teste.o
	g++ -fpermissive -std=c++11 nodes.o graph.o teste.o -o teste

######################################################
MAIN:	nodes.o graph.o critcpath.o graphop.o main.o 
	g++ -fpermissive -std=c++11 graphop.o critcpath.o nodes.o graph.o main.o -o main  
critcpath.o:	critcpath.cpp critcpath.hpp
	g++ -c critcpath.cpp
nodes.o:	nodes.cpp nodes.hpp
	g++ -c nodes.cpp
graph.o:	graph.cpp graph.hpp
	g++ -c graph.cpp
##Parte do Arthur###
BFS.o:	BFS.cpp BFS.hpp
	g++ -c BFS.cpp
####################
graphop.o: graphop.cpp graphop.hpp
	g++ -c graphop.cpp	
main.o:	main.cpp
	g++ -c main.cpp
######################################################
######################################################	

TST:	graphop.o nodes.o graph.o tst.o 
	g++ -fpermissive -std=c++11 graphop.o nodes.o graph.o tst.o -o tst  
####################
tst.o:	tst.cpp
	g++ -c tst.cpp
#########################################
#########################################
#########################################
CRITC:	graphop.o nodes.o graph.o critc.o 
	g++ -fpermissive -std=c++11 graphop.o nodes.o graph.o critc.o -o critc  
critc.o:
	g++ critc.cpp -c critc