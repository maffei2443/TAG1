/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/

#ifndef _GRAPHFLUX_HPP_
#define _GRAPHFLUX_HPP_
#include "nodes.hpp"
#include <vector>
#include <string>
#include <set>
template <class T>
class Graphflux{
private:
	void exclui_aninhado(T*);
	void mostra_set(set <int> to_show);
	void exclude_list(int);	// Exclui um vertice e suas adjacencias. Consertar: nao exclui os que o referenciam. Serve portanto apenas p/ o destrutor
	vector <T*> node;
	int verts;
	int edge;

public:
	inline int get_verts(){return verts;}
	inline int get_edge(){return edge;}
	inline T* get_node(int i){return node[i];}
//	inline vector<T*> get_vet_node(){return node;}
	vector<T*> :: iterator iterador(){return node.begin();}
	vector<set<int> > adjacentes;
	Graphflux();
	Graphflux(int);		// Construtor 
	Graphflux(string);
	Graphflux(string, string);
	~Graphflux();
	
	void mk_bi();			// Arestas direcionadas passam a ser sem direcao
	void reset();			/// Apaga o grafo
	void insert(T*);	/// Insere novo noh no grafo
	void insert_qtd_nxt(int, T*, int);	/// Indice do no de origem,No nxt e o cost do caminho
//	void insert_end(int, T*, int);	/// Insere no final da lista

	void cliques_no_maximais(T * no, set<int>candidatos);
	void max_click();

	vector <int> list(int);
	void show();
	void show_verts();
	void show_nodes();
};
