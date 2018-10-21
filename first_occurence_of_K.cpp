/**
 * Find fist occurence of number K in a sorted vector.
 *
 */

#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <string>

using namespace std;

int find_first_of_K(const vector<int>& vec, int K) {
	int left = 0;
	int right = vec.size() - 1;
	int result = -1;

	// binary search
	while (left <= right) {
		// this prevents overflow which might happend
		// in case: int mid = (left + right) / 2;
		int mid = left + ((right - left)) / 2;
		
		if (vec[mid] > K) {
			right = mid - 1;
		} else if (vec[mid] == K) {
			result = mid;
			right = mid - 1;
		} else {
			left = mid + 1;
		}
		
	}

	return result;
}

void print_vector(const vector<int>& vec) {
	for (const auto& a : vec) {
		cout << a << ' ';
	}
	cout << endl;
}

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cerr << "usage: " << argv[0] << " <size_of_vector> <K>" << endl;
		return -1;
	}

	int N = stoi(argv[1]);
	int K = stoi(argv[2]);

	random_device rd;
	default_random_engine dre(rd());
	uniform_int_distribution<int> uid(0, N);

	vector<int> vec(N);
	generate(vec.begin(), vec.end(), [&]() { return uid(dre); });

	sort(vec.begin(), vec.end());

	print_vector(vec);

	cout << endl;

	cout << "First occurence of " << K << ": " << find_first_of_K(vec, K) << endl;

	return 0;
}
