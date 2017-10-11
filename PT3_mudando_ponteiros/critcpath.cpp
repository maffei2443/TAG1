#include "critcpath.hpp"
using namespace std;

void Critcpath :: addnodes(Nodes *n){
        keys.push(n->get_key());
        names.push(n->get_name());
        accumulatedcost += n->get_cost();
        sizequeue++;
}

Critcpath :: Critcpath(Nodes *n){
        keys.push(n->get_key());
        names.push(n->get_name());
        accumulatedcost = n->get_cost();
        sizequeue = 1;
    }
Critcpath :: Critcpath(){
        accumulatedcost = 0;
        sizequeue = 0;
}