#include "nodes.hpp"
#include "graph.hpp"
#include <queue>
#include <set>

using namespace std;

bool bipartido1(Graph * G, vector<bool> &visit, set<int> &A, set<int> &B, queue<int> &fila){
	int before, now;
	set<int> *x, *y;
	x = &A;
	y = &B;
	int caso;
	while(fila.empty() == false){
		int key = fila.front();
		fila.pop();
		visit[key] = true;
		if(A.count(key) == 0)
			caso = 2;
		else
			caso = 1;

		auto init = G->get_node(key)->get_nxt();
		auto end = G->get_node(key)->get_end();
		if(caso == 2){	// vizinho deve pertences ao conjunto A
			B.insert(key);
			for(; init != end; init++){
				cout << "pre1" << endl;
				if( B.count( (*init)->get_key()) != 0)	return false;	//Se vizinho estah no mesmo conjunto dele, nao eh bipartido
				if( A.count( (*init)->get_key()) == 0){
					A.insert( (*init)->get_key() );
					cout << "inseriu " << (*init)->get_key()  << " em A\n";
				}
				if(visit[(*init)->get_key()] == false)	fila.push((*init)->get_key());
			}
			cout << "caso == 1?" << endl;
			cout << caso << endl;
		}
		else if(caso == 1){	// Vizinhos NAO DEVEM ESTAR em A
			A.insert(key);
			for(; init != end; init++){
				cout << "pre 2" << endl;
				if( A.count( (*init)->get_key()) != 0)	return false;	//Se vizinho estah no mesmo conjunto dele, nao eh bipartido
				if( B.count( (*init)->get_key()) == 0){
					B.insert((*init)->get_key());	// Insere  no conjunto oposto
					cout << "inseriu " << (*init)->get_key()  << " em B\n";
				}
				if(visit[(*init)->get_key()] == false)	fila.push((*init)->get_key());
			}
			cout << "caso == 2?" << endl;
			cout << caso << endl;
		}
		else	cout << "???" << endl;

	}
	cout  << "Fim\n";
	return true;
}

bool bipartido(Graph * G, vector<bool> &queued, set<int> &A, set<int> &B, queue<int> &fila){
	int before, now;
	set<int> *x, *y;
	x = &A;	y = &B;
	before = 1;	// Antes de 1, '0' estah no conjunto B
	int key = fila.front();
	A.insert(key);
	queued[key] = true;
	while(fila.empty() == false){	// No primeiro caso, before == now.
		key = fila.front();		fila.pop();
		if(A.count(key) == 0)			now = 0;
		else			now = 1;
		
		if(before != now)
			swap(x,y);
		
		before = now;		
		auto init = G->get_node(key)->get_nxt();
		auto end = G->get_node(key)->get_end();
												//No primeiro caso, before == now.
		x->insert(key);
		for(; init != end; init++){
			if( x->count( (*init)->get_key()) != 0)	return false;	//Se vizinho estah no mesmo conjunto dele, nao eh bipartido

			y->insert( (*init)->get_key() );		// Inseriu no conjunto oposto
		
			if(queued[(*init)->get_key()] == false){
				fila.push((*init)->get_key());
				queued[ (*init)->get_key() ] = true;
			}
		}
	}
	cout  << "Bipartido\n";
	return true;
}

bool bipartido(Graph * G){
	vector<bool> visit(G->get_verts()+1, false);
	set<int> A, B;	// Conjuntos que deverao ser disjuntos
	queue<int> fila;
	fila.push(1);
	return bipartido(G, visit, A, B, fila);
}

inline void n_lados(Graph * G, int n){
	n++;
	for(int i = 1; i < n; i++)
		G->insert(new Nodes(i));
	for(int i = 1; i < n-1; i++){
		G->get_node(i)->set_nxt_back(G->get_node(i+1));
		G->get_node(i+1)->set_nxt_back(G->get_node(i));
	}
	G->get_node(1)->set_nxt_back(G->get_node(n-1));
	G->get_node(n-1)->set_nxt_back(G->get_node(1));

}

int main(){
	Graph * G;
	G = new Graph;
	n_lados(G, 3);
/*	for(int i = 1; i < 4; i++)
		G->insert(new Nodes(i));
	for(int i = 1; i < 3; i++){
		G->get_node(i)->set_nxt_back(G->get_node(i+1));
		G->get_node(i+1)->set_nxt_back(G->get_node(i));
	}
	G->get_node(1)->set_nxt_back(G->get_node(3));
	G->get_node(3)->set_nxt_back(G->get_node(1));
*/
	cout << "Triangulo. Esperado :: 0\n";
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>> G Bipartido :: " << bipartido(G) << endl;
	Graph * G2;
	G2 = new Graph;
	
	for(int i = 1; i < 5; i++)
		G2->insert(new Nodes(i));
	for(int i = 1; i < 4; i++){
		G2->get_node(i)->set_nxt_back(G2->get_node(i+1));
		G2->get_node(i+1)->set_nxt_back(G2->get_node(i));
	}
	G2->get_node(1)->set_nxt_back(G2->get_node(4));
	G2->get_node(4)->set_nxt_back(G2->get_node(1));

	cout << "Retangulo. Esperado :: 1\n";
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>> G2 Bipartido :: " << bipartido(G2) << endl;

	Graph * G3;
	G3 = new Graph;

	G3->insert(new Nodes(1));
	G3->insert(new Nodes(2));
	G3->insert(new Nodes(3));
	G3->insert(new Nodes(4));

	G3->get_node(1)->set_nxt_back(G3->get_node(2));
	G3->get_node(2)->set_nxt_back(G3->get_node(1));

	G3->get_node(1)->set_nxt_back(G3->get_node(4));
	G3->get_node(4)->set_nxt_back(G3->get_node(1));

	G3->get_node(1)->set_nxt_back(G3->get_node(3));
	G3->get_node(3)->set_nxt_back(G3->get_node(1));

	G3->get_node(2)->set_nxt_back(G3->get_node(3));
	G3->get_node(3)->set_nxt_back(G3->get_node(2));

	G3->get_node(3)->set_nxt_back(G3->get_node(4));
	G3->get_node(4)->set_nxt_back(G3->get_node(3));

	cout << "Retangulo com 1 diagonal. Esperado :: 0\n";
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>> G3 Bipartido :: " << bipartido(G3) << endl;

	Graph * G4;
	G4 = new Graph;

	for(int i = 1; i < 7; i++)
		G4->insert(new Nodes(i));
	for(int i = 1; i < 6; i++){
		G4->get_node(i)->set_nxt_back(G4->get_node(i+1));
		G4->get_node(i+1)->set_nxt_back(G4->get_node(i));
	}
	G4->get_node(1)->set_nxt_back(G4->get_node(6));
	G4->get_node(6)->set_nxt_back(G4->get_node(1));

	cout << "Hexagono. Esperado :: 1\n";
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>> G4 Bipartido :: " << bipartido(G4) << endl;

	Graph * G5;
	G5 = new Graph;

	for(int i = 1; i < 8; i++)
		G5->insert(new Nodes(i));
	for(int i = 1; i < 7; i++){
		G5->get_node(i)->set_nxt_back(G5->get_node(i+1));
		G5->get_node(i+1)->set_nxt_back(G5->get_node(i));
	}
	G5->get_node(1)->set_nxt_back(G5->get_node(7));
	G5->get_node(7)->set_nxt_back(G5->get_node(1));

	cout << "Heptagono. Esperado :: 0\n";
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>> G5 Bipartido :: " << bipartido(G5) << endl;


}