#include "nodes.hpp"
#include "graph.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

int main(){

	deque<Nodes*> foo;
	
	Nodes * neoo = new Nodes(1);

	foo.push_back(neoo);


	Graph * n = new Graph;
	for(int i = 1; i < 4; i++)
		n->insert(new Nodes(i));
	
	for(auto it = foo.begin(); it != foo.end(); it++){
		cout << (*it)->get_key() << endl;
	}

	for(auto it = n->iterador(); it != n->end(); it++){
		cout << (*it)->get_key() << endl;
	}

	return 0;
















	Graph * neo = new Graph;
	for(int i = 1; i < 4; i++)
		neo->insert(new Nodes(i));

	neo->get_node(1)->set_nxt_back(neo->get_node(2));
	neo->get_node(1)->set_nxt_back(neo->get_node(3));
	neo->get_node(2)->set_nxt_back(neo->get_node(3));


	for(int i = 1; i < 4; i++)
		for (auto it = neo->get_node(i)->get_nxt(); it != neo->get_node(i)->get_end(); it++){
			printf("Iterando sobre node[%d] :: ", i); cout <<  (*it)->get_key() << endl;
		}
	
	Graph * neu = new Graph;
	for(int i = 1; i < 4; i++)
		neu->insert(new Nodes(i));

	for(int i = 1; i < 4; i++)
		for (auto it = neu->get_node(i)->get_nxt(); it != neu->get_node(i)->get_end(); it++){
			printf("Iterando sobre node[%d] :: ", i); cout <<  (*it)->get_key() << endl;
		}
	
	cout << "Debug" << endl;
	for (auto it = neu->iterador(); it != neu->end(); it++)
		cout << (*it)->get_key() << endl;
	return 0;
}