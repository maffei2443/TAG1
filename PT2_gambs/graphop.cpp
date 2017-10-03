/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/

#include "graphop.hpp"
#include <set>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
/////////////

void mostra_set(set <int> to_show){
    set<int> :: iterator iter;
    for(iter = to_show.begin(); iter != to_show.end(); iter++)
        cout << (*iter) << " ";
    cout << "\n\n";
}
void mostra_set_node(set <int> to_show, Graph * G){
    set<int> :: iterator iter;
    for(iter = to_show.begin(); iter != to_show.end(); iter++)
        cout << (*iter) << " ";
    cout << '\n';
	for(iter = to_show.begin(); iter != to_show.end(); iter++)
		G->get_node(*iter)->mostra_no();    
    cout << "Final do clique\n\n\n\n\n\n\n\n";
}

// Profundidade
inline void dfs_caminho(Graph * G, Nodes * no){
	dfs_caminho(G, no, 0);
}

void dfs_caminho(Graph * G, Nodes * no, int tabs){
	vector <bool> neo;
	neo.resize(1);
	for(int i=1; i <= G->get_verts(); i++) neo.push_back(G->get_node(i)->get_visit());
	dfs_caminho_instavel(G, no, tabs);
	for(int i=1; i <= G->get_verts(); i++) G->get_node(i)->set_visit(neo[i]);
}

void dfs_caminho_estavel(Graph * G, Nodes * no, set<int>& visit, int tabs){	// Obs: passar set POR REFERENCIA!!!
	if(visit.count(no->get_key()) != 0)	return;		//Elemento ja foi visitado
	visit.insert(no->get_key());
	Nodes * pivo = no;
	queue <int> fila;
	if(pivo->get_nxt() != NULL)
		while(pivo->get_nxt() != NULL){	// ainda tem nos em que incide
			if(visit.count(G->get_node(pivo->get_nxt()->get_key())->get_key()) == 0)
				fila.push(pivo->get_nxt()->get_key());
			pivo = pivo->get_nxt();
		}
	int aux;
	while(!fila.empty()){	
		aux = fila.front();
		fila.pop();
		for(int i=0; i < tabs; i++)
			cout << " ";
		cout << no->get_key() << " - " << aux << endl;
		dfs_caminho_estavel(G, G->get_node(aux), visit, tabs+1);
	}
}

void dfs_caminho_instavel(Graph * G, Nodes * no, int tabs){
	if(no->get_visit() == true)	//Elemento ja foi visitado
		return;	
	no->set_visit(true);
	Nodes * pivo = no;
	queue <int> fila;
	if(pivo->get_nxt() != NULL)
		while(pivo->get_nxt() != NULL){	// ainda tem nos em que incide
			if(G->get_node(pivo->get_nxt()->get_key())->get_visit() == false)
				fila.push(pivo->get_nxt()->get_key());
			pivo = pivo->get_nxt();
		}
//	else	{cout << "Sem proximos" << endl;return;}			// Nao tem nxts para visitar	
	int aux;
	while(!fila.empty()){
		aux = fila.front();
//		visitados.insert(aux);
		fila.pop();
		for(int i=0; i < tabs; i++)
			cout << " ";
		cout << no->get_key() << " - " << aux << endl;
		dfs_caminho_instavel(G, G->get_node(aux), tabs+1);
	}
}

void dfs_pure(Graph * G, Nodes * no, set<int>& visitados){	// Obs: passar set POR REFERENCIA!!!
	if(visitados.count(no->get_key()) != 0)	return;			//Elemento ja foi visitado
	visitados.insert(no->get_key());
	Nodes * pivo = no;
	queue <int> fila;
	while(pivo->get_nxt() != NULL){	// ainda tem nos em que incide
		if(visitados.count(G->get_node(pivo->get_nxt()->get_key())->get_key()) == 0)
			fila.push(pivo->get_nxt()->get_key());
		pivo = pivo->get_nxt();
	}
	int aux;
	while(!fila.empty()){	
		aux = fila.front();
		fila.pop();
		dfs_pure(G, G->get_node(aux), visitados);
	}
}

/// Largura	

