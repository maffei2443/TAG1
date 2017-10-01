#ifndef _CRITC_HPP_
#define _CRITC_HPP_
#include <queue>

class Critpath{
public:
    queue<int> keys;
    int sizequeue;
    int accumulatedcost;

    void addnodes(Nodes *n);
	Critpath(Nodes *n);
	Critpath();
};
