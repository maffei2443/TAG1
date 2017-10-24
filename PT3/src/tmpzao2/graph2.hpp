    #ifndef _GRAPH_HPP_
    #define _GRAPH_HPP_
    #include "nodes.hpp"
    #include <deque>
    using namespace std;
    class Graph{

	private:

		deque <Nodes*> node;

	public:

		Nodes* get_node(int key){return node.at(key);}

		deque<Nodes*> :: iterator iterador(){return node.begin();}

		deque<Nodes*> :: iterator end(){return node.end();}

		void insert(Nodes* no){node.push_back(no);}	
	};
    #endif