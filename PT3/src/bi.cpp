#include "nodes.hpp"
#include "graph.hpp"
#include <queue>
#include <set>

using namespace std;

bool bipartido(Graph * G, vector<int> &visit, set<int> &A, set<int> &B, queue<int> &fila){
	int caso = 1;
	while(fila.empty() == false){
		int key = fila.front();
		fila.pop();
		
		if(caso == 2){	// vizinho deve pertences ao conjunto A
			for(auto x = G->get_node(key)->get_nxt(); x != G->get_node(key)->get_end(); x++){
				if( B.count( key) != 0)	return false;	//Se vizinho estah no mesmo conjunto dele, nao eh bipartido
				if( visit[ key ] == false)	{fila.push(key); visit[key] = true;}
				if(A.count(key) == 0)	A.insert(key);
				caso = 1;
				cout << "caso == 1?" << endl;
				cout << caso << endl;
			}
		}
		else{	// Vizinhos NAO DEVEM ESTAR em A
			for(auto x = G->get_node(key)->get_nxt(); x != G->get_node(key)->get_end(); x++){
				if( A.count( key) != 0)	return false;	//Se vizinho estah no mesmo conjunto dele, nao eh bipartido
				if( visit[ key ] == false){	fila.push(key); visit[key] = true;}
				if(B.count(key) == 0)	B.insert(key);
				caso = 2;
				cout << "caso == 2?" << endl;
				cout << caso << endl;
			}
		}
			
	}
	cout  << "Fim\n";
	return true;
}

bool bipartido(Graph * G){
	vector<int> visit(G->get_verts(), false);
	set<int> A, B;	// Conjuntos que deverao ser disjuntos
	queue<int> fila;
	fila.push(1);
	return bipartido(G, visit, A, B, fila);
}

int main(){
	Graph * G;
	G = new Graph;

	G->insert(new Nodes(1));
	G->insert(new Nodes(2));
	G->insert(new Nodes(3));

	G->get_node(1)->set_nxt_back(G->get_node(2));
	G->get_node(2)->set_nxt_back(G->get_node(1));

	G->get_node(1)->set_nxt_back(G->get_node(3));
	G->get_node(3)->set_nxt_back(G->get_node(1));

	G->get_node(2)->set_nxt_back(G->get_node(3));
	G->get_node(3)->set_nxt_back(G->get_node(2));

	cout << "Bipartido :: " << bipartido(G) << endl;
	if( bipartido(G)== true)
		cout << "erro: nao devia ser bipartido\n";

	Graph * G2;
	G2 = new Graph;

	G2->insert(new Nodes(1));
	G2->insert(new Nodes(2));
	G2->insert(new Nodes(3));
	G2->insert(new Nodes(4));

	G2->get_node(1)->set_nxt_back(G2->get_node(2));
	G2->get_node(2)->set_nxt_back(G2->get_node(1));

	G2->get_node(1)->set_nxt_back(G2->get_node(4));
	G2->get_node(4)->set_nxt_back(G2->get_node(1));

	G2->get_node(2)->set_nxt_back(G2->get_node(3));
	G2->get_node(3)->set_nxt_back(G2->get_node(2));

	G2->get_node(3)->set_nxt_back(G2->get_node(4));
	G2->get_node(4)->set_nxt_back(G2->get_node(3));

	cout << "Bipartido :: " << bipartido(G2) << endl;
	if( bipartido(G2)== false)
		cout << "erro: devia ser bipartido\n";

	bool foo = true;
	cout << foo << endl;
	foo = false;
	cout << foo << endl;

}