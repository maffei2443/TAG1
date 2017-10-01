
#include "critcpath.hpp"

void Critic :: addnodes(Nodes *n){
        keys.push(n->get_key());
        accumulatedcost+=n->get_cost();
        sizequeue++;
}

Critpath :: Critpath(Nodes *n){
//      cout << "itsleaf" << endl;
        keys.push(n->get_key());
        accumulatedcost = n->get_cost();
        sizequeue = 1;
    }
Critpath :: Critpath(){
//      cout << "wat" << endl;
        accumulatedcost=0;
        sizequeue=0;
}