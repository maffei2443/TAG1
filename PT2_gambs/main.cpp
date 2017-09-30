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
//	Graph * G = new Graph(9);
	Graph * G = new Graph("");
	cout << "Vai Criar grafo" << endl;
//	Graph * G = new Graph(""); 
	cout << "Criou grafo" << endl;
    G->mk_bi();					// Força a bidirecao
	cout << "Virou bi" << endl;

	G->show();

	cout << "Cliques maximos/maximais de grau 6 (os maiores da turma):\n";
    bk(G, 6);			// Pertence aa biblioteca graphop.hpp
//
	return 0;
}