#include <iostream>
using namespace std;

template <class T>
class Foo{
	public:
	T el;
		Foo(){el = 99; cout << el << endl;}
		Foo(int a){el = a; cout << el << endl;}
		void all(){cout<<"All!!!"<<el<<"\n";}
};

int main(){
	Foo<int> foo;
	Foo<int> * foo2 = new Foo<int>(898);
	foo.all();
	return 0;
}