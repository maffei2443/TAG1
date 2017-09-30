#include "graph.hpp"
#include "nodes.hpp"
#include <queue>

#include <map>
#include <utility>
using namespace std;
vector<int> sort_tp(Graph * G){
	int verts = G->get_verts();	

	map <int, int> code_index;
	queue <int> nxt_sorted;		// Proximos a SEREM INSERIDOS, de qqer forma, na ordenacao topologica.
	vector<int>	sorted;			// Uma possivel ordenacao topologica
	vector<bool> inserted(verts+3, false);	// Inseridos na ordem

	// Coloca todos os de grau de chegada zero em uma fila.
	for(int i = 1; i < verts+1; i++){
		// Criando o mapa para busca mais eficiente depois.
		code_index.insert(code_index.begin(), pair<int,int>(G->get_node(i)->get_key(), i));	// Necesario; faz o map.
		if(G->get_node(i)->get_in() == 0){
//			cout << "Insercao primaria: " << i << endl;
			nxt_sorted.push(i);
		}
	}
	queue<int> to_decrease_by_one;
	for(int id; nxt_sorted.empty() == false;){
//		cout << "Proximo nivel\n\n\n";
		for(int i = 0, j = nxt_sorted.size(); i < j; i++){	// Esvazia a parte da pilha que foi enviada para cah.
			id = nxt_sorted.front();	// 'id' contem a posicao no vetor jah.
			nxt_sorted.pop();
//			cout << "id autal : " << id << endl;
			// POSSIVELMENTE enche novamente a pilha
			Nodes * pivot;
			// Para cada vertice, verifica se seu "sucessores" podem seradicionados aa fila
			for(pivot = G->get_node(id)->get_nxt(); pivot != NULL; ){
				
				to_decrease_by_one.push(code_index.find(pivot->get_key())->second);	// Lista das materias a se decrementar o grau de incidencia.				
//				cout << "Diminuir o grau de " << code_index.find(pivot->get_key())->second << endl;
/*				if(pivot->get_in() < 2){
					int nxt = code_index.find(pivot->get_key())->second;
					if(inserted[nxt] != true){// Nao foi inserido, entra na fila de insercao.
						nxt_sorted.push(nxt);
						cout << "Inseriu " << nxt << " na fila\n";
					}	
					else
						cout << "Nao inseriu " << nxt << " na fila\n";
				}
*/

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
/*				cout << "Diminuiu o grau de " << code_index.find(G->get_node(aux)->get_key())->second;
				cout << " de " << in_degree +1 << " para " << in_degree << endl;
				cout << "Bugou?? " << in_degree << endl;
				if(in_degree == 0)	cout << "INSERE, PORRA, A MERDA DO " << in_degree << " NA FILA\n";
				if(in_degree < 1)	cout << "INSERE, PORRA, A MERDA DO " << in_degree << " NA FILA\n";
*/				if(in_degree < 1){		// Se fez todos os pre-erq, pode entrar na ordem
					int tmp = code_index.find(G->get_node(aux)->get_key())->second;
					if(inserted[tmp] == false){ // Se ainda nao foi colocado na lista ordenada, eh colocado
						nxt_sorted.push(code_index.find(G->get_node(aux)->get_key())->second);
//						cout << "Inseriu na fila: " << code_index.find(G->get_node(aux)->get_key())->second << endl;
					}
					else;
//						cout << "Nao inseriu na fila:" << code_index.find(G->get_node(aux)->get_key())->second << endl;
				}
				else;
//					cout << "Nao inseriu na fila:" << code_index.find(G->get_node(aux)->get_key())->second << endl;
			}
//			cout << "\nInseriu na ordem topologica: " << id << endl << endl;
			sorted.push_back(id);	// Lista com ordenacao tpologica valida.
			inserted[id] = true;
		}
	}
	int i=0;
	for(vector<int>::iterator it = sorted.begin(); it != sorted.end(); it++, i++)
		sorted[i] = G->get_node(*it)->get_key();
	return sorted;	
}

int main(){
//	Graph * neo = new Graph(9);
	Graph * G = new Graph(9);

	map <int, int> code_index;
	for(int i = 1; i < G->get_verts()+1; i++){
		// Criando o mapa para busca mais eficiente depois.
		code_index.insert(code_index.begin(), pair<int,int>(G->get_node(i)->get_key(), i));
	}
	vector<int> sort = sort_tp(G);

//	G->show();
	
	vector<int>::iterator it = sort.begin();
	int i;
	for(i = 0; it != sort.end(); it++, i++)
		cout << "Posicao: " << i+1 << " | Code == " << sort[i] << " | Name: " << G->get_node(code_index.find(sort[i])->second)->get_name() << endl;
	return 0;
}