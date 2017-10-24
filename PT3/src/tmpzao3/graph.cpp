#include "nodes.cpp"
#include <deque>
using namespace  std;
class Graph{
private:
	deque <Nodes*> node;

public:
	inline Nodes* get_node(int key){return node.at(key);}
	Graph(){node.resize(1);}
	deque<Nodes*> :: iterator iterador(){return node.begin();}
	deque<Nodes*> :: iterator* iterador2(){return &node.begin();}
	deque<Nodes*> :: iterator end(){return node.end();}
	void insert(Nodes* no){node.push_back(no);}
};