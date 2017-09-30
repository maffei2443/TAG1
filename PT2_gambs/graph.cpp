/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/
#include "nodes.hpp"
#include "graph.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
/// class Graph

// private

void Graph :: exclui_aninhado(Nodes * excluir){
	if(excluir == NULL)	return;
	if(excluir->get_nxt() != NULL)
		exclui_aninhado(excluir->get_nxt());
	delete(excluir);
}

void Graph :: mostra_set(set <int> to_show){
    set<int> :: iterator iter;
    for(iter = to_show.begin(); iter != to_show.end(); iter++)
        cout << (*iter) << " ";
    cout << '\n';
}

void inline Graph :: exclude_list(int index){
	exclui_aninhado(node[index]);
}


// public
Graph :: Graph() : edge(0), verts(0){node.resize(1);///*/
}
Graph :: Graph(int, int){
	cout << "Contrutor para bedug\n";
	int id, code, rec_credits, hardness, pre_req;	//id: posicao no vetor (this->key); code = codigo da disciplina no MW (this->matricula)
	string name;
	ifstream arq("fluxo_cic.txt");
 	
	int id_max;		arq >> id_max;
	cout << id_max;
	// Debug
	getline(arq, name);
	cout << name << endl;

	getline(arq, name);
	cout << name << endl;

	this->verts = id_max;
	this->node.resize(id_max + 1);
	

	int prev[id_max+1] {};	// fila para usar pra guardar pre-requisitos
	int i;
	do{
		i = 0;
		arq >> id >> code >> rec_credits >> hardness >> name;

		if(id > id_max)		return;	// Arquivo zuado :/ .

		int cost = rec_credits * hardness;
		node[id] = new Nodes(code);	this->node[id]->set_name(name);	this->node[id]->set_cost(cost);
		cout << "Atual> " << id << endl;
		// Vai pegar os pre-requisitos
		do{
			arq >> code;
			cout << code << ' ';
			if(code != 0 && code != -1){
				prev[i] = code;
				if(code == 1)	cout << "Pre-req de " << id << endl;
// zoado		this->node[code]->plus_out(1);	// +1 mateira que libera
				this->node[id]->plus_in(1);		// +1 pre-requisito
				i++;
			}
			else
				cout << "\nPulou " << code << endl;
			// -1 eh seprador de requisitos
		}while(code != 0);
		
		for(int j=0; j < i; j++){
			this->node[prev[j]]->insert_qtd_nxt_pro(new Nodes(this->node[id], this->node[id]->get_cost()));		
			this->node[prev[j]]->set_out(this->node[prev[j]]->get_qtd_nxt());
		}

		switch (id){case 5: case 9: case 14:
					case 19: case 24: case 29:
					case 32: case 34:	getline(arq,name);		// Quebra de linha entre os semestres
		}
				
	}while(id != id_max);
	cout << "Construiu grafo do fluxo " << endl;
	arq.close();
}

Graph :: Graph(string){
	edge = 0;	verts = 0;
	vector <string> friend_list;	/// Lista auxiliar p/ contruir a list de adjacencia APOS ler todo o arq
	friend_list.resize(1);
	this->node.resize(1);	// Assim os node se iniciam pelo numero 1, posicao 1
	ifstream arq;
	arq.open("amigos_tag20172.txt");
//	arq.open("minigrafo");
	int aux, aux2;
	string line, s_aux;
	int index, j;			// Bbs: 'j' e 'index' sao variaveis >essenciais <
	/// Ler os dados e criar o grafo
	for(index=1; arq.eof() == false; index++){
		///Ler a line
		getline(arq, line); line += '\n';	// Marca o termino da line. Serah util ao final
		///Pegar o ID do animal	
		for(j=0, aux=0; line[j] <= '9' && line[j] >= '0'; j++)
			aux = aux*10 + (line[j] - 48);
		j++;				// Para  << passar pela virgula
		this->insert(new Nodes(aux));		// Obviamente, aux == index
		this->node[index]->set_qtd_nxt(0);			// Serao contados QUANDO for mantada a list de adjacencia
/*//////////////////////////////////////////////////*/
		for(	 aux=0; line[j] != ',' ; j++)		// A matricula termina com virgula
			aux = aux*10 + (line[j] - 48);
		j++;				// Ultima virgula antes do name
		this->node[index]->set_matricula(aux);
//		cout << "Matricula?:		" << this->node[index]->get_matricula() << endl;
/*//////////////////////////////////////////////////*/
		line.erase(0, j);				/// Apaga o que vem ANTES do Nome
		s_aux = line;
		for(aux=0; s_aux[aux] != ',' &&  s_aux[aux] != '\n';aux++);// Conta quantos caracteres vem ANTES da primeira virgula
		s_aux.erase(0, aux+1);				// Deixa entao apenas a list dos nxts (apaga a primeira virgula tbm)
		
		if(s_aux.length() == 0)
			friend_list.push_back("\n");		
		else{
			line.erase(aux);					//  Deixa apenas o name da pessoa (apaga o que vem DEPOIS)
			s_aux = s_aux+ '\n';
			friend_list.push_back(s_aux);
		}
		
		this->node[index]->set_name(line);
		line += "\n"; 
	}
//	cout << "Contador de qtd_nxt. " << endl;
	for(int i =1, count=0; i < index; i++, count=0){		// Obs: redundante; deveria ter salvo os nxts em vectors
		char c;
		for(j=0; (c = friend_list[i][j]) != '\n'; j++)
			if(c == ',')	count++;		
		if(j == 0 || j == 1)this->node[i]->set_qtd_nxt(j);
		else				this->node[i]->set_qtd_nxt(count+1);
//		this->node[i]->mostra_no();
	}

	/// Efetivamente vai criar a list de adjacencia
	for(int i =1, c ; i < index; i++){
		for(j=0; (c = friend_list[i][j]) != '\n'; j++){
			for(aux=0;c >= '0' && c <= '9';){
				aux = aux*10 + (c - 48);
				j++;
				c = friend_list[i][j];
			}
			this->node[i]->insere_pre_calculado(this->node[aux]);	// Insere nxt de node[i] a partir de this->node[aux]; JAH CONTA OS AMIGOS!!!
		}
	}
	arq.close();
}

