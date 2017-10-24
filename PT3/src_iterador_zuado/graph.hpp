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
	void mostra_set(set <int> to_show);
	void exclude_list(int);	// Exclui um vertice e suas adjacencias. Consertar: nao exclui os que o referenciam. Serve portanto apenas p/ o destrutor
	deque <Nodes*> node;
	int verts;
	int edge;
	int sum_pay;
public:
	inline int get_verts(){return verts;}
	inline int get_edge(){return edge;}
	inline Nodes* get_node(int key){return node.at(key);}
	inline int get_sum_pay(){return sum_pay;}

//	inline vector<Nodes*> get_vet_node(){return node;}
	deque<Nodes*> :: const_iterator iterador(){return node.begin();}
	vector<set<int> > adjacentes;
	Graph();
	~Graph();
	
///	void mk_bi();			// Arestas direcionadas passam a ser sem direcao
	void reset();			/// Apaga o grafo
	void insert(Nodes*);	/// Insere novo noh no grafo (no final da lsita de nohs)
///	void insert_qtd_nxt(int, Nodes*, int);	/// Indice do no de origem,No nxt e o cost do caminho

	void max_click();

	vector <int> list(int);
	void show();
	void show_verts();
	void show_nodes();
};
#endif