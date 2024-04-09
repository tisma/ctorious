#include <iostream>
#include <vector>

int countRotations(std::vector<int>& vec) {
	int n = vec.size();
	int left = 0;
	int right = n - 1;

	while (left < right) {
		if (vec[left] <= vec[right]) {
			return left;
		}

		int mid = left + (right - left) / 2;
		int next = (mid + 1) % n;

		if (vec[mid] <= vec[(mid - 1 + n) % n] && vec[mid] <= vec[next]) {
			return mid;
		}

		if (vec[mid] <= vec[right]) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}

	return -1;
}

int main() {
	std::vector vec = { 4, 5, 6, 7, 0, 1, 2, 3 };
	std::cout << countRotations(vec) << '\n';
	return 0;
}
