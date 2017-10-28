#include "graph.hpp"
#include <iostream>
using namespace std;




void emparelhamento(Graph * G, const int& PROF, const int& SCHO){

	set<int> nsat_prof, nsat_scho;	// Conjunto dos professores/escolas nao saturados
	
	set<int> sat_prof, sat_scho;
	set<int> rejected;				// Professores rejeitados
	
	// Iterar APENAS sobre os professores
	int i = 1;
	for(auto x = G->iterador(); (*x)->get_key() <= PROF; x++ ){
		nsat_prof.insert(G->get_node((*x)->get_key())->get_key());//		cout << "Professor inserido: " << (*x)->get_key() << endl;
		if(i <= SCHO){
			nsat_scho.insert( (*x)->get_key() + PROF );//	cout << "Escola inserida: " << (*x)->get_key() + PROF << endl;
		}
		i++;
	}
	// Obs: se um professor for dispensado, checar se ele tem
	// mais alguma rpeferencia. Se nao, foi REJEITADO.
	// over1, over2 e over3 sao apenas subconjuntos de rejected
		// Iterar APENAS sobre os professores nsat, os quais tambem nao foram rejeitados
		for(auto x = nsat_prof.begin(); x != nsat_prof.end();x = nsat_prof.begin()){	// x eh iterador de SET

			Nodes* novo = G->get_node( (*x) );
			
			Nodes* school = (* (novo->get_nxt()) );					// Ponteiro para ESCOLA.

			if( school ==  NULL)	throw 666;// NAO DEVE OCORRER.				

			novo->remove_nxt_front();	// Jah esgotou uma possibilidade.

			Nodes* antigo = school->insert_teacher( novo );

			if(antigo != NULL){	// Se novo nao pegar vala limpa, tratar casos
				if(antigo  !=  novo){	// PROFESSOR NOVO FOI ACEITO.	Professor antigo deixou de ser saturado! 

//					nsat_prof.insert(antigo->get_key()) ;	// Antigo professor passou a ser nao saturado... mas ainda tem opcaoes??
					sat_prof.erase(antigo->get_key())	;	// Antigo contratado NAO ESTAH MAIS SATURADO. Portando, remover de sat_prof. .
					
					sat_prof.insert(novo->get_key())	;	// Atual professor virou saturado.
					nsat_prof.erase(novo->get_key())	;	// Atual professsor eh REMOVIDO dos nao saturados
					
					if(antigo->get_nxt() == antigo->get_end())			/// Verificar se o professor retirado ainda tem preferencias; se nao, eh rejeitado
						rejected.insert(antigo->get_key())	;
					else											/// Se ainda tem preferencias, eh nsat
						nsat_prof.insert(antigo->get_key()) ;	// Antigo professor passou a ser nao saturado.					
				}
				else{												// Profesor for REJEITADO
					if(novo->get_nxt() == novo->get_end()){		// Verifica se ainda tem opcoes; se nao tem, eh rejeitado.
						nsat_prof.erase(novo->get_key());		// Como ele foi rejeitado, logo nao tem opcoes E portanto nao pode estar em nsat_prof.
						rejected.insert(novo->get_key());	
					}	
				}				
			}

			else{	// Saturou o professor, pois ele PEGOU UMA VAGA LIMPA.
				sat_prof.insert( novo->get_key() );
				nsat_prof.erase( novo->get_key() );
				if( school->get_sat() ==  true ){	// Se escola foi saturada, colocar no conjunto de saturadas
					sat_scho.insert( school->get_key() );
					nsat_scho.erase( school->get_key() );
				}
			}

			// Se mudou o conjunto
		}
/**/	auto y = nsat_scho.begin();

		// Soh joga os professores pras escolas.
		// Uma vez que professor conseguiu emprego, nao quer mais trocar.
		for(auto x = rejected.begin(); x != rejected.end(); x = rejected.begin(), y = nsat_scho.begin()){
			
			G->get_node( (*y) )->insert_teacher_forced( G->get_node( (*x) ) );
			if( G->get_node( (*y) )->get_sat() == true ){
				sat_scho.insert( (*y) );
				nsat_scho.erase( (*y) );
			}
			sat_prof.insert( (*x) );
			rejected.erase( (*x) );
		}
}



int main(){

	Graph * G = new Graph(1);


	Nodes foo;
	emparelhamento(G, 100, 50);

	for(int i = 101; i < 151; i++){
		Nodes* au = G->get_node(i);
		cout << "\n" << "Escola: " << au->get_key() << endl;
		if(au->get_teacher1() != NULL){
			cout << " " << au->get_teacher1()->get_key() <<  " "<< endl;
			if(au->get_teacher2() != NULL)
				cout << " " << au->get_teacher2()->get_key() << " " << endl;
				
		}
		cout << endl;
	}
/**/	
	return 0;
}