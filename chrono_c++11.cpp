#include <iostream>
#include <chrono>

using namespace std;

int main() {
	cout << "system clock" << endl;
	cout << chrono::system_clock::period::num << endl;
	cout << chrono::system_clock::period::den << endl;
	cout << "steady = " << boolalpha << chrono::system_clock::is_steady << endl << endl;

	cout << "high_resolution_clock" << endl;
	cout << chrono::high_resolution_clock::period::num << endl;
	cout << chrono::high_resolution_clock::period::den << endl;
	cout << "steady = " << boolalpha << chrono::high_resolution_clock::is_steady << endl << endl;

	cout << "steady_clock" << endl;
	cout << chrono::steady_clock::period::num << endl;
	cout << chrono::steady_clock::period::den << endl;
	cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;

	auto start = chrono::steady_clock::now();

	volatile int x = 0, y = 0, z = 0;
	for (volatile int i = 0; i < 10000; i++) {
		for (volatile int j = 0; j < 10000; j++) {
			x = y - 1;
			y = z + 1;
			z = x - 2;
		}
	}

	auto end = chrono::steady_clock::now();

	auto diff = end - start;

	cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;

	return 0;
}