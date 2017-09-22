/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/



#ifndef _NODES_HPP_
#define _NODES_HPP_
#include <string>
#include <cstdio>		//DEBUGG
#include <iostream>		//DEBUGG
using namespace std;
class Nodes{
private:
public:
	int chave, matricula;	/// ID do vertice, matricula
	int amigos;				/// Nohs adjacentes a esse noh
	string nome;			/// Nome do estudante
	int custo;				/// Custo para ir ateh o noh. Por padrao, eh 1.
	bool visit;
	Nodes * vizinho;		/// Para fazer a lista de adjacencia
	Nodes() : chave(-1), matricula(-1), amigos(0), nome(""), visit(false), custo(1), vizinho(NULL){}
	Nodes(int key) : chave(key), visit(false), custo(1),vizinho(NULL){}
	Nodes(int key, int cost) : chave(key), visit(false), custo(cost),vizinho(NULL){}
	Nodes(Nodes * cpy) : chave(cpy->chave), matricula(cpy->matricula), amigos(cpy->amigos), nome(cpy->nome), custo(cpy->custo), visit(false), vizinho(NULL){}
	Nodes(Nodes * cpy, int cost) : chave(cpy->chave), matricula(cpy->matricula), amigos(cpy->amigos), nome(cpy->nome), custo(cost), visit(false), vizinho(NULL){}

	void mostra_no();
	void mostra_lista();			/// Mostra lista em ordem de insercao
	void mostra_lista_rersa();	/// Mostra lista em ordem contraria de insercao
	void insert_nxt_pro(Nodes*);
	void insert_nxt_pro(Nodes*, int);	/// Vizinho com custo
	void insert_nxt_pro_debug(Nodes*);
	void insere_pre_calculado(Nodes*);
};

#endif