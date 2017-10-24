/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/



#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include <vector>
using namespace std;

class Queue{
private:
	int size;
	vector <int> data;
public:
	Queue();
	void queue_up(int);
	int queue_out();
};

#endif