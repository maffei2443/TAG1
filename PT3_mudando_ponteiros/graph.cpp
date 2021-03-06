/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/
#include "nodes.hpp"
#include "graph.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
/// class Graph

// private

void Graph :: mostra_set(set <int> to_show){
    set<int> :: iterator iter;
    for(iter = to_show.begin(); iter != to_show.end(); iter++)
        cout << (*iter) << " ";
    cout << '\n';
}

void inline Graph :: exclude_list(int index){
	this->node[index]->remove_all_out();
	delete(this->node[index]);
	this->node[index] = NULL;
}


// public
Graph :: Graph() : edge(0), verts(0){node.resize(1);///*/
}

Graph :: ~Graph(){
	this->reset();
}


void Graph :: reset(){
	for(int i=1; i <= this->verts; i++){
		exclude_list(i);
	}
	this->node.resize(0);
	this->verts = 0;	this->edge=0;
}

void Graph :: insert(Nodes * novo){
	node.push_back(novo);
	this->verts = this->verts + 1;	//Novo vertice
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
vector<int> Graph ::  list(int vertice){
	vector<int> list;
//	for(deque<Nodes*>::iterator it = node[vertice-1]->get_nxt();pivo != NULL){
//		list.push_back(pivo->get_key());
//		++pivo;
//	}
	return list;
}

void Graph :: show_verts(){
	for(int i=1; i <= this->verts;i++){
		cout << "****** i == " << i << " ******" << endl; 
		this->node[i]->mostra_no();		
	}
}

void Graph :: show(){
	cout << "Mostrando grafo: " << endl;
	for(int i=1; i <= this->verts;i++){
		cout << "****** i == " << i << " ******" << endl; 
		this->node[i]->mostra_lista();
	}
}

void Graph :: show_nodes(){
	cout << "Mostrando grafo: " << endl;
	for(int i=1; i <= this->verts;i++){
		cout << "****** i == " << i << " ******" << endl; 
		this->node[i]->mostra_no();
	}
}

/*static*/

/*
Graph :: Graph(int){
	int id, code, rec_credits, hardness, pre_req;	//id: posicao no vetor (this->key); code = codigo da disciplina no MW (this->matricula)
	string name;
	ifstream arq("fluxo_cic.txt");
 	
	int id_max;		arq >> id_max;
	// Debug
	getline(arq, name);

	getline(arq, name);

	this->verts = id_max;
	this->node.resize(id_max + 1);
	

	int prev[id_max+1] {};	// fila para usar pra guardar pre-requisitos
	int i, k;
	int acumulator = 0;		// Creditos necessario de OBRIGATORIAS
	do{
		set <int> redundancy;
		i = k = 0;
		arq >> id >> code >> rec_credits >> hardness >> name;
		if(id > id_max || id < 1)		return;	// Arquivo zuado :/ .

		int cost = rec_credits * hardness;
		node[id] = new Nodes(code);	this->node[id]->set_name(name);	this->node[id]->set_cost(cost);
		node[id]->set_payment(rec_credits);
		acumulator += rec_credits;
		// Vai pegar os pre-requisitos
		do{
			arq >> code;
			if(code != 0 && code != -1){
				prev[i] = code;
				if(redundancy.count(code) == 0){	// Se nao eh redundante adicionar esse pre-req, add
					redundancy.insert(code);
// zoado			this->node[code]->plus_out(1);	// +1 mateira que libera
					this->node[id]->plus_in(1);		// +1 pre-requisito
					i++;
				}
			}
			// -1 eh separador de requisitos
		}while(code != 0);
		
		for(int j=0; j < i; j++){
			this->node[prev[j]]->insert_qtd_nxt_pro(new Nodes(this->node[id], this->node[id]->get_cost()));		
			this->node[prev[j]]->set_out(this->node[prev[j]]->get_qtd_nxt());
		}

		switch (id){case 5: case 9: case 14:
					case 19: case 24: case 29:
					case 32: case 34:	getline(arq,name);		// Quebra de linha entre os semestres
		}
				
	}while(id != id_max);
	this->sum_pay = acumulator;
	arq.close();
}
*/
