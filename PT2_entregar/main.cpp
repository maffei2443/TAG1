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
#define CLS cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
#define ENTER cout << "Tecle enter para continuar..." << endl
#define WAIT getchar();
using namespace std;
// /*

//*/


int main(){
//	Graph * G = new Graph(9);

	cout << "Autores: Arthur da Silveira Couto 		16/0002575" << endl;
	cout << "Autores: Leonardo Maffei da Silva 		16/0033811" << endl;
	ENTER;	WAIT;	CLS;

	int useless = 0;
	Graph *  G = new Graph(useless);		// Apenas para chamar o contrutor correto

	cout << "Curso: Ciencia da Computacao" << endl;
	cout << "DAG(vertice, seguido de disciplinas que dependem dele):\n\n";
	ENTER;	WAIT;	CLS;
	
	G->show();
	ENTER;	WAIT;	CLS;




	map <int, int> code_index;
	for(int i = 1; i < G->get_verts()+1; i++){
		// Criando o mapa para busca mais eficiente depois.
		code_index.insert(code_index.begin(), pair<int,int>(G->get_node(i)->get_key(), i));
	}
	cout << "Ordenacao topologica:\n\n";
	ENTER;	WAIT;	CLS;

	vector<int> sorted = sort_tp(G);
	vector<int>::iterator it = sorted.begin();

	for(int i = 0; it != sorted.end(); it++, i++)
		cout << "Posicao: " << i+1 << " | Code == " << sorted[i] << " | Name: " << G->get_node(code_index.find(sorted[i])->second)->get_name() << endl;
	
	ENTER;	WAIT;	CLS;

	cout << "Caminho critico:\n\n";
	ENTER;	WAIT;	CLS;
	Critcpath way = dfs_cpg(G);
	int limit = way.sizequeue;
	for(int j = 0; j < limit; j++){
        cout  << "Codigo: " << way.keys.front() << "	Nome:	" << way.names.front() << endl;
        way.keys.pop();
        way.names.pop();
        way.sizequeue--;
    }

    cout << "Final do Trabalho 2." << endl;
	return 0;
}