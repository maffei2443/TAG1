#include <deque>
#include <iostream>
#include <string>
#include <iostream>		//DEBUGG
#include <set>
#include <deque>
using namespace std;

class No{
public:
	int oo;
	deque <No*> nxt;
	deque<No*>::const_iterator func(){return nxt.begin();}
};


/*
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


	deque<Nodes*>::const_iterator get_nxt(){return nxt.begin();}	// Retorna iterador constante para o primeiro elemento dos que o noh pode atingir
	inline int get_key(){return key;}
	inline int get_matricula(){return matricula;}
	inline int get_qtd_nxt(){return qtd_nxt;}
	inline int get_in(){return in;}
	inline int get_out(){return out;}
	inline string get_name(){return name;}
	inline int get_cost(){return cost;}
	inline int get_payment(){return payment;}
	inline bool get_visit(){return visit;}

	inline void set_key(int key){this->key = key;}
	inline void set_matricula(int matricula){ this->matricula = matricula;}
	inline void set_qtd_nxt(int qtd_nxt){ this->qtd_nxt = qtd_nxt;}
	inline void set_in(int in){ this->in = in;}
	inline void set_out(int out){ this->out = out;}
	inline void set_payment(int pay){ this->payment = pay;}
//	void set_nxt_front(Nodes * nxt);
//	void set_nxt_back(Nodes * nxt);
//	void remove_nxt_front();
//	void remove_nxt_back();

//	void remove_all_out();
	inline void plus_in(int add){this->in += add;}
	inline void plus_out(int add){this->out += add;}
//	inline string set_name(string name){ this->name = name;}	// Causou um bug lvl hard
	inline void set_name(const string& name){ this->name = name;}
	inline void set_cost(int cost){ this->cost = cost;}
	inline void set_visit(bool visit){ this->visit = visit;}
};
//*/
int main(){
	deque<int>::const_iterator it;
	No foo;
	No *a, *b;
	No c;
	a = new No;
	b = new No;
	a->oo = 99;
	b->oo = 1000;
	c.oo = 2000;
	foo.nxt.push_front(a);
	foo.nxt.push_back(b);
	foo.nxt.push_back(&c);
	for(deque<No*>::iterator x = foo.nxt.begin(); x != foo.nxt.end(); x++)
		cout << (*(*x)).oo << endl;

	a->oo *= 1000;
	b->oo *= -1;
	c.oo = 0;
	
	for(deque<No*>::iterator x = foo.nxt.begin(); x != foo.nxt.end(); x++){
		cout << (*(*x)).oo << endl;
		cout << (*x)->oo << endl;
	}
	foo.nxt.clear();

	foo.nxt.push_front(a);
	foo.nxt.push_back(b);
	foo.nxt.push_back(&c);	
	for(deque<No*>::iterator x = foo.nxt.begin(); x != foo.nxt.end(); x++){
		cout << (*(*x)).oo << endl;
		cout << (*x)->oo << endl;
	}



	return 0;
}