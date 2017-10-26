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
	
	// Obs: se um professor for dispensado, checar se ele tem
	// mais alguma rpeferencia. Se nao, foi REJEITADO.
	// over1, over2 e over3 sao apenas subconjuntos de rejected
		// Iterar APENAS sobre os professores nsat, os quais tambem nao foram rejeitados
		for(auto x = nsat_prof.begin(); x != nsat_prof.end(); x = nsat_prof.begin()){

			auto at = (*x);								// Ponteiro para o PROFESSOR candidato.

			auto next = at->get_nxt();					// Ponteiro para ESCOLA.

			if( next ==  NULL)	throw 666;// NAO DEVE OCORRER.				

			at->remove_nxt_front();	// Jah esgotou uma possibilidade.

			auto aux = next->insert_teacher(at);

			if(aux != NULL){	// Se at nao foi o primeiro candidato, tratar casos
				if(aux  !=  at){	// Professor antigo deixou de ser saturado! Professor novo foi aceito.
					sat_prof.erase(aux->get_key())	;	// Antigo contratado NAO ESTAH MAIS SATURADO. Portando, remover de sat_prof .
					sat_prof.insert(at->get_key())	;	// Atual professor virou saturado.
					
					if(aux->get_nxt() == aux->get_end())			/// Verificar se o professor retirado ainda tem preferencias; se nao, eh rejeitado
						rejected.insert(aux->get_key())	;
					else											/// Se ainda tem preferencias, eh nsat
						nsat_prof.insert(aux->get_key());			// Jah foi retirado dos visitados; inserir apenas nos nao visitados "com esperanca"						
				}
				else	// next foi recusado
					if(at->get_nxt() == at->get_end()){		// Verifica se ainda tem opcoes; se nao tem, eh rejeitado.
						rejected.insert(at->get_key());	
						nsat_prof.erase(at->get_key());		// Como ele foi rejeitado, logo nao tem opcoes E portanto nao pode estar em nsat_prof.
					}					
			}
			else{	// Saturou o professor, pois ele FOI O PRIMEIRO CANDIDATO.
				sat_prof.insert( at->get_key() );
				nsat_prof.erase( at->get_key() );
				if( next->get_sat() ==  true ){	// Se escola foi saturada, colocar no conjunto de saturadas
					sat_scho.insert( next->get_key() );
					nsat_scho.erase( next->get_key() );
				}
			}
			// Se mudou o conjunto
		}
}

