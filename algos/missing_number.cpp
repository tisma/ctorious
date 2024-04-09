#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

int smallestMissing(const std::vector<int>& vec) {
	std::unordered_set<int> nums(vec.begin(), vec.end());

	int smallest = 1;
	while (nums.count(smallest)) {
		smallest++;
	}

	return smallest;
}

int smallestMissingSorted(const std::vector<int>& vec) {
	int left = 0;
	int right = vec.size() - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (vec[mid] == mid + 1 or vec[mid] <= 0) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	return left + 1;
}

int main() {
	std::vector<int> vec = { 4, 5, -1, 1 };
	std::cout << smallestMissing(vec) << '\n';
	std::sort(vec.begin(), vec.end());
	std::cout << smallestMissingSorted(vec) << '\n';
	return 0;
}
