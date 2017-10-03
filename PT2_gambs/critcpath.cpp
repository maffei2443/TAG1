#include "critcpath.hpp"
using namespace std;

void Criticpath :: addnodes(Nodes *n){
        keys.push(n->get_key());
        accumulatedcost+=n->get_cost();
        sizequeue++;
}

Critcpath :: Critcpath(Nodes *n){
//      cout << "itsleaf" << endl;
        keys.push(n->get_key());
        accumulatedcost = n->get_cost();
        sizequeue = 1;
    }
Critcpath :: Critcpath(){
//      cout << "wat" << endl;
        accumulatedcost=0;
        sizequeue=0;
}