/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/



#ifndef _NODES_HPP_
#define _NODES_HPP_
#include <string>
#include <iostream>		//DEBUGG
#include <set>
#include <deque>
using namespace std;
class Nodes;
/*
typedef struct {
	Nodes * no;
	int w;			// weight
}aresta_no;
*/
class Nodes{
private:
	int key, matricula;	/// ID do vertice, matricula
	int qtd_nxt;				/// Nohs adjacentes a esse noh
	int in, out;
	string name;			/// Nome do estudante
	int cost, payment;				/// Custo para ir ateh o noh. Por padrao, eh 1.
	bool visit;
	set <int> already;
	deque <Nodes*> nxt;		/// Para fazer a lista de adjacencia
public:

	Nodes() : in(0), out(0),payment(0), key(-1), matricula(-1), qtd_nxt(0), name(""), visit(false), cost(1){}
	Nodes(int keyy) : in(0), out(0), payment(0), key(keyy), visit(false), cost(1){}
	Nodes(int keyy, int cost) : in(0), out(0),  payment(0), key(keyy), visit(false), cost(cost){}


	inline int get_key(){return key;}
	inline int get_matricula(){return matricula;}
	inline int get_qtd_nxt(){return qtd_nxt;}
	inline int get_in(){return in;}
	inline int get_out(){return out;}
	inline string get_name(){return name;}
	inline int get_cost(){return cost;}
	inline int get_payment(){return payment;}
	inline bool get_visit(){return visit;}
	deque<Nodes*>::iterator get_nxt(){return nxt.begin();}	// Retorna iterador constante para o primeiro elemento dos que o noh pode atingir
	deque<Nodes*>::iterator get_end(){return nxt.end();}	// Retorna iterador constante para o primeiro elemento dos que o noh pode atingir

	inline void set_key(int key){this->key = key;}
	inline void set_matricula(int matricula){ this->matricula = matricula;}
	inline void set_qtd_nxt(int qtd_nxt){ this->qtd_nxt = qtd_nxt;}
	inline void set_in(int in){ this->in = in;}
	inline void set_out(int out){ this->out = out;}
	inline void set_payment(int pay){ this->payment = pay;}
	void set_nxt_front(Nodes * nxt);
	void set_nxt_back(Nodes * nxt);
	void remove_nxt_front();
	void remove_nxt_back();
	

	void remove_all_out();
	inline void plus_in(int add){this->in += add;}
	inline void plus_out(int add){this->out += add;}
//	inline string set_name(string name){ this->name = name;}	// Causou um bug lvl hard
	inline void set_name(const string& name){ this->name = name;}
	inline void set_cost(int cost){ this->cost = cost;}
	inline void set_visit(bool visit){ this->visit = visit;}
	
	

	void mostra_no();
	void mostra_lista();			/// Mostra lista em ordem de insercao
	void mostra_lista_reversa();	/// Mostra lista em ordem contraria de insercao
};

#endif