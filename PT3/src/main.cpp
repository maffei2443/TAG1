#include "graph.hpp"
#include <iostream>
using namespace std;

void emparelhamento(Graph * G, const int& PROF, const int& SCHO){

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
	
	// Obs: se um professor for dispensado, checar se ele tem
	// mais alguma rpeferencia. Se nao, foi REJEITADO.
	// over1, over2 e over3 sao apenas subconjuntos de rejected
		// Iterar APENAS sobre os professores nsat, os quais tambem nao foram rejeitados

	for(int i=1; nsat_prof.empty() == false;i++){
		set<int> nxt_nsat;
		for(auto x = nsat_prof.begin(); x != nsat_prof.end(); x++){

			Nodes* next = G->get_node(*x);								
			Nodes* scho = *(G->get_node(*x)->get_nxt());

			cout << "next == " << next->get_key() << endl;
			cout << "scho == " << scho->get_key() << endl;
			if( next ==  NULL)	throw 666;// NAO DEVE OCORRER.				

			next->remove_nxt_front();	// Jah esgotou uma possibilidade.

			auto aux = scho->insert_teacher_debug(next);

			if(aux != NULL){	// Se at nao foi o primeiro candidato, tratar casos
				if(aux  !=  next){	// Professor antigo deixou de ser saturado! Professor novo foi aceito.

					sat_prof.erase(aux->get_key())	;	// Antigo contratado NAO ESTAH MAIS SATURADO. Portando, remover de sat_prof .
					sat_prof.insert(next->get_key())	;	// Atual professor virou saturado.
					
					if(aux->get_nxt() == aux->get_end())			/// Verificar se o professor retirado ainda tem preferencias; se nao, eh rejeitado
						rejected.insert(aux->get_key())	;
					else											/// Se ainda tem preferencias, eh nsat
						nxt_nsat.insert(aux->get_key());			// Jah foi retirado dos visitados; inserir apenas nos nao visitados "com esperanca"						
				}
				else{	// next foi recusado
					if(next->get_nxt() == next->get_end()){		// Verifica se ainda tem opcoes; se nao tem, eh rejeitado.
						rejected.insert(next->get_key());	
						nxt_nsat.erase(next->get_key());		// Como ele foi rejeitado, logo nao tem opcoes E portanto nao pode estar em nsat_prof.
					}
					else	// ainda tem opcoes!!!
						nxt_nsat.insert(next->get_key());		// Lol tinha me esquecido dessa linha :/
				}					
			}
			else{	// Saturou o professor, pois ele FOI O PRIMEIRO CANDIDATO.
				sat_prof.insert( next->get_key() );
				nxt_nsat.erase( next->get_key() );
				if( scho->get_sat() ==  true ){	// Se escola foi saturada, colocar no conjunto de saturadas
					sat_scho.insert( scho->get_key() );
					nsat_scho.erase( scho->get_key() );
				}
			}
			// Se mudou o conjunto
		}
		cout << "\n\n\nnsat_prof : " << nsat_prof.size() << endl;
		cout << "nxt_nsat : " << nxt_nsat.size() << endl;
		cout << "rejected : " << rejected.size() << endl;
		nsat_prof = nxt_nsat;
		cout << i << "ª passada\n";
		getchar();
	}
	cout << "Rejeitados antes: " << rejected.size() << endl;
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
	cout << "Rejeitados depois: " << rejected.size() << endl;
}

int main(){

	Graph * G = new Graph(1);


	Nodes foo;
	emparelhamento(G, 100, 50);
	getchar();
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