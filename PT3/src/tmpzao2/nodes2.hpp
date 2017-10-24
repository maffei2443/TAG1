#ifndef _NODES_HPP_
#define _NODES_HPP_
#include <deque>

using namespace std;
class Nodes{
private:
    int key;
    deque <Nodes*> nxt;     // The adjacency list
public:

    Nodes(int keyy) :key(keyy){}

    inline int get_key(){return key;}

    deque<Nodes*>::iterator get_nxt(){return nxt.begin();}
    deque<Nodes*>::iterator get_end(){return nxt.end();}    

    void set_nxt_front(Nodes * node){nxt.push_front(node);}
    void set_nxt_back(Nodes * node){nxt.push_back(node);}

};
#endif