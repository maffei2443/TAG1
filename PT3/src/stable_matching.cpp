#include "graph.hpp"
#include <iostream>
#include <fstream>
using namespace std;

void le(){
	ifstream fp("entradaProj3TAG.txt");
	string oo;
	for(int i=0; i < 100; i++){	
		getline(fp, oo);
		cout << oo << endl;
	}
	fp.close(); 
}

int main(){
	cout << "Hello World" << endl;
	le();
	cout << "Hello World" << endl;
	return 0;
}