void bfs_caminho_instavel_debug(Graph * G, Nodes * no){
	int per_lvl = 1;			// Inicialmente, apenas um noh expansivel
	int new_per_lvl = 0;
	int profundidade = 0;
	cout << "Inicia em: " << no->get_key() << endl;
	Nodes * pivo = no;
	queue <int> fila;
	set<int> expandido;
	fila.push(pivo->get_key());
	while(!fila.empty()){
		for(int j=0; j < per_lvl; j++){
			int aux = fila.front();
			new_per_lvl += G->get_node(aux)->get_qtd_nxt();		// Nova qtd de elemetos por level
			cout << "Expandindo: " << aux << endl;
			if(expandido.count(aux) == 0){			// Ainda nao foi expandido o noh
				pivo = G->get_node(aux)->get_nxt();
				while(pivo != NULL){	// ainda tem nos em que incide
					if(expandido.count(pivo->get_key()) == 0)	// Se nao foi expandido, insere
						fila.push(pivo->get_key());
					else	cout << "Ciclo! ";// << aux << "-" << pivo->get_key() << endl;
					for(int i = 0; i < profundidade; i++) cout << " ";
					cout << aux << "-" << pivo->get_key() << endl;
					pivo = pivo->get_nxt();
				}
			}
			fila.pop();		expandido.insert(aux);
		}
		profundidade++;	per_lvl = new_per_lvl; new_per_lvl = 0;
	}
}

void bfs_caminho_instavel(Graph * G, Nodes * no){
	Nodes * pivo = no;
	queue <int> fila;	set <int> expandido;
	fila.push(pivo->get_key());
	while(!fila.empty()){
		int aux = fila.front();
		if(expandido.count(aux) == 0){			// Ainda nao foi expandido o noh
			pivo = G->get_node(aux)->get_nxt();
			while(pivo != NULL){	// ainda tem nos em que incide
				if(expandido.count(pivo->get_key()) == 0)	// Se nao foi expandido, insere
					fila.push(pivo->get_key());
				pivo = pivo->get_nxt();
			}
		}
		fila.pop();		expandido.insert(aux);			/// Tira da pilha E marca como expandido
	}
}

void bfs_caminho(Graph * G, Nodes * no){
	vector <bool> neo;
	neo.resize(1);
	for(int i=1; i <= G->get_verts(); i++) neo.push_back(G->get_node(i)->get_visit());
	bfs_caminho_instavel_debug(G, no);	
	for(int i=1; i <= G->get_verts(); i++) G->get_node(i)->set_visit(neo[i]);
}

void bk(Graph * G, int const& min, set<int>clique, set<int>candidatos, set<int>falhos){
    if(falhos.empty() == true && candidatos.empty() == true)
    	if(clique.size() >= min){
    	cout << "Maximal: ";
    	mostra_set_node(clique, G);
    	}
    else if(candidatos.empty() == true) return;
    
    set<int> clique_ext, nxts_no, intercecao_cand_nxts, intercecao_falhos_nxts;
    set<int>::iterator it_candidatos, it_nxts, it_intercecao;

    for(it_candidatos = candidatos.begin();it_candidatos != candidatos.end(); it_candidatos = candidatos.begin()){	// Sempre mudo candidato.begin
        clique_ext = clique;
        clique_ext.insert(*it_candidatos);
        for(Nodes * pivo = G->get_node((*it_candidatos))->get_nxt(); pivo != NULL; pivo = pivo->get_nxt())
            nxts_no.insert(pivo->get_key());            //  Usado p/ intercecao com o clique
        for(it_intercecao = nxts_no.begin(); it_intercecao != nxts_no.end(); it_intercecao++){
           if(nxts_no.count((*it_intercecao)) > 0 && candidatos.count((*it_intercecao)) > 0)
                intercecao_cand_nxts.insert((*it_intercecao));
            if(nxts_no.count((*it_intercecao)) > 0 && falhos.count((*it_intercecao)) > 0)
                intercecao_falhos_nxts.insert((*it_intercecao));
        }     
        bk(G, min, clique_ext, intercecao_cand_nxts, intercecao_falhos_nxts);
        
        clique_ext.clear();
        nxts_no.clear();
        intercecao_cand_nxts.clear();
        intercecao_falhos_nxts.clear();
        // Duhhhhhhhhhhhhhhh
        candidatos.erase((*it_candidatos));
        falhos.insert((*it_candidatos));    
    }
}

void bk(Graph * G, int min){
	if(min<0 || min > G->get_verts())	min = 0;
    set<int> vazio;
    set<int> cheio;
    for(int i=1; i < G->get_verts()+1; i++)
        cheio.insert(G->get_node(i)->get_key());
    //cout << "Inicialmente, candidatos sao:\n";
//    mostra_set(cheio);
    cout << "Serao mostrados cliques maximais com " << min << "+ componentes:\n";
    bk(G,min, vazio, cheio, vazio);
}

