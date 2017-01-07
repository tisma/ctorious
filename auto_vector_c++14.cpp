#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

auto& add_one(auto& v) {
	for (auto& it : v) {
		it += 1;
	}
	return v;
}

void multiply_by_two(auto& v) {
	for (auto& it : v) {
		it *= 2;
	}
}

void print_vector(auto& v) {
	for (const auto& e : v) {
		cout << e << endl;
	}
	cout << endl;
}

int main() {
	vector<int> vec{ -1, 2, 3, 5 };
	multiply_by_two(add_one(vec));
	print_vector(vec);
	return 0;
}
