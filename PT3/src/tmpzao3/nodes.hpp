/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/



#ifndef _NODES_HPP_
#define _NODES_HPP_
#include <set>
#include <string>
#include <iostream>		
#include <deque>
using namespace std;
class Nodes;
/*
typedef struct {
	Nodes * no;
	int w;			
}aresta_no;
*/
class Nodes{
private:
	int key;
	deque <Nodes*> nxt;		
public:

	Nodes() :key(-1){}
	Nodes(int keyy) : key(keyy){}

	inline int get_key(){return key;}

	deque<Nodes*>::iterator get_nxt(){return nxt.begin();}	
	deque<Nodes*>::iterator get_end(){return nxt.end();}	
	void set_nxt_front(Nodes * no){this->nxt.push_front(no);}
	void set_nxt_back(Nodes * no){this->nxt.push_back(no);}
	

};

#endif