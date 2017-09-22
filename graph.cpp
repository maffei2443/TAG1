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
	if(excluir->vizinho != NULL)
		exclui_aninhado(excluir->vizinho);
	delete(excluir);
}

void Graph :: mostra_set(set <int> to_show){
    set<int> :: iterator iter;
    for(iter = to_show.begin(); iter != to_show.end(); iter++)
        cout << (*iter) << " ";
    cout << '\n';
}

// public
Graph :: Graph() : edge(0), verts(0){node.resize(1);}

//*

Graph :: Graph(string, string){
	vector <string> friend_list;	/// Lista auxiliar p/ contruir a list de adjacencia APOS ler todo o arquivo
	friend_list.resize(1);
	this->node.resize(1);	// Assim os node se iniciam pelo numero 1, posicao 1
	///Abrir o arquivo
	ifstream arquivo;
	arquivo.open("amigos");
//	arquivo.open("minigrafo");
	int aux, aux2;
	string line, s_aux;
	int index, j;
	/// Ler os dados e criar o grafo
	for(index=1; arquivo.eof() == false; index++){
		///Ler a line
		getline(arquivo, line); line += '\n';	// Marca o termino da line. Serah util ao final
		///Pegar o ID do animal	
		for(j=0, aux=0; line[j] <= '9' && line[j] >= '0'; j++)
			aux = aux*10 + (line[j] - 48);
		j++;				// Para  << passar pela virgula
		this->insert(new Nodes(aux));		// Obviamente, aux == index
/*//////////////////////////////////////////////////*/
		for(	 aux=0; line[j] != ',' ; j++)		// A matricula termina com virgula
			aux = aux*10 + (line[j] - 48);
		j++;				// Ultima virgula antes do nome
		this->node[index]->matricula = aux;
/*//////////////////////////////////////////////////*/
		line.erase(0, j);				/// Apaga o que vem ANTES do Nome
		s_aux = line;
		for(aux=0; s_aux[aux] != ',' &&  s_aux[aux] != '\n';aux++);// Conta quantos caracteres vem ANTES da primeira virgula
//		##############################3			
//		##############################3			
//		##############################3			
//		##############################3			
		s_aux.erase(0, aux+1);				// Deixa entao apenas a list dos vizinhos (apaga a primeira virgula tbm)
		

		if(s_aux.length() == 0)
			friend_list.push_back("\n");		
		else{
			line.erase(aux);					//  Deixa apenas o nome da pessoa (apaga o que vem DEPOIS)
			friend_list.push_back(s_aux);
		}
		this->node[index]->amigos = 0;			// Serao contados a seguir p/ facilitar montar o grafo


		
		line += "\n"; 
		this->node[index]->nome = line;
	}

								
	for(int i =1, count=0; i < index; i++, count=0){		// Obs: redundante; deveria ter salvo os vizinhos em vectors
		char c;
		for(j=0; (c = friend_list[i][j]) != '\n'; j++){
			if(c == ',')	count++;
			cout << c;
		}
		cout << endl;
		if(j == 0)			this->node[i]->amigos = 0;
		else if(j == 1) 	this->node[i]->amigos = 1;
		else				this->node[i]->amigos = count+1;
		cout << "AMIGOS DE " << this->node[i]->chave << ": " << this->node[i]->amigos << endl;
	}
	/// Efetivamente vai criar a list de adjacencia
	char c;
	for(int i =1; i < index; i++){
		this->node[i]->amigos = 0;	// Inicializa o contador de amigos
		cout << "Inserindo vizinhos de " << i  << " (Graph(string))"<< endl;
		for(j=0; (c = friend_list[i][j]) != '\n'; ){
			aux = 0;					// Vai armazenas a chave do proximo vizinho
			while(c >= '0' && c <= '9'){
				aux = aux*10 + (c - 48);
				j++;
				c = friend_list[i][j];
			}
			cout << "	Inserindo " << aux << endl;
			this->node[i]->insere_pre_calculado(this->node[aux]);	// Insere vizinho de node[i] a partir de this->node[aux]; Conta cada insercao
//			node[i]->amigos--;									// Decrementa a conta extra feita acima
			cout << "Soma amigoss " << this->node[i]->amigos << endl;
			j++;	// Pula a virgula
		}
	}
}

