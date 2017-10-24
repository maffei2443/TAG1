/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/
#include "nodes.hpp"
#include <iostream>
using namespace std;

// private

// public

void Nodes :: set_nxt_front(Nodes * no){
	if(this->already.find(no->key) == this->already.end()){	// Se ainda nao foi inserido o No, insere
		this->already.insert(no->key);
		this->nxt.push_front(no);
	}
}

void Nodes :: set_nxt_back(Nodes * no){
	if(this->already.find(no->key) == this->already.end()){	// Se ainda nao foi inserido o No, insere
		this->already.insert(no->key);
		this->nxt.push_back(no);
	}
}

void Nodes :: remove_nxt_front(){
	if(this->already.empty() == true)	return;

	int remove = this->nxt.front()->get_key();
	this->already.erase(remove);
	this->nxt.pop_front();
}


void Nodes :: remove_nxt_back(){
	if(this->already.empty() == true)	return;

	int remove = this->nxt.back()->get_key();
	this->already.erase(remove);
	this->nxt.pop_back();
}

void Nodes :: remove_all_out(){
	if(this->already.empty() == false){
		this->nxt.clear();
		this->already.clear();
		this->out = this->qtd_nxt = 0;
	}
}

void Nodes :: mostra_no(){
	cout << " key		  : " << this->key << endl;
//	cout << " Matricula	  : " << this->matricula << endl;
//	cout << " td_nxt 	  : " << this->qtd_nxt << endl;
	cout << " In 		  : " << this->in << endl;
	cout << " Out 		  : " << this->out << endl;
	cout << " Name:		  : " << this->name << endl;
	cout << " Cost:		  : " << this->cost << endl;
//	cout << " visit 	  : " << this->visit << endl;
	cout  << "\n\n";
}

void Nodes :: mostra_lista(){
	this->mostra_no();
	for(deque<Nodes*>::iterator x = this->nxt.begin(); x != this->nxt.end(); x++)	
		(*x)->mostra_no();
}

void Nodes :: mostra_lista_reversa(){
	for(deque<Nodes*>::iterator x = this->nxt.begin(); x != this->nxt.end(); x++)
		(*x)->mostra_no();
	this->mostra_no();
}

// Es colcar inline, undefined reference	/*inline*/