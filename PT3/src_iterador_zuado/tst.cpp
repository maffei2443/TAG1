#include "nodes.hpp"
#include "graph.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

int main(){
	Graph * neo = new Graph;
	for(int i = 1; i < 4; i++)
		neo->insert(new Nodes(i));

	neo->get_node(1)->set_nxt_back(neo->get_node(2));
	neo->get_node(1)->set_nxt_back(neo->get_node(3));
	neo->get_node(2)->set_nxt_back(neo->get_node(3));

	auto x = 999999;
	cout << x << endl;
	for(int i = 1; i < 4; i++)
		for (deque<Nodes*>::iterator it = neo->get_node(i)->get_nxt(); it != neo->get_node(i)->get_end(); it++){
			printf("Iterando sobre node[%d] :: ", i); cout <<  (*it)->get_key() << endl;
		}
		
	return 0;
}