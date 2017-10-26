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
		this->qtd_nxt++;
	}
}

void Nodes :: set_nxt_back(Nodes * no){
	if(this->already.find(no->key) == this->already.end()){	// Se ainda nao foi inserido o No, insere
		this->already.insert(no->key);
		this->nxt.push_back(no);
		this->qtd_nxt++;
	}
}

void Nodes :: remove_nxt_front(){
	if(this->already.empty() == true)	return;

	int remove = this->nxt.front()->get_key();
	this->already.erase(remove);
	this->nxt.pop_front();
	this->qtd_nxt--;
}


void Nodes :: remove_nxt_back(){
	if(this->already.empty() == true)	return;

	int remove = this->nxt.back()->get_key();
	this->already.erase(remove);
	this->nxt.pop_back();
	this->qtd_nxt--;
}

void Nodes :: remove_all_nxt(){
	if(this->already.empty() == false){
		this->nxt.clear();
		this->already.clear();
		this->qtd_nxt = 0;
	}
}



// Es colcar inline, undefined reference	/*inline*/