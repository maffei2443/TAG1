#ifndef _CRITCPATH_HPP_
#define _CRITCPATH_HPP_
#include <queue>
#include "nodes.hpp"
using namespace  std;


class Critcpath{
public:
    queue<int> keys;
    int sizequeue;
    int accumulatedcost;

    void addnodes(Nodes *n);
	Critcpath(Nodes *n);
	Critcpath();
};

#endif