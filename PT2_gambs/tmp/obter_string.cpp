#include <iostream>
#include <fstream>
using namespace std;

int main(){
	ifstream arq("txt.txt");
	string oi;
	int i, j;
	arq >> i >> j;
	getline(arq, oi);
	
	cout << i << j;
	cout << oi << endl;
	return 0;
}