void mostra_por_nota(Graph *G){
	vector<int> vecbros;
	vecbros.resize(G->get_verts());
	for (int i=0;i<G->get_verts(); i++){
		vecbros[i]=0;
	}
	for (int i=1;i<=G->get_verts(); i++){
		vecbros[G->get_node(i)->get_qtd_nxt()]++;
	}
	for (int i=G->get_verts()-1;i!=0; i--){
		int j=1;
		while (vecbros[i]!=0){
			if (G->get_node(j)->get_qtd_nxt()==i){
				vecbros[i]--;
				cout << G->get_node(j)->get_key() << " : " <<G->get_node(j)->get_matricula() << endl;
			}
			j++;
		}
	}
}

// Outros

void clicks_maxi_node_debug(Graph* G, Nodes * no, set<int> el_clique, set<int> candidatos, set<int>& inutil){   // Requer ainda um parametro "secreto", que estah no proprio grafo
    queue<int> pre_candidatos;  // Vai tentar expandir eles
    queue<int>candidatos2;
    set<int>::iterator iter, iter2;    // Vai iterar sobre conjunto que forma o clique
    int aux;
    bool maximal, expande;                // Por padrao, eh o maximal.
    cout << "\n\nNoh atual: " << no->get_key() << endl;

	el_clique.insert(no->get_key());		// Insere a si mesmo na lista de node do clique
    candidatos.erase(no->get_key());
    Nodes * pivo;						// Vai percorrer lista de adjacencia do noh
    if(no->get_qtd_nxt() != 0){        // Ah nao ser que seja na primeira chamada, TEM que ter qtd_nxt
        for(pivo =  no->get_nxt(); pivo != NULL; pivo = pivo->get_nxt()){
            if(inutil.count(pivo->get_key()) == 0){   // Se ainda nao foi eh inutil
              	   	pre_candidatos.push(pivo->get_key());   //  Insere na fila p/ VER SE eh candidato
                  	cout << pivo->get_key() << " ";
                }
            }
            cout << '\n';
        }
        while(pre_candidatos.empty() == false){       // Enquanto fila nao vazia, checar os nxt recursivamente
            aux = pre_candidatos.front();  pre_candidatos.pop();             
           ////////////////////////		CRIANDO LISTA DOS VIZINHOSS DE G->get_node(aux)
            if(G->adjacentes[aux].empty() == true){	// Tste p/ nao recriar varias vezes a msm lista :P
	            cout << "Criando lista de adjacencia para " << aux << " :\n";
	            for(pivo=G->get_node(aux)->get_nxt(); pivo != NULL; pivo = pivo->get_nxt()){
		            G->adjacentes[aux].insert(pivo->get_key());
		            cout << "Inseriu "<< pivo->get_key() <<"\n";
	            }
	        }
	        ////////////////////////
	        // P/ cada aux, ver se ele contem toodos os node do clique como nxts
			set<int>::iterator help = el_clique.end();
	        for(iter2 = el_clique.begin(), expande =true; iter2 != el_clique.end(); iter2++){
	        	if(G->adjacentes[aux].count(*iter2) == 0){
	        		cout << "iter2 == " << (*iter2) << endl;
	        		inutil.insert(aux);		expande = false;
	        		break;
	        		}
	        	if(*help == *iter2)	break;
	        	help = iter2;	
	        	cout << "se lascar" << endl;
	        }
				     	
            if(expande == true){
            	candidatos.insert(aux); 
	            candidatos2.push(aux);	//recoloca na fila
	        }
            else
            	candidatos.erase(aux);
    	}


    	while(candidatos2.empty() == false){
    		maximal = false;
    		aux = candidatos2.front();	candidatos2.pop();
    		clicks_maxi_node(G, G->get_node(aux), el_clique, candidatos, inutil);
    	}
    	if(maximal == true)
    		cout << "Maximal:";
   		for(iter=el_clique.begin(); iter != el_clique.end(); iter++)
   			cout << (*iter) << " ";
   		cout << endl;	
}
//*/
void clicks_maxi_node(Graph* G, Nodes * no, set<int> el_clique, set<int> candidatos, set<int>& inutil){   // Requer ainda um parametro "secreto", que estah no proprio grafo
    queue<int> pre_candidatos;  // Vai tentar expandir eles
    queue<int>candidatos2;
    set<int>::iterator iter, iter2;    // Vai iterar sobre conjunto que forma o clique
    int aux;
    bool maximal, expande;                // Por padrao, eh o maximal.

	el_clique.insert(no->get_key());		// Insere a si mesmo na lista de node do clique
    candidatos.erase(no->get_key());
    Nodes * pivo;						// Vai percorrer lista de adjacencia do noh
    if(no->get_qtd_nxt() != 0){        // Ah nao ser que seja na primeira chamada, TEM que ter qtd_nxt
        for(pivo =  no->get_nxt(); pivo != NULL; pivo = pivo->get_nxt())
//            if(inutil.count(pivo->get_key()) == 0)   // Se ainda nao foi eh inutil
              	   	pre_candidatos.push(pivo->get_key());   //  Insere na fila p/ VER SE eh candidato                       
        
        while(pre_candidatos.empty() == false){       // Enquanto fila nao vazia, checar os nxts recursivamente
            aux = pre_candidatos.front();  pre_candidatos.pop();             
           ////////////////////////		CRIANDO LISTA DOS VIZINHOSS DE G->get_node(aux)
            if(G->adjacentes[aux].empty() == true)	// Tste p/ nao recriar varias vezes a msm lista :P
	            for(pivo=G->get_node(aux)->get_nxt(); pivo != NULL; pivo = pivo->get_nxt())
		            G->adjacentes[aux].insert(pivo->get_key());
	            	       
	        ////////////////////////
	        // P/ cada aux, ver se ele contem toodos os node do clique como nxts
			set<int>::iterator help = el_clique.end();
			expande =true;
	        for(iter2 = el_clique.begin() ; iter2 != el_clique.end(); iter2++){
	        	if(G->adjacentes[aux].count(*iter2) == 0){
	        		inutil.insert(aux);		expande = false;
	        		break;
	        		}
	        	if(*help == *iter2)	break;
	        	help = iter2;	
	        }
				     	
            if(expande == true){
            	candidatos.insert(aux); 
	            candidatos2.push(aux);	//Coloca em outra fila
	            maximal = false;
	        }
            else{
            	candidatos.erase(aux);
            }
    	}


    	while(candidatos2.empty() == false){
    		maximal = false;
    		aux = candidatos2.front();	candidatos2.pop();
    		clicks_maxi_node(G, G->get_node(aux), el_clique, candidatos, inutil);
    	}
    	if(expande == false)
    		inutil.insert(aux);

    	if(maximal == true)
    		cout << "Maximal:";
   		for(iter=el_clique.begin(); iter != el_clique.end(); iter++)
   			cout << (*iter) << " ";
   		cout << endl;	
	}
	else 	cout << "No isolado; portanto jah eh maximal." << endl;
}

