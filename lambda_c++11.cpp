#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print_vector(const vector<int>& v) {
	for (auto& it : v) {
		cout << it << ' ';
	}
	cout << endl;
}

int main() {
	const int N = 10;
	vector<int> v(N);
	
	for (int i = N - 1, j = 0; i >= 0; i--, j++) {
		v[j] = i + 1;
	}

	print_vector(v);

	sort(v.begin(), v.end(), [](int i, int j) -> bool { return (i < j); });

	print_vector(v);

	return 0;
}