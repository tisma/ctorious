#include <iostream>

using namespace std;

class X {

public:
	virtual void func()  { cout << "Called and n = " << n << endl; }
	virtual void func2() { cout << "Second function called " << endl; }
	int n;

};

int main(int argc, char const *argv[])
{
	X* obj = new X();
	obj->n = 10;

	int* vptr = *(int**)obj;

	((void(*)()) vptr[0])();

	return 0;
}

