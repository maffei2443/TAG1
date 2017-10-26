#include <deque>
#include <iostream>

int main(){
	std :: deque <int> foo;
	for(int i = 0; i < 4; i++)	foo.push_back(i);
	int i = 0;
	for(;foo.begin() != foo.end(); i++)
		foo.pop_front();
	std :: cout << i << std :: endl;
	return 0;
}