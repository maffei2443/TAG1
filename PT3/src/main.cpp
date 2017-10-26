#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
using namespace std;

Graph :: Graph(int){
	
	this->edge = 0;
	this->sum_pay = 0;
	FILE * fp = fopen("input.txt", "r+");
	
	int num, hab;
	int prof, scho;
	char tmp;
	string oo;
	fscanf(fp, "%d %d", &prof, &scho);
	fprintf(stdout, "%d %d\n", prof, scho);
	this->verts = prof + scho;
	this->edge = prof * 5;
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
		printf("Elementos na lista: %d\n", this->node[i]->get_qtd_nxt());
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

Nodes* Nodes :: insert_teacher2(Nodes* teach){	// Retorna o ponteiro removido, ou o candidato caso ele nao seja inserido
												// ou NULL se eh o primeiro candidato
	if(this->teacher2 != NULL){
		if(this->teacher2->get_hab() != this->hab){	// Se o antigo nao eh o ideal, considera troca
			if(teach->get_hab() > this->teacher2->get_hab()){	// Se professor que se ofereceu tem + habilidades, aceite-o
				auto removed = teacher2;
				teacher2 = teach;
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
	this->sat = true;	
	return NULL;		// Colocou no teacher2 E eh o primeiro candidato
}

Nodes* Nodes :: insert_teacher(Nodes* teach){	// Retorna o ponteiro removido, ou o candidato caso ele nao seja inserido
	if(teach == NULL) throw NULL;				// ou NULL se eh o primeiro candidato
	
	if(this->teacher1 != NULL){		//   Tem candidato jah? Se nao, insere teach.
		if(this->teacher1->get_hab() != this->hab){	// Se o antigo nao eh o ideal, considera troca
			if(teach->get_hab() > this->teacher1->get_hab()){	// Se professor que se ofereceu tem + habilidades, aceite-o
				auto removed = teacher1;
				teacher1 = teach;
				return removed;
			}
			else
				return teach;	// Professorr rejeitado
		}
		else
			return insert_teacher2(teach);
	}
	else	// Primeiro a se candidatar; portanto, eh aceito de inicio
		this->teacher1 = teach;
	return NULL;		// Colocou no teacher1 E eh o primeiro candidato
}

void emparelhamento_top(Graph * G, const int& PROF, const int& SCHO){

	set<int> nsat_prof, nsat_scho;	// Conjunto dos professores/escolas nao saturados
	
	set<int> sat_prof, sat_scho;
	set<int> over1, over2, over3;	// Professores (com 1, 2 ou 3 habilidades) que foram rejeitados
	set<int> rejected;				// Professores rejeitados
	
	// Iterar APENAS sobre os professores
	int i = 1;
	for(auto x = G->iterador(); (*x)->get_key() <= PROF; x++ ){
		nsat_prof.insert(G->get_node((*x)->get_key())->get_key());//		cout << "Professor inserido: " << (*x)->get_key() << endl;
		if(i <= SCHO)
			nsat_scho.insert( (*x)->get_key() + PROF );//	cout << "Escola inserida: " << (*x)->get_key() + PROF << endl;
		i++;
	}
	cout << "Inseriu de boas\n";
	// Obs: se um professor for dispensado, checar se ele tem
	// mais alguma rpeferencia. Se nao, foi REJEITADO.
	// over1, over2 e over3 sao apenas subconjuntos de rejected
		// Iterar APENAS sobre os professores nsat, os quais tambem nao foram rejeitados
		for(auto x = nsat_prof.begin(); x != nsat_prof.end(); x = nsat_prof.begin()){	// x eh iterador de SET
			Nodes* prof = G->get_node( (*x) );
			cout << prof->get_key() << endl;
			
			Nodes* school = (* (prof->get_nxt()) );					// Ponteiro para ESCOLA.

			if( school ==  NULL)	throw 666;// NAO DEVE OCORRER.				

			prof->remove_nxt_front();	// Jah esgotou uma possibilidade.

			Nodes* aux = school->insert_teacher( prof );

			if(aux != NULL){	// Se at nao foi o primeiro candidato, tratar casos
				if(aux  !=  prof){	// Professor antigo deixou de ser saturado! PROFESSOR NOVO FOI ACEITO.
					sat_prof.erase(aux->get_key())	;	// Antigo contratado NAO ESTAH MAIS SATURADO. Portando, remover de sat_prof .
					sat_prof.insert(prof->get_key())	;	// Atual professor virou saturado.
					
					if(aux->get_nxt() == aux->get_end())			/// Verificar se o professor retirado ainda tem preferencias; se nao, eh rejeitado
						rejected.insert(aux->get_key())	;
					else											/// Se ainda tem preferencias, eh nsat
						nsat_prof.insert(aux->get_key());			// Jah foi retirado dos visitados; inserir apenas nos nao visitados "com esperanca"						
				}
				else;	// PROF FOI RECUSADO
				
			}
			else{	// Saturou o professor, pois ele FOI O PRIMEIRO CANDIDATO.
				sat_prof.insert( prof->get_key() );
				nsat_prof.erase( prof->get_key() );
				if( school->get_sat() ==  true ){	// Se escola foi saturada, colocar no conjunto de saturadas
					sat_scho.insert( school->get_key() );
					nsat_scho.erase( school->get_key() );
				}
			}
			// Se mudou o conjunto
			if(prof->get_qtd_nxt() == 0){		// Verifica se ainda tem opcoes; se nao tem, eh rejeitado.
				rejected.insert(prof->get_key());	
				nsat_prof.erase(prof->get_key());		// Como ele foi rejeitado, logo nao tem opcoes E portanto nao pode estar em nsat_prof.
			}	
			if(rejected.count(prof->get_key()) != 0)
				cout << "Rejeitdao do momento: " << prof->get_key() << endl;
		}
}



int main(){

	Graph * G = new Graph(1);


	Nodes foo;
	emparelhamento_top(G, 100, 50);

	cout << "Terminou a main\n";
	return 0;
}