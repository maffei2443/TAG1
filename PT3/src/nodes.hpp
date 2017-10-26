/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/



#ifndef _NODES_HPP_
#define _NODES_HPP_
#include <set>
#include <string>
#include <iostream>		//DEBUGG
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
	bool teacher;
	Nodes * teacher1;
	Nodes * teacher2;
	int key, hab;				/// semantica dependese eh professor ou escola
	int qtd_nxt;				/// Nohs adjacentes a esse noh
	bool visit;
	set <int> already;			// Conjunto dos que jah estao na lista de adjacencia. Impede arestas paralelas.
	deque <Nodes*> nxt;		/// Para fazer a lista de adjacencia
public:

	Nodes(int k, int h) : teacher(true),  hab(h), key(k), qtd_nxt(0), visit(false), teacher1(NULL), teacher2(NULL){}
	Nodes(int k, int h, char) : teacher(false), hab(h), key(k+100), qtd_nxt(0), visit(false), teacher1(NULL), teacher2(NULL){}
	
	inline int get_key(){return key;}
	inline int get_hab(){return hab;}
	inline int get_qtd_nxt(){return qtd_nxt;}
	inline bool get_visit(){return visit;}
	deque<Nodes*>::iterator get_nxt(){return nxt.begin();}	// Retorna iterador constante para o primeiro elemento dos que o noh pode atingir
	deque<Nodes*>::iterator get_end(){return nxt.end();}	// Retorna iterador constante para o primeiro elemento dos que o noh pode atingir

	void set_nxt_front(Nodes * no);
	void set_nxt_back(Nodes * no);
	void remove_nxt_front();
	void remove_nxt_back();
	
//	inline void set_qtd_nxt(int qtd_nxt){ this->qtd_nxt = qtd_nxt;}
//	inline void set_key(int key){this->key = key;}

	void remove_all_nxt();
//	inline string set_name(string name){ this->name = name;}	// Causou um bug lvl hard
	inline void set_visit(bool visit){ this->visit = visit;}
	
};

#endif