void clicks_maxi_node(Graph * G, Nodes * no, set<int>candidatos){
    cout << "No base:     " << no->get_key() << endl;
    G->adjacentes.resize(G->get_verts()+1);
    int qtd_nxt[G->get_verts()+1];

    set <int> el_clique, inutil;
    clicks_maxi_node(G, no, el_clique, candidatos, inutil);

    G->adjacentes.resize(0);
}

///*


void max_click(Graph * G){
	set<int> candidatos;
	for(int i = 1; i <= G->get_verts(); i++)
		candidatos.insert(G->get_node(i)->get_key());
	for(int i = 1; i  <= G->get_verts(); i++)
		clicks_maxi_node(G, G->get_node(i), candidatos);
}

bool big_keyy(Nodes * a, Nodes * b){return (a->get_key() < b->get_key());}	// Ordena crescente
bool small_keyy(Nodes * a, Nodes * b){return (a->get_key() > b->get_key());}	// Ordena decrescente

bool comp(Nodes * a, Nodes * b){if(a->get_qtd_nxt() != b->get_qtd_nxt())return (a->get_qtd_nxt() < b->get_qtd_nxt());	return big_keyy(a,b);}	// Ordena crescente
bool comp_r(Nodes * a, Nodes * b){if(a->get_qtd_nxt() != b->get_qtd_nxt()) return (a->get_qtd_nxt() > b->get_qtd_nxt()); return small_keyy(a,b);}	// Ordena crescente


void sort_reach(Graph * G){	
	sort(G->iterador()+1, G->iterador() + G->get_verts() + 1 , comp);
}

void sort_reach_r(Graph * G){	
	sort(G->iterador()+1, G->iterador() + G->get_verts() + 1 , comp_r);
}

void sort_keyy(Graph* G){
	sort(G->iterador()+1, G->iterador() + G->get_verts() + 1 , big_keyy);
}

// Ordenacao topologica BEM especifica

