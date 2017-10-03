/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/
#include "nodes.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

// private

void Nodes :: del_nxt(){
	Nodes * empty = this->nxt;
	if(empty != NULL){
		if(empty->get_nxt() != NULL)
			empty->get_nxt()->del_nxt();
	empty = NULL;
	}
	else
		delete(this->nxt);
}

// public

void Nodes :: insere_pre_calculado(Nodes* proximo){	// Com direito tratamento caso ono inserido a seja um nxt!!!
	if(this == NULL) return;

	Nodes * aux = this;
	while(aux->get_nxt() != NULL && 	aux->get_key() != proximo->get_key() && proximo->get_key() > aux->get_nxt()->get_key())
		// Ainda tem nxt    E   ainda nao foi inserido 	  	  E  o atual eh maior 
		aux = aux->get_nxt();
	if(aux->get_key() == proximo->get_key()) cout << "Ciclo!\n";	// Implementar a opcao de criar laco
	else if(aux->get_nxt() == NULL){						// Acabaram os sucesores menores
			aux->set_nxt(new Nodes(proximo));//*/
	}
	else if(proximo->get_key() < aux->get_nxt()->get_key()){	//Sempre vai ocorrer, evidentemente. Inserir ordenadamente entao
		Nodes *  pivo = aux->get_nxt();
		aux->set_nxt(new Nodes(proximo));
		aux->get_nxt()->set_nxt(pivo);
		pivo = NULL;
	}
	aux=NULL;
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
	printf("\n\n");
}

void Nodes :: mostra_lista(){
	this->mostra_no();
	printf("\n\n");
	if(this->nxt != NULL)	this->nxt->mostra_lista();
}

void Nodes :: mostra_lista_rersa(){
	if(this->nxt != NULL)
		this->nxt->mostra_lista_rersa();
	this->mostra_no();
}

// Es colcar inline, undefined reference	/*inline*/
void Nodes :: insert_qtd_nxt_pro(Nodes* proximo){	// Com direito tratamento caso ono inserido a seja um nxt!!!
	insert_qtd_nxt_pro(proximo, 1);	
}
void Nodes :: insert_qtd_nxt_pro(Nodes* proximo, int cost){	// Com direito tratamento caso ono inserido a seja um nxt!!!
	if(this == NULL) return;

	Nodes * aux = this;
	while(aux->get_nxt() != NULL && 	aux->get_key() != proximo->get_key() && proximo->get_key() > aux->get_nxt()->get_key())
		// Ainda tem nxt    E   ainda nao foi inserido 	  	  E  o atual eh maior 
		aux = aux->get_nxt();
	if(aux->get_key() == proximo->get_key())cout<<"Ciclos aida nao implementados\n";	// Implementar a opcao de criar laco
	else if(aux->get_nxt() == NULL){						// Acabaram os sucesores menores
			aux->set_nxt(new Nodes(proximo, cost));//*/
			this->qtd_nxt++;
	}
	else if(proximo->get_key() < aux->get_nxt()->get_key()){	//Sempre vai ocorrer, evidentemente. Inserir ordenadamente entao
		Nodes *  pivo = aux->get_nxt();
		aux->set_nxt(new Nodes(proximo, cost));
		aux->get_nxt()->set_nxt(pivo);
		this->qtd_nxt++;
		pivo = NULL;
	}
	aux=NULL;
}

void Nodes :: insert_qtd_nxt_pro_debug(Nodes* proximo){	// Com direito tratamento caso ono inserido a seja um nxt!!!
	if(this == NULL) return;

	Nodes * aux = this;
	while(aux->get_nxt() != NULL && aux->get_key() != proximo->get_key() && proximo->get_key() > aux->get_nxt()->get_key())
		// Ainda tem nxt    E   ainda nao foi inserido 	  	  E  o atual eh maior 
		aux = aux->get_nxt();
	cout << "Atual: " << this->key << endl;
	cout << "Proximo->get_key() == " << proximo->get_key() << endl;
	if(aux->get_key() == proximo->get_key())
		cout << "Vizinho ja inserido previamente \n";	// Implementar a opcao de criar laco
	else if(aux->get_nxt() == NULL){						// Acabaram os sucesores menores
			aux->set_nxt(new Nodes(proximo));//*/
			this->qtd_nxt++;
	}
	else if(proximo->get_key() < aux->get_nxt()->get_key()){	//Sempre vai ocorrer, evidentemente. Inserir ordenadamente entao
		Nodes *  pivo = aux->get_nxt();
		aux->set_nxt(new Nodes(proximo));
		aux->get_nxt()->set_nxt(pivo);
		this->qtd_nxt++;
		pivo = NULL;
	}
	cout << "Mostrando Lista (Nodes :: insert_qtd_nxt_pro)" << endl;
	this->mostra_lista();
	aux=NULL;
}