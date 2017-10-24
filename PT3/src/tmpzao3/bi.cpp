#include "graph.cpp"
#include <queue>
#include <set>
#include <iostream>
using namespace std;

int main(){
	Graph * G;
	G = new Graph;

	G->insert(new Nodes(1));
	G->insert(new Nodes(2));
	G->insert(new Nodes(3));

	G->get_node(1)->set_nxt_back(G->get_node(2));
	G->get_node(2)->set_nxt_back(G->get_node(1));

	G->get_node(1)->set_nxt_back(G->get_node(3));
	G->get_node(3)->set_nxt_back(G->get_node(1));

	G->get_node(2)->set_nxt_back(G->get_node(3));
	G->get_node(3)->set_nxt_back(G->get_node(2));

	for(auto i = 1; i < 4; i++){
		cout << "Iterating over " << i << endl;
		for(auto it = G->get_node(i)->get_nxt(); it != G->get_node(i)->get_end();it++)
			cout << "neighbor :: " << (*it)->get_key() << endl;
	}

	for(int i = 1; i < 4; i++){
		auto x = G->iterador();
		cout << "iterating at " << i << endl;
		for(auto y = (*x)->get_nxt(); y != (*x)->get_end(); y++)
			cout << "Neighbor : " << (*y)->get_key() << endl;
		x++;
	}


}