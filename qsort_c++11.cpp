#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main() {

	vector<int> vec(10000);
	generate(vec.begin(), vec.end(), rand);

	sort(vec.begin(), vec.end(), [](int a, int b) -> bool { return a > b; });

	for (auto &a : vec) {
		cout << a << " ";
	}
	cout << endl;

	return 0;
}