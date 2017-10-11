/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/

#include <iostream>
#include <set>
#include <queue>
#include <cstdio>
#include <vector>
#include "nodes.hpp"
#include "graph.hpp"
#include "graphop.hpp"
#define cls cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

using namespace std;
int main(){

	Graph * G = new Graph(9);

	map <int, int> code_index;
	for(int i = 1; i < G->get_verts()+1; i++){
		// Criando o mapa para busca mais eficiente depois.
		code_index.insert(code_index.begin(), pair<int,int>(G->get_node(i)->get_key(), i));
	}
	vector<int> sorted = sort_tp(G);
	vector<int>::iterator it = sorted.begin();
	int i;
	for(i = 0; it != sorted.end(); it++, i++)
		cout << "Posicao: " << i+1 << " | Code == " << sorted[i] << " | Name: " << G->get_node(code_index.find(sorted[i])->second)->get_name() << endl;

	return 0;	
}