Graph :: Graph(string){
	vector <string> friend_list;	/// Lista auxiliar p/ contruir a list de adjacencia APOS ler todo o arquivo
	friend_list.resize(1);
	this->node.resize(1);	// Assim os node se iniciam pelo numero 1, posicao 1
	ifstream arquivo;
	arquivo.open("amigos_tag20172.txt");
//	arquivo.open("minigrafo");
	int aux, aux2;
	string line, s_aux;
	int index, j;			// Bbs: 'j' e 'index' sao variaveis >essenciais <
	/// Ler os dados e criar o grafo
	for(index=1; arquivo.eof() == false; index++){
		///Ler a line
		getline(arquivo, line); line += '\n';	// Marca o termino da line. Serah util ao final
		///Pegar o ID do animal	
		for(j=0, aux=0; line[j] <= '9' && line[j] >= '0'; j++)
			aux = aux*10 + (line[j] - 48);
		j++;				// Para  << passar pela virgula
		this->insert(new Nodes(aux));		// Obviamente, aux == index
		this->node[index]->amigos = 0;			// Serao contados QUANDO for mantada a list de adjacencia
/*//////////////////////////////////////////////////*/
		for(	 aux=0; line[j] != ',' ; j++)		// A matricula termina com virgula
			aux = aux*10 + (line[j] - 48);
		j++;				// Ultima virgula antes do nome
		this->node[index]->matricula = aux;
/*//////////////////////////////////////////////////*/
		line.erase(0, j);				/// Apaga o que vem ANTES do Nome
		s_aux = line;
		for(aux=0; s_aux[aux] != ',' &&  s_aux[aux] != '\n';aux++);// Conta quantos caracteres vem ANTES da primeira virgula
		s_aux.erase(0, aux+1);				// Deixa entao apenas a list dos vizinhos (apaga a primeira virgula tbm)
		
		if(s_aux.length() == 0)
			friend_list.push_back("\n");		
		else{
			line.erase(aux);					//  Deixa apenas o nome da pessoa (apaga o que vem DEPOIS)
			s_aux = s_aux+ '\n';
			friend_list.push_back(s_aux);
		}
		
		this->node[index]->nome = line;
		line += "\n"; 
	}
//	cout << "Contador de amigos. " << endl;
	for(int i =1, count=0; i < index; i++, count=0){		// Obs: redundante; deveria ter salvo os vizinhos em vectors
		char c;
		for(j=0; (c = friend_list[i][j]) != '\n'; j++)
			if(c == ',')	count++;		
		if(j == 0 || j == 1)this->node[i]->amigos = j;
		else				this->node[i]->amigos = count+1;
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
			this->node[i]->insere_pre_calculado(this->node[aux]);	// Insere vizinho de node[i] a partir de this->node[aux]; JAH CONTA OS AMIGOS!!!
		}
	}
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
		for(j = aux->amigos+1; j > 0; j--){//OBS: ||| >= ||| Para cada amigo, faça
			this->node[aux->chave]->insert_nxt_pro(this->node[i]);
			aux = aux->vizinho;
		}
	}
	// Atualizar os valores nas lists de adj
	for(j = 1; j <= this->verts; j++){//OBS: ||| >= ||| Para cada amigo, faça
		aux = this->node[j]->vizinho;			// Vertice "raiz" ja esta com nº amigos atualizados
		while(aux != NULL){
			if(aux->amigos != this->node[aux->chave]->amigos)
				aux->amigos = this->node[aux->chave]->amigos;
			aux = aux->vizinho;
		}
	}
//	*/
	aux = NULL;
}

void inline Graph :: exclude_list(int index){
	exclui_aninhado(node[index]);
}

void Graph :: reset(){
	for(int i=1; i <= this->verts; i++)
		exclude_list(i);
	this->node.resize(0);
	this->verts = 0;	this->edge=0;
}

void Graph :: insert(Nodes * novo){
	node.push_back(novo);
	this->verts = this->verts + 1;	//Novo vertice
}

inline void Graph :: insert_nxt(int origem, Nodes* no, int custo){
	this->insert_nxt(origem, no, custo);
}

vector<int> Graph ::  list(int vertice){
	vector<int> list;
	Nodes* pivo = node[vertice-1]->vizinho;
	while(pivo != NULL){
		list.push_back(pivo->chave);
		pivo = pivo->vizinho;
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
