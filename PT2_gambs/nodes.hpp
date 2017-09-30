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
	int key, matricula;	/// ID do vertice, matricula
	int qtd_nxt;				/// Nohs adjacentes a esse noh
	int in, out;
	string name;			/// Nome do estudante
	int cost;				/// Custo para ir ateh o noh. Por padrao, eh 1.
	bool visit;
	Nodes * nxt;		/// Para fazer a lista de adjacencia
public:
	Nodes() : in(0), out(0), key(-1), matricula(-1), qtd_nxt(0), name(""), visit(false), cost(1), nxt(NULL){}
	Nodes(int keyy) : in(0), out(0), key(keyy), visit(false), cost(1),nxt(NULL){}
	Nodes(int keyy, int cost) : in(0), out(0), key(keyy), visit(false), cost(cost),nxt(NULL){}
	Nodes(Nodes * cpy) : in(cpy->get_in()), out(cpy->get_out()), key(cpy->get_key()), matricula(cpy->get_matricula()), qtd_nxt(cpy->get_qtd_nxt()), name(cpy->get_name()), cost(cpy->get_cost()), visit(false), nxt(NULL){
		if(nxt == NULL)	this->nxt = NULL;
		else			this->nxt = new Nodes(cpy->get_nxt());
	}
	Nodes(Nodes * cpy, int cost) : in(cpy->get_in()), out(cpy->get_out()), key(cpy->get_key()), matricula(cpy->get_matricula()), qtd_nxt(cpy->get_qtd_nxt()), name(cpy->get_name()), cost(cost), visit(false), nxt(NULL){}
	~Nodes(){del_nxt();}

	inline int get_key(){return key;}
	inline int get_matricula(){return matricula;}
	inline int get_qtd_nxt(){return qtd_nxt;}
	inline int get_in(){return in;}
	inline int get_out(){return out;}
	inline string get_name(){return name;}
	inline int get_cost(){return cost;}
	inline bool get_visit(){return visit;}
	Nodes * get_nxt(){return nxt;}

	inline void set_key(int key){this->key = key;}
	inline void set_matricula(int matricula){ this->matricula = matricula;}
	inline void set_qtd_nxt(int qtd_nxt){ this->qtd_nxt = qtd_nxt;}
	inline void set_in(int in){ this->in = in;}
	inline void set_out(int out){ this->out = out;}
	inline void plus_in(int add){this->in += add;}
	inline void plus_out(int add){this->out += add;}
//	inline string set_name(string name){ this->name = name;}	// Causou um bug lvl hard
	inline void set_name(const string& name){ this->name = name;}
	inline void set_cost(int cost){ this->cost = cost;}
	inline void set_visit(bool visit){ this->visit = visit;}
	inline void set_nxt(Nodes * nxt){this->nxt = nxt;}
	

	void mostra_no();
	void mostra_lista();			/// Mostra lista em ordem de insercao
	void mostra_lista_rersa();	/// Mostra lista em ordem contraria de insercao
	void insert_qtd_nxt_pro(Nodes*);		/// Vizinho com cost = 1
	void insert_qtd_nxt_pro(Nodes*, int);	/// Vizinho com cost
	void insert_qtd_nxt_pro_debug(Nodes*);
	void insere_pre_calculado(Nodes*);
	void del_nxt();	
};

#endif