/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/
#include "nodes.hpp"
#include <iostream>
using namespace std;

// private




Nodes* Nodes :: insert_teacher2_debug(Nodes* teach){	// Retorna o ponteiro removido, ou o candidato caso ele nao seja inserido
														// ou NULL se eh o primeiro candidato
	if(this->teacher2 != NULL){
		if(this->teacher2->get_hab() != this->hab){	// Se o antigo nao eh o ideal, considera troca
			if(teach->get_hab() > this->teacher2->get_hab()){	// Se professor que se ofereceu tem + habilidades, aceite-o
				auto removed = teacher2;
				teacher2 = teach;
				cout << "(2) Retirou teacher2 == " << removed->get_key() << ". H == " << removed->get_hab() <<endl;
				cout << "(2) Inseriu teacher  == " << this->teacher2->get_key() << ". H == " << this->teacher2->get_hab() << endl;
				this->set_sat();
				return removed;
			}
			else{
				cout << "(2) Rejeitou " << teach->get_key() << endl;
				cout << "(2) Habilidade teacher2 : " << this->teacher2->get_hab() << endl;
				return teach;	// Professorr rejeitado
			}
		}
		else
			return teach;
	}
	else{	// Primeiro a se candidatar; portanto, eh aceito de inicio
		cout << "(2) Removido : ninguem\n";
		this->teacher2 = teach;
	}
	this->set_sat();
	return NULL;		// Colocou no teacher2 E eh o primeiro candidato
}
Nodes* Nodes :: insert_teacher2(Nodes* teach){	// Retorna o ponteiro removido, ou o candidato caso ele nao seja inserido
												// ou NULL se eh o primeiro candidato
	if(this->teacher2 != NULL){
		if(this->teacher2->get_hab() != this->hab){	// Se o antigo nao eh o ideal, considera troca
			if(teach->get_hab() > this->teacher2->get_hab()){	// Se professor que se ofereceu tem + habilidades, aceite-o
				auto removed = teacher2;
				teacher2 = teach;
				this->set_sat();
				return removed;
			}
			else
				return teach;	// Professorr rejeitado
		}
		else
			return teach;
	}
	else	// Primeiro a se candidatar; portanto, eh aceito de inicio
		this->teacher2 = teach;
	this->set_sat();
	return NULL;		// Colocou no teacher2 E eh o primeiro candidato
}

// public

bool Nodes :: set_sat(){
	if(this->teacher1 != NULL && this->teacher2 != NULL)
		this->sat = true;
	return this->sat;
}

bool Nodes :: set_sat2(){
	if(this->teacher1->get_hab() == this->hab)
		if(this->teacher2->get_hab() == this->hab)
			this->sat = true;
	return this->sat;
}


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

Nodes* Nodes :: insert_teacher_debug(Nodes* teach){	// Retorna o ponteiro removido, ou o candidato caso ele nao seja inserido
	cout << "\n\nCandidato: " << teach->get_key() << endl;
	cout << "Habilidades Candidato: " << teach->get_hab() << endl;
	cout << "Escola : " << this->get_key() << endl;
	cout << "Habilidades escola : " << this->get_hab() << endl;
	if(this->sat == true){cout << "Escola "<<this->get_key() << " saturada.\n";	return teach;}
	if(teach == NULL) throw NULL;				// ou NULL se eh o primeiro candidato
	
	if(this->teacher1 != NULL){		//   Tem candidato jah? Se nao, insere teach.
		if(this->teacher2 == NULL)	return insert_teacher2_debug(teach);	// t1 preenchido, tenta encaixar na segunda posicao
		if(this->teacher1->get_hab() != this->hab){	// Se o antigo nao eh o ideal, considera troca
			if(teach->get_hab() > this->teacher1->get_hab()){	// Se professor que se ofereceu tem + habilidades, aceite-o
				auto removed = teacher1;
				teacher1 = teach;
				cout << "(1) Retirou teacher1 == " << removed->get_key() << ". H == " << removed->get_hab() <<endl;
				cout << "(1) Inseriu teacher  == " << this->teacher1->get_key() << ". H == " << this->teacher1->get_hab() << endl;
				return removed;
			}
			else
				return insert_teacher2_debug(teach);	// Professorr  (1) rejeitado. Tentar inserir na segunda posicao.
		}
		else
			return insert_teacher2_debug(teach);
	}
	else{	// Primeiro a se candidatar; portanto, eh aceito de inicio
		cout << "(1) Removido : ninguem\n";
		this->teacher1 = teach;
	}
	return NULL;		// Colocou no teacher1 E eh o primeiro candidato
}

Nodes* Nodes :: insert_teacher(Nodes* teach){	// Retorna o ponteiro removido, ou o candidato caso ele nao seja inserido
	if(this->sat == true)	return teach;
	if(teach == NULL) throw NULL;				// ou NULL se eh o primeiro candidato
	
	if(this->teacher1 != NULL){		//   Tem candidato jah? Se nao, insere teach.
		if(this->teacher2 == NULL)	return insert_teacher2(teach);	// t1 preenchido, tenta encaixar na segunda posicao
		if(this->teacher1->get_hab() != this->hab){	// Se o antigo nao eh o ideal, considera troca
			if(teach->get_hab() > this->teacher1->get_hab()){	// Se professor que se ofereceu tem + habilidades, aceite-o
				auto removed = teacher1;
				teacher1 = teach;
				return removed;
			}
			else
				return insert_teacher2(teach);	// Professorr  (1) rejeitado. Tentar inserir na segunda posicao.
		}
		else
			return insert_teacher2(teach);
	}
	else	// Primeiro a se candidatar; portanto, eh aceito de inicio
		this->teacher1 = teach;
	return NULL;		// Colocou no teacher1 E eh o primeiro candidato
}
Nodes* Nodes :: insert_teacher_forced_debug(Nodes * trash){
	if(this->teacher1 != NULL){
		this->sat = true;
		if(this->teacher2 != NULL){
			auto ret = this->teacher2;
			this->teacher2 = trash;
			return ret;
		}
		else{
			this->teacher2 = trash;
		}
	}
	else
		this->teacher1 = trash;
	cout << "(1) Removido : ninguem\n";
	return NULL;
}
Nodes* Nodes :: insert_teacher_forced(Nodes * trash){
	if(this->teacher1 != NULL){
		this->sat = true;
		if(this->teacher2 != NULL){
			auto ret = this->teacher2;
			this->teacher2 = trash;
			return ret;
		}
		else
			this->teacher2 = trash;		
	}
	else
		this->teacher1 = trash;
	return NULL;
}

void Nodes :: remove_all_nxt(){
	if(this->already.empty() == false){
		this->nxt.clear();
		this->already.clear();
		this->qtd_nxt = 0;
	}
}



// Es colcar inline, undefined reference	/*inline*/