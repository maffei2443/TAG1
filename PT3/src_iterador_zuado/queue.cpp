/*
Autores:
	Arthur da Silveira Couto - 160002575
	Leonardo Maffei da Silva - 160033811
*/

#include "queue.hpp"

inline Queue::Queue(){
	data.resize((size=0));
}

void Queue::queue_up(int newdata){
	size++;
	data.resize(size);
	data[size-1]=newdata;
}

int Queue::queue_out(){
	if (size==0) return 0;
	size--;
	int aux=data[0];
	for (int i=0; i<size; i++)
		data[i]=data[i+1];
	data.resize(size);
	return aux;
}