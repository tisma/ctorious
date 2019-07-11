#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool HasPairWithSum(const vector<int> &data, const int sum) {
	unordered_set<int> complements;
	for (auto value : data) {
		if (complements.find(value) != complements.end()) {
			return true;
		}
		complements.insert(sum - value);
	}
	return false;
}

int main(int argc, char* argv[]) {
	vector<int> v1 = { 1, 2, 3, 9 }, v2 = { 1, 2, 4, 4 };
	cout << HasPairWithSum(v1, 8) << endl;
	cout << HasPairWithSum(v2, 8) << endl;
	return 0;
}

