/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/

#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_
#include "nodes.hpp"
#include <vector>
#include <string>
#include <set>
class Graph{
private:
	void exclui_aninhado(Nodes*);
	void mostra_set(set <int> to_show);
	void exclude_list(int);	// Exclui um vertice e suas adjacencias. Consertar: nao exclui os que o referenciam. Serve portanto apenas p/ o destrutor
	vector <Nodes*> node;
	int verts;
	int edge;

public:
	inline int get_verts(){return verts;}
	inline int get_edge(){return edge;}
	inline Nodes* get_node(int i){return node[i];}
//	inline vector<Nodes*> get_vet_node(){return node;}
	vector<Nodes*> :: iterator iterador(){return node.begin();}
	vector<set<int> > adjacentes;
	Graph();
	Graph(int);		// Construtor 
	Graph(string);
	Graph(string, string);
	~Graph();
	
	void mk_bi();			// Arestas direcionadas passam a ser sem direcao
	void reset();			/// Apaga o grafo
	void insert(Nodes*);	/// Insere novo noh no grafo
	void insert_qtd_nxt(int, Nodes*, int);	/// Indice do no de origem,No nxt e o cost do caminho
//	void insert_end(int, Nodes*, int);	/// Insere no final da lista

	void cliques_no_maximais(Nodes* no, set<int>candidatos);
	void max_click();

	vector <int> list(int);
	void show();
	void show_verts();
	void show_nodes();
};
#endif