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

void Nodes :: insere_pre_calculado(Nodes* proximo){	// Com direito tratamento caso ono inserido a seja um vizinho!!!
	if(this == NULL) return;

	Nodes * aux = this;
	while(aux->vizinho != NULL && 	aux->chave != proximo->chave && proximo->chave > aux->vizinho->chave)
		// Ainda tem vizinho    E   ainda nao foi inserido 	  	  E  o atual eh maior 
		aux = aux->vizinho;
	if(aux->chave == proximo->chave) cout << "Ciclo!\n";	// Implementar a opcao de criar laco
	else if(aux->vizinho == NULL){						// Acabaram os sucesores menores
			aux->vizinho = new Nodes(proximo);//*/
	}
	else if(proximo->chave < aux->vizinho->chave){	//Sempre vai ocorrer, evidentemente. Inserir ordenadamente entao
		Nodes *  pivo = aux->vizinho;
		aux->vizinho = new Nodes(proximo);
		aux->vizinho->vizinho = pivo;
		pivo = NULL;
	}
	aux=NULL;
}

// public

void Nodes :: mostra_no(){
	cout << "Chave		  : " << this->chave << endl;
	cout << "Matricula	  : " << this->matricula << endl;
//	cout << "Nome 		 : " << this->nome << endl;
	cout << "Amigos (grau): " << this->amigos << endl;
//	cout << "Custo:		 : " << this->custo << endl;
//	cout << "Visitado 	 : " << this->visit << endl;
	printf("\n\n");
}

void Nodes :: mostra_lista(){
	this->mostra_no();
	printf("\n\n");
	if(this->vizinho != NULL)	this->vizinho->mostra_lista();
}

void Nodes :: mostra_lista_rersa(){
	if(this->vizinho != NULL)
		this->vizinho->mostra_lista_rersa();
	this->mostra_no();
}

// Es colcar inline, undefined reference	/*inline*/
void Nodes :: insert_nxt_pro(Nodes* proximo){	// Com direito tratamento caso ono inserido a seja um vizinho!!!
	insert_nxt_pro(proximo, 1);	
}
void Nodes :: insert_nxt_pro(Nodes* proximo, int custo){	// Com direito tratamento caso ono inserido a seja um vizinho!!!
	if(this == NULL) return;

	Nodes * aux = this;
	while(aux->vizinho != NULL && 	aux->chave != proximo->chave && proximo->chave > aux->vizinho->chave)
		// Ainda tem vizinho    E   ainda nao foi inserido 	  	  E  o atual eh maior 
		aux = aux->vizinho;
	if(aux->chave == proximo->chave)cout<<"Ciclos aida nao implementados\n";	// Implementar a opcao de criar laco
	else if(aux->vizinho == NULL){						// Acabaram os sucesores menores
			aux->vizinho = new Nodes(proximo, custo);//*/
			this->amigos++;
	}
	else if(proximo->chave < aux->vizinho->chave){	//Sempre vai ocorrer, evidentemente. Inserir ordenadamente entao
		Nodes *  pivo = aux->vizinho;
		aux->vizinho = new Nodes(proximo, custo);
		aux->vizinho->vizinho = pivo;
		this->amigos++;
		pivo = NULL;
	}
	aux=NULL;
}

void Nodes :: insert_nxt_pro_debug(Nodes* proximo){	// Com direito tratamento caso ono inserido a seja um vizinho!!!
	if(this == NULL) return;

	Nodes * aux = this;
	while(aux->vizinho != NULL && 	aux->chave != proximo->chave && proximo->chave > aux->vizinho->chave)
		// Ainda tem vizinho    E   ainda nao foi inserido 	  	  E  o atual eh maior 
		aux = aux->vizinho;
	cout << "Atual: " << this->chave << endl;
	cout << "Proximo->chave == " << proximo->chave << endl;
	if(aux->chave == proximo->chave)
		cout << "Vizinho ja inserido priamente \n";	// Implementar a opcao de criar laco
	else if(aux->vizinho == NULL){						// Acabaram os sucesores menores
			aux->vizinho = new Nodes(proximo);//*/
			this->amigos++;
	}
	else if(proximo->chave < aux->vizinho->chave){	//Sempre vai ocorrer, evidentemente. Inserir ordenadamente entao
		Nodes *  pivo = aux->vizinho;
		aux->vizinho = new Nodes(proximo);
		aux->vizinho->vizinho = pivo;
		this->amigos++;
		pivo = NULL;
	}
	cout << "Mostrando Lista (Nodes :: insert_nxt_pro)" << endl;
	this->mostra_lista();
	aux=NULL;
}