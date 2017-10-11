#include "graphop.hpp"
#include <set>
#include <queue>
#include <iostream>
#include <algorithm>
#define cls cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

using namespace std;


int main(){
    Graph * G = new Graph(9);
    for(int i = 1; i < 36; i++){
        cout << "Inicio em i : " << i << endl;
        Critpath haha = dfs_cp(G, G->get_node(i));
        int l = haha.sizequeue;
        for(int j = 0; j < l; j++){
            cout  << haha.keys.front() << endl;
            haha.keys.pop();
        }
        cout << "Custo do caminho: " << haha.accumulatedcost;
        cls;
    }

    return 0;
}