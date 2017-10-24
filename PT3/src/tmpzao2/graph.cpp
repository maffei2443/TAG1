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
// public
Graph :: Graph(){
	node.resize(1);
}

Graph :: ~Graph(){
	this->reset();
}


void Graph :: reset(){

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

