#include <vector>
#include <iostream>

void print_vec(const std::vector<int>& vec) {
	for (const auto& v : vec) {
		std::cout << v << ' ';
	}
	std::cout << '\n';
}

int search(const std::vector<int>& vec, int target) {
	int left = 0;
	int right = vec.size() - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (target == vec[mid]) {
			return mid;
		}

		if (vec[left] < vec[mid]) {
			if (vec[left] <= target && target < vec[mid]) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		} else if (vec[left] > vec[mid]) {
			if (vec[mid] < target && target <= vec[right]) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		} else {
			left++;
		}
	}

	return -1;
}

int main() {
	std::vector<int> vec = { 2, 2, 2, 4, 5, 6, 53, 0, 1, 2 };
	print_vec(vec);
	int target;
	std::cin >> target;

	int index = search(vec, target);

	std::cout << "element index: " << index << '\n';

	return 0;
}