//*

Graph :: Graph(int){
	int id, code, rec_credits, hardness, pre_req;	//id: posicao no vetor (this->key); code = codigo da disciplina no MW (this->matricula)
	string name;
	ifstream arq("fluxo_cic.txt");
 	
	int id_max;		arq >> id_max;
	// Debug
	getline(arq, name);

	getline(arq, name);

	this->verts = id_max;
	this->node.resize(id_max + 1);
	

	int prev[id_max+1] {};	// fila para usar pra guardar pre-requisitos
	int i, k;
	do{
		set <int> redundancy;
		i = k = 0;
		arq >> id >> code >> rec_credits >> hardness >> name;

		if(id > id_max || id < 1)		return;	// Arquivo zuado :/ .

		int cost = rec_credits * hardness;
		node[id] = new Nodes(code);	this->node[id]->set_name(name);	this->node[id]->set_cost(cost);
		// Vai pegar os pre-requisitos
		do{
			arq >> code;
			if(code != 0 && code != -1){
				prev[i] = code;
				if(redundancy.count(code) == 0){	// Se nao eh redundante adicionar esse pre-req, add
					redundancy.insert(code);
// zoado			this->node[code]->plus_out(1);	// +1 mateira que libera
					this->node[id]->plus_in(1);		// +1 pre-requisito
					i++;
				}
			}
			// -1 eh separador de requisitos
		}while(code != 0);
		
		for(int j=0; j < i; j++){
			this->node[prev[j]]->insert_qtd_nxt_pro(new Nodes(this->node[id], this->node[id]->get_cost()));		
			this->node[prev[j]]->set_out(this->node[prev[j]]->get_qtd_nxt());
		}

		switch (id){case 5: case 9: case 14:
					case 19: case 24: case 29:
					case 32: case 34:	getline(arq,name);		// Quebra de linha entre os semestres
		}
				
	}while(id != id_max);
	arq.close();
}


