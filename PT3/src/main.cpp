#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
using namespace std;

Graph :: Graph(int){
	this->verts = 0;
	this->edge = 0;
	this->sum_pay = 0;
	FILE * fp = fopen("input.txt", "r+");
	
	int num, hab;
	int prof, scho;
	char tmp;
	string oo;
	fscanf(fp, "%d %d", &prof, &scho);
	fprintf(stdout, "%d %d\n", prof, scho);
	this->node.resize(1 + prof + scho);

	vector< vector<int> > tmpp(prof + scho + 1);

	for(int i = 0; i < prof + scho + 1; i++)		tmpp[i].resize(5);
	

	cout << "Criando nohs dos professores\n";
	// Criando nohs dos professores
	for(int i = 1; i < prof+1; i++){
		fscanf(fp, "%d %d %d %d %d %d %d", &num, &hab, &tmpp[i][0], &tmpp[i][1], &tmpp[i][2], &tmpp[i][3], &tmpp[i][4]);
		this->node[i] = new Nodes(num, hab);
		for(int j = 0; j < 5; j++)	tmpp[i][j] += prof;
	}

	int scho_hab[50][2];
	// Criando nohs das escolas
	cout << "Criando nohs das escolas\n";
	for(int i = 1; i < scho+1; i++){
		fscanf(fp, "%d %d", &scho_hab[i][0], &scho_hab[i][1]);
		this->node[i+prof] = new Nodes(scho_hab[i][0], scho_hab[i][1], ' ');
	}
	
	cout << "Mostrando professores e habilidades possuidas\n";
	for(int i = 1; i < prof+1; i++){
		for(int j = 0; j < 5; j++)
			this->node[i]->set_nxt_back( this->node[ tmpp[i][j] ] );

		printf("Professor: 		%d | ", this->node[i]->get_key());
		printf("Habilidades: 	%d\n",  this->node[i]->get_hab());
		printf("Lista de preferencias : \n");
		for(auto x = this->node[i]->get_nxt(); x != this->node[i]->get_end(); x++)
			cout << (*x)->get_key() << " ";
		cout << endl;
	}

	
	cout << "Mostrando escolas e habilidades exigidas\n";
	for(int i = 1; i < scho+1; i++){
		printf("Escola : 		%d | ",  this->node[i+prof]->get_key());
		printf("Habilidades:	%d\n" , this->node[i+prof]->get_hab());
	}
/**/for(int i = 1; i < prof+1; i++);
	
	
	fclose(fp); 
}


int main(){

	Graph G(1);

	cout << "Terminou a main\n";
	return 0;
}