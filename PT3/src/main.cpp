#include "graph.hpp"
#include <iostream>
using namespace std;

int try_match_equal(Graph * G, Nodes* prof, Nodes* scho, set<int>& overX, set<int>& rejected, set<int>& nsat_scho, const int& req){
	if( prof->get_hab() == req ){
		scho->insert_teacher( prof );
		overX.erase( prof->get_key() );
		rejected.erase( prof->get_key() );
		if(scho->get_sat() == true)
			nsat_scho.erase( scho->get_key() );
		return 1;
	}
	return 0;
}

int try_match_bigger(Graph * G, Nodes* prof, Nodes* scho, set<int>& overX, set<int>& rejected, set<int>& nsat_scho, const int& req){
	if( prof->get_hab() > req ){
		scho->insert_teacher( prof );
		overX.erase( prof->get_key() );
		rejected.erase( prof->get_key() );
		if(scho->get_sat() == true)
			nsat_scho.erase( scho->get_key() );
		return 1;
	}
	return 0;
}

void emparelhamento_lixo(Graph * G, const int& PROF, const int& SCHO){

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

	while(nsat_prof.empty() == false){
		set<int> nxt_nsat;
		for(auto x = nsat_prof.begin(); x != nsat_prof.end(); x++){

			Nodes* next = G->get_node(*x);								
			Nodes* scho = *(G->get_node(*x)->get_nxt());

			if( next ==  NULL)	throw 666;// NAO DEVE OCORRER.				

			next->remove_nxt_front();	// Jah esgotou uma possibilidade.

			auto aux = scho->insert_teacher(next);

			if(aux != NULL){	// Se at nao foi o primeiro candidato, tratar casos
				if(aux  !=  next){	// Professor antigo deixou de ser saturado! Professor novo foi aceito.

					sat_prof.erase(aux->get_key())	;	// Antigo contratado NAO ESTAH MAIS SATURADO. Portando, remover de sat_prof .
					sat_prof.insert(next->get_key())	;	// Atual professor virou saturado.
					
					if(aux->get_nxt() == aux->get_end()){			/// Verificar se o professor retirado ainda tem preferencias; se nao, eh rejeitado
						rejected.insert(aux->get_key())	;
						int key = next->get_key();
						switch(key){
							case 1: over1.insert(key);break;
							case 2: over2.insert(key);break;
							case 3: over3.insert(key);break;
						}
					}
					else											/// Se ainda tem preferencias, eh nsat
						nxt_nsat.insert(aux->get_key());			// Jah foi retirado dos visitados; inserir apenas nos nao visitados "com esperanca"						
				}
				else{	// next foi recusado
					if(next->get_nxt() == next->get_end()){		// Verifica se ainda tem opcoes; se nao tem, eh rejeitado.
						rejected.insert(next->get_key());
						int key = next->get_key();
						switch(key){
							case 1: over1.insert(key);break;
							case 2: over2.insert(key);break;
							case 3: over3.insert(key);break;
						}
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
		nsat_prof = nxt_nsat;
	}
	cout << "Inseriu com as preferencias dos professores\n";
/**/	auto y = nsat_scho.begin();

		// Soh joga os professores pras escolas.
		// Uma vez que professor conseguiu emprego, nao quer mais trocar.
		int change = 1;
		while(change == 1){
			change = 0;
			for(auto x = nsat_scho.begin(); x != nsat_scho.end(); x++){
				Nodes* scho = G->get_node(*x);
				int req = scho->get_hab();
				cout << "Here1 " << scho->get_key() << endl;
				switch(req){
					case 1:

						for(auto y = over1.begin(); y != over1.end(); y++){						
							Nodes* tmp = G->get_node( (*y) );
							if( tmp->get_hab() == req ){
								change = 1;
								scho->insert_teacher( tmp );
								over1.erase( tmp->get_key() );
								rejected.erase( tmp->get_key() );
								if(scho->get_sat() == true)
									nsat_scho.erase( scho->get_key() );
							}
						}						
						break;
					case 2:

						for(auto y = over2.begin(); y != over2.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							if( tmp->get_hab() == req ){
								change = 1;
								scho->insert_teacher( tmp );
								over1.erase( tmp->get_key() );
								rejected.erase( tmp->get_key() );
								if(scho->get_sat() == true)
									nsat_scho.erase( scho->get_key() );
							}
						}					
						break;
					case 3:

						for(auto y = over3.begin(); y != over3.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							if( tmp->get_hab() == req ){
								change = 1;
								scho->insert_teacher( tmp );
								over1.erase( tmp->get_key() );
								rejected.erase( tmp->get_key() );
								if(scho->get_sat() == true)
									nsat_scho.erase( scho->get_key() );
							}
						}						
						break;
				}
			}
		}
		change = 1;
		while(change == 1){
			change = 0;
			for(auto x = nsat_scho.begin(); x != nsat_scho.end(); x++){
				Nodes* scho = G->get_node(*x);
				int req = scho->get_hab();
				switch(req){
					case 1:
						for(auto y = over1.begin(); y != over2.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							if( tmp->get_hab() > req ){
								change = 1;
								scho->insert_teacher(tmp);
								over1.erase( tmp->get_key() );
								rejected.erase( tmp->get_key() );
								if(scho->get_sat() == true)
									nsat_scho.erase( scho->get_key() );
							}
						}
						break;
					case 2:
						for(auto y = over2.begin(); y != over2.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							if( tmp->get_hab() > req ){
								change = 1;
								scho->insert_teacher(tmp);
								over2.erase( tmp->get_key() );
								rejected.erase( tmp->get_key() );
								if(scho->get_sat() == true)
									nsat_scho.erase( scho->get_key() );
							}
						}
						break;
					case 3:
						for(auto y = over3.begin(); y != over3.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							if( tmp->get_hab() > req ){
								change = 1;
								scho->insert_teacher(tmp);
								over3.erase( tmp->get_key() );
								if(scho->get_sat() == true)
								rejected.erase( tmp->get_key() );
									nsat_scho.erase( scho->get_key() );
							}		
						}
						break;
				}
			}
		}
//*/
		for(auto x = rejected.begin(); x != rejected.end(); x = rejected.begin(), y = nsat_scho.begin()){
			
			G->get_node( (*y) )->insert_teacher_forced( G->get_node( (*x) ) );
			if( G->get_node( (*y) )->get_sat() == true ){
				sat_scho.insert( (*y) );
				nsat_scho.erase( (*y) );
			}
			sat_prof.insert( (*x) );
			rejected.erase( (*x) );
		}
//*/
}

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
//########################################################################################################
	while(nsat_prof.empty() == false){
		set<int> nxt_nsat;
		for(auto x = nsat_prof.begin(); x != nsat_prof.end(); x++){

			Nodes* next = G->get_node(*x);								
			Nodes* scho = *(G->get_node(*x)->get_nxt());

			if( next ==  NULL)	throw 666;// NAO DEVE OCORRER.				

			next->remove_nxt_front();	// Jah esgotou uma possibilidade.

			auto aux = scho->insert_teacher(next);

			if(aux != NULL){	// Se at nao foi o primeiro candidato, tratar casos
				if(aux  !=  next){	// Professor antigo deixou de ser saturado! Professor novo foi aceito.

					sat_prof.erase(aux->get_key())	;	// Antigo contratado NAO ESTAH MAIS SATURADO. Portando, remover de sat_prof .
					sat_prof.insert(next->get_key())	;	// Atual professor virou saturado.
					
					if(aux->get_nxt() == aux->get_end()){			/// Verificar se o professor retirado ainda tem preferencias; se nao, eh rejeitado
						rejected.insert(aux->get_key())	;
						int key = next->get_key();
						switch(key){
							case 1: over1.insert(key);break;
							case 2: over2.insert(key);break;
							case 3: over3.insert(key);break;
						}
					}
					else											/// Se ainda tem preferencias, eh nsat
						nxt_nsat.insert(aux->get_key());			// Jah foi retirado dos visitados; inserir apenas nos nao visitados "com esperanca"						
				}
				else{	// next foi recusado
					if(next->get_nxt() == next->get_end()){		// Verifica se ainda tem opcoes; se nao tem, eh rejeitado.
						rejected.insert(next->get_key());
						int key = next->get_key();
						switch(key){
							case 1: over1.insert(key);break;
							case 2: over2.insert(key);break;
							case 3: over3.insert(key);break;
						}
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
		nsat_prof = nxt_nsat;
	}
//########################################################################################################	

		// Soh joga os professores pras escolas.
		// Uma vez que professor conseguiu emprego, nao quer mais trocar.
		int change = 1, again = 1;
		while(again == 1){
			again = change = 0;
			for(auto x = nsat_scho.begin(); x != nsat_scho.end(); x++){
				Nodes* scho = G->get_node(*x);
				int req = scho->get_hab();
				cout << "Here1 " << scho->get_key() << endl;
				switch(req){
					case 1:

						for(auto y = over1.begin(); y != over1.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							change = try_match_equal(G, tmp, scho, over1, rejected, nsat_scho, req);
						}						
						break;
					case 2:

						for(auto y = over2.begin(); y != over2.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							change = try_match_equal(G, tmp, scho, over2, rejected, nsat_scho, req);
						}					
						break;
					case 3:

						for(auto y = over3.begin(); y != over3.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							change = try_match_equal(G, tmp, scho, over3, rejected, nsat_scho, req);
						}						
						break;
				}
				if(change == 1)
					again = 1;
			}
		}
		change = 1, again = 1;
		while(again == 1){
			again = change = 0;
			for(auto x = nsat_scho.begin(); x != nsat_scho.end(); x++){
				Nodes* scho = G->get_node(*x);
				int req = scho->get_hab();
				cout << "Here1 " << scho->get_key() << endl;
				switch(req){
					case 1:

						for(auto y = over1.begin(); y != over1.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							change = try_match_bigger(G, tmp, scho, over1, rejected, nsat_scho, req);
						}						
						break;
					case 2:

						for(auto y = over2.begin(); y != over2.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							change = try_match_bigger(G, tmp, scho, over2, rejected, nsat_scho, req);
						}					
						break;
					case 3:

						for(auto y = over3.begin(); y != over3.end(); y++){
							Nodes* tmp = G->get_node( (*y) );
							change = try_match_bigger(G, tmp, scho, over3, rejected, nsat_scho, req);
						}						
						break;
				}
				if(change == 1)
					again = 1;
			}
		}

//*/	
		auto y = nsat_scho.begin();
		for(auto x = rejected.begin(); x != rejected.end(); x = rejected.begin(), y = nsat_scho.begin()){
			
			G->get_node( (*y) )->insert_teacher_forced( G->get_node( (*x) ) );
			if( G->get_node( (*y) )->get_sat() == true ){
				sat_scho.insert( (*y) );
				nsat_scho.erase( (*y) );
			}
			sat_prof.insert( (*x) );
			rejected.erase( (*x) );
		}
//*/
}


int main(){
/*
	change = try_match(G, tmp, over1, rejected, nsat_scho, req)

*/
	Graph * G = new Graph(1);


	Nodes foo;
	emparelhamento(G, G->get_prof(), G->get_scho());

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