Graph :: Graph(string, string){
	vector <string> friend_list;	/// Lista auxiliar p/ contruir a list de adjacencia APOS ler todo o arq
	friend_list.resize(1);
	this->node.resize(1);	// Assim os node se iniciam pelo numero 1, posicao 1
	///Abrir o arq
	ifstream arq;
	arq.open("amigos_tag20172.txt");
//	arq.open("minigrafo");
	int aux, aux2;
	string line, s_aux;
	int index, j;
	/// Ler os dados e criar o grafo
	for(index=1; arq.eof() == false; index++){
		///Ler a line
		getline(arq, line); line += '\n';	// Marca o termino da line. Serah util ao final
		///Pegar o ID do animal	
		for(j=0, aux=0; line[j] <= '9' && line[j] >= '0'; j++)
			aux = aux*10 + (line[j] - 48);
		j++;				// Para  << passar pela virgula
		this->insert(new Nodes(aux));		// Obviamente, aux == index
/*//////////////////////////////////////////////////*/
		for(	 aux=0; line[j] != ',' ; j++)		// A matricula termina com virgula
			aux = aux*10 + (line[j] - 48);
		j++;				// Ultima virgula antes do name
		this->node[index]->set_matricula(aux);
/*//////////////////////////////////////////////////*/
		line.erase(0, j);				/// Apaga o que vem ANTES do Nome
		s_aux = line;
		for(aux=0; s_aux[aux] != ',' &&  s_aux[aux] != '\n';aux++);// Conta quantos caracteres vem ANTES da primeira virgula
//		##############################3			
//		##############################3			
//		##############################3			
//		##############################3			
		s_aux.erase(0, aux+1);				// Deixa entao apenas a list dos nxts (apaga a primeira virgula tbm)
		

		if(s_aux.length() == 0)
			friend_list.push_back("\n");		
		else{
			line.erase(aux);					//  Deixa apenas o name da pessoa (apaga o que vem DEPOIS)
			friend_list.push_back(s_aux);
		}
		this->node[index]->set_qtd_nxt(0);			// Serao contados a seguir p/ facilitar montar o grafo


		
		line += "\n"; 
		this->node[index]->set_name(line);
	}

								
	for(int i =1, count=0; i < index; i++, count=0){		// Obs: redundante; deveria ter salvo os nxts em vectors
		char c;
		for(j=0; (c = friend_list[i][j]) != '\n'; j++){
			if(c == ',')	count++;
			cout << c;
		}
		cout << endl;
		if(j == 0)			this->node[i]->set_qtd_nxt(0);
		else if(j == 1) 	this->node[i]->set_qtd_nxt(1);
		else				this->node[i]->set_qtd_nxt(count+1);
		cout << "AMIGOS DE " << this->node[i]->get_key() << ": " << this->node[i]->get_qtd_nxt() << endl;
	}
	/// Efetivamente vai criar a list de adjacencia
	char c;
	for(int i =1; i < index; i++){
//		this->node[i]->set_qtd_nxt(0);	// Inicializa o contador de qtd_nxt; BUG; jah estah certo
		cout << "Inserindo nxts de " << i  << " (Graph(string))"<< endl;
		for(j=0; (c = friend_list[i][j]) != '\n'; ){
			aux = 0;					// Vai armazenas a key do proximo nxt
			while(c >= '0' && c <= '9'){
				aux = aux*10 + (c - 48);
				j++;
				c = friend_list[i][j];
			}
			cout << "	Inserindo " << aux << endl;
			this->node[i]->insere_pre_calculado(this->node[aux]);	// Insere nxt de node[i] a partir de this->node[aux]; Conta cada insercao
//			node[i]->get_qtd_nxt()--;									// Decrementa a conta extra feita acima
			cout << "Soma qtd_nxts " << this->node[i]->get_qtd_nxt() << endl;
			j++;	// Pula a virgula
		}
	}
	arq.close();
}



//*/

Graph :: ~Graph(){
	this->reset();
}
void Graph :: mk_bi(){
	int i,j;
	Nodes * aux;
	for(i = 1; i <= this->verts; i++){	// Passar em todos os vertices
		aux = this->node[i];			// Vertice a ser varrido
		for(j = aux->get_qtd_nxt()+1; j > 0; j--){//OBS: ||| >= ||| Para cada amigo, faça
			this->node[aux->get_key()]->insert_qtd_nxt_pro(this->node[i]);
			aux = aux->get_nxt();
		}
	}
	// Atualizar os valores nas lists de adj
	for(j = 1; j <= this->verts; j++){//OBS: ||| >= ||| Para cada amigo, faça
		aux = this->node[j]->get_nxt();			// Vertice "raiz" ja esta com nº qtd_nxt atualizados
		while(aux != NULL){
			if(aux->get_qtd_nxt() != this->node[aux->get_key()]->get_qtd_nxt())
				aux->set_qtd_nxt(this->node[aux->get_key()]->get_qtd_nxt());
			aux = aux->get_nxt();
		}
	}
//	*/
	aux = NULL;
}


void Graph :: reset(){
	for(int i=1; i <= this->verts; i++){
		exclude_list(i);
	}
	this->node.resize(0);
	this->verts = 0;	this->edge=0;
}

void Graph :: insert(Nodes * novo){
	node.push_back(novo);
	this->verts = this->verts + 1;	//Novo vertice
}

inline void Graph :: insert_qtd_nxt(int origem, Nodes* no, int cost){
	this->insert_qtd_nxt(origem, no, cost);
}

vector<int> Graph ::  list(int vertice){
	vector<int> list;
	Nodes* pivo = node[vertice-1]->get_nxt();
	while(pivo != NULL){
		list.push_back(pivo->get_key());
		pivo = pivo->get_nxt();
	}
	delete(pivo);			/// Do I have to do this?
	return list;
}

void Graph :: show_verts(){
	for(int i=1; i <= this->verts;i++){
		cout << "****** i == " << i << " ******" << endl; 
		this->node[i]->mostra_no();		
	}
}

void Graph :: show(){
	cout << "Mostrando grafo: " << endl;
	for(int i=1; i <= this->verts;i++){
		cout << "****** i == " << i << " ******" << endl; 
		this->node[i]->mostra_lista();
	}
}

void Graph :: show_nodes(){
	cout << "Mostrando grafo: " << endl;
	for(int i=1; i <= this->verts;i++){
		cout << "****** i == " << i << " ******" << endl; 
		this->node[i]->mostra_no();
	}
}

/*static*/
