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
// /*

//*/

int main(){
//    Graph * G = new Graph("sdd", ""); 
	Graph * G = new Graph("ssd"); 
	cout << "Criou grafo" << endl;
    G->mk_bi();					// Força a bidirecao
	cout << "Virou bi" << endl;

	G->show_nodes();

    cout << "Grafo em ordem Decrescente de numero de amigos (grau):\n";
	sort_reach_r(G);
	G->show_nodes();
	cls;
	
	cout << "Grafo em ordem crescente de chave:\n";
	sort_key(G);
	G->show_nodes();
	cls;

	
	cout << "Grafo em ordem decrescente de amigos (apenas chhave e matricula):\n";
	mostra_por_nota(G);	// Pertence aa biblioteca graphop.hpp
	cls;

	cout << "Cliques maximos/maximais de grau 6 (os maiores da turma):\n";
    bk(G, 6);			// Pertence aa biblioteca graphop.hpp
	return 0;
}