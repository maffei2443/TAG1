/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/

#ifndef _GRAPHOP_HPP_
#define _GRAPHOP_HPP_

#include "nodes.hpp"
#include "graph.hpp"
#include "critcpath.hpp"
#include <set>
#include <utility>
#include <queue>
#include <map>

using namespace std;
// Suporte
void mostra_set(set <int> to_show);
// Profundidade
void dfs_caminho(Graph *, Nodes *);
void dfs_caminho(Graph *, Nodes *, int tabs);
void dfs_caminho_estavel(Graph *, Nodes *, set<int>& visit, int tabs);
void dfs_caminho_instavel(Graph *, Nodes *, int tabs);
void dfs_pure(Graph *, Nodes *, set<int>& visitados);

// Largura
void bfs_caminho_instavel_debug(Graph * G, Nodes * no);
void bfs_caminho_instavel(Graph * G, Nodes * no);
void bfs_caminho(Graph * G, Nodes * no);

// Outros
void bk(Graph * G, int const& min, set<int>clique, set<int>candidatos, set<int>falhos);
void bk(Graph *, int);
void mostra_por_nota(Graph *);

void clicks_maxi_node_debug(Graph* G, Nodes * no, set<int> el_clique, set<int> candidatos, set<int>& inutil);   // Requer ainda um parametro "secreto", que estah no proprio grafo
void clicks_maxi_node(Graph* G, Nodes * no, set<int> el_clique, set<int> candidatos, set<int>& inutil);   // Requer ainda um parametro "secreto", que estah no proprio grafo
void clicks_maxi_node(Graph * G, Nodes * no, set<int>candidatos);

bool big_keyy(Nodes * a, Nodes * b);
bool small_keyy(Nodes * a, Nodes * b);
bool comp(Nodes * a, Nodes * b);
bool comp_r(Nodes * a, Nodes * b);

void sort_reach(Graph* G); 		// Ordena do menor ateh maior quanditade de qtd_nxt
void sort_reach_r(Graph* G); // Ordena do maior ateh menor quanditade de qtd_nxt
void sort_keyy(Graph* G); // Ordena do maior ateh menor quanditade de qtd_nxt

// Ordenacao topologica BEM especifica
vector<int> sort_tp(Graph * G);

// Caminho critico

Critcpath true_dfs_cp(Graph * G, Nodes * no, map <int, int> code_index);
Critcpath dfs_cp(Graph * G, Nodes * no);

#endif