vector<int> sort_tp(Graph * G){		// Retorna uma ordenacao topologica do grafo
	int verts = G->get_verts();	

	map <int, int> code_index;
	queue <int> nxt_sorted;		// Proximos a SEREM INSERIDOS, de qqer forma, na ordenacao topologica.
	vector<int>	sorted;			// Uma possivel ordenacao topologica
	vector<bool> inserted(verts+3, false);	// Inseridos na ordem

	bool tg1_added = false;	// Se torna true apenas quando o TG1 for adicionado aa fila
	int tg1, index_tg1;	// Vaii armazenar o id de TG1 no grafo
//	int min = ceil((3 * G->get_sum_pay)/4);
//	int done = 0;			// Cursou nenhumam ateria inicialmente
	// Coloca todos os de grau de chegada zero em uma fila.
	for(int i = 1; i < verts+1; i++){
		// Criando o mapa para busca mais eficiente depois.
		code_index.insert(code_index.begin(), pair<int,int>(G->get_node(i)->get_key(), i));	// Necesario; faz o map.
		
		if(G->get_node(i)->get_in() == 0)
			if(G->get_node(i)->get_name() != "TG1")
				nxt_sorted.push(i);
			else{
				tg1 = G->get_node(i)->get_key();
				index_tg1 = i;
			}
	}
	queue<int> to_decrease_by_one;
	for(int id; nxt_sorted.empty() == false;){
		for(int i = 0, j = nxt_sorted.size(); i < j; i++){	// Esvazia a parte da pilha que foi enviada para cah.
			id = nxt_sorted.front();	// 'id' contem a posicao no vetor jah.
			nxt_sorted.pop();
			// POSSIVELMENTE enche novamente a pilha
			Nodes * pivot;
			// Para cada vertice, verifica se seu "sucessores" podem seradicionados aa fila
			for(pivot = G->get_node(id)->get_nxt(); pivot != NULL; ){
				to_decrease_by_one.push(code_index.find(pivot->get_key())->second);	// Lista das materias a se decrementar o grau de incidencia.				
				if(pivot->get_nxt() != NULL)
					pivot = pivot->get_nxt();
				else
					pivot = NULL;
			}
			for(int aux; to_decrease_by_one.empty() == false;){	// Enquanto houver decrementos pendentes, decrementar
				aux = to_decrease_by_one.front();
				to_decrease_by_one.pop();
				G->get_node(aux)->plus_in(-1);
				int in_degree = G->get_node(aux)->get_in();
				if(in_degree < 1){		// Se fez todos os pre-erq, pode entrar na ordem
					int tmp = code_index.find(G->get_node(aux)->get_key())->second;
					if(inserted[tmp] == false){ // Se ainda nao foi colocado na lista ordenada, eh colocado
						nxt_sorted.push(code_index.find(G->get_node(aux)->get_key())->second);
					}
				}
			}
			sorted.push_back(id);	// Lista com ordenacao tpologica valida.
			inserted[id] = true;
		}
	}
	int j=0;	sorted.push_back(-1);	// Fim da fila
	for(vector<int>::iterator it = sorted.begin(); sorted[j] != -1; it++, j++)
		sorted[j] = G->get_node(*it)->get_key();
	sorted[j] = tg1;

	int tmp;
	for(Nodes * pivo = G->get_node(index_tg1)->get_nxt(); pivo != NULL; pivo = pivo->get_nxt())
		if(pivo->get_name() == "TG2"){
			tmp = pivo->get_key();
			break;
		}
	sorted.push_back(tmp);

	return sorted;	
}

// Caminho critico


Critcpath true_dfs_cp(Graph * G, Nodes * no, map <int, int> code_index){ // Obs: passar set POR REFERENCIA!!!
    // Coloca todos os de grau de chegada zero em uma fila.

    if(no->get_nxt() == NULL)   return Critpath(no);            //Elemento ja foi visitado
    Nodes * pivo = no;
    Critcpath maxpath, aux;

    while(pivo->get_nxt() != NULL){ // ainda tem nos em que incide
        aux = true_dfs_cp(G, G->get_node(code_index.find(pivo->get_nxt()->get_key())->second), code_index);
        if(aux.accumulatedcost > maxpath.accumulatedcost)
            maxpath = aux;  
        pivo = pivo->get_nxt();
    }
    maxpath.addnodes(no);
    return maxpath;
}

Critcpath dfs_cp(Graph * G, Nodes * no){
	map <int, int> code_index;
    for(int i = 1; i < G->get_verts()+1; i++){
        // Criando o mapa para busca mais eficiente depois.
        code_index.insert(code_index.begin(), pair<int,int>(G->get_node(i)->get_key(), i)); // Necesario; faz o map.
     }
     return true_dfs_cp(G, no, code_index);

}