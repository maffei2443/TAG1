/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/

#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_
#include "nodes.hpp"
#include <vector>
#include <deque>
#include <string>
#include <set>
class Graph{
private:
	deque <Nodes*> node;

public:
	inline Nodes* get_node(int key){return node.at(key);}

	deque<Nodes*> :: iterator iterador(){auto ret = node.begin();ret++; return ret;}
	deque<Nodes*> :: iterator* iterador2(){return &node.begin();}
	deque<Nodes*> :: iterator end(){return node.end();}
	void insert(Nodes* no){node.push_back(no);}
};
#endif