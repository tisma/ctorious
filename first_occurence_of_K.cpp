/**
 * Find fist occurence of number K in a sorted array.
 *
 */

#include <iostream>
#include <algorithm>
#include <random>
#include <array>
#include <string>

using namespace std;

const int N = 10;

int find_first_of_K(const array<int, N>& A, int K) {
	int left = 0;
	int right = A.size() - 1;
	int result = -1;

	while (left <= right) {
		
		int mid = left + ((right - left)) / 2;
		
		if (A[mid] > K) {
			right = mid - 1;
		} else if (A[mid] == K) {
			result = mid;
			right = mid - 1;
		} else {
			left = mid + 1;
		}
		
	}

	return result;
}

void print_array(const array<int, N> arr) {
	for (const auto& a : arr) {
		cout << a << ' ';
	}
	cout << endl;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "usage: " << argv[0] << " <K>" << endl;
		return -1;
	}

	int K = stoi(argv[1]);

	random_device rd;
	default_random_engine dre(rd());
	uniform_int_distribution<int> uid(0, N);

	array<int, N> arr;
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = uid(dre);
	}

	// print_array(arr);

	sort(arr.begin(), arr.end());

	print_array(arr);

	cout << endl;

	cout << "First occurence of " << K << ": " << find_first_of_K(arr, K) << endl;

	return 0;
}
