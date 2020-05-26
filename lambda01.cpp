#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>


int main() {
	using std::placeholders::_1;

	const std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	const auto val = std::count_if(v.begin(), v.end(),
				       std::bind(std::logical_and<bool>(),
				       std::bind(std::greater<int>(), _1, 2),
				       std::bind(std::less_equal<int>(), _1, 6)));

	std::cout << val << std::endl;

	const auto val2 = std::count_if(v.begin(), v.end(), [](int n) { return n > 2 && n <= 6; });
	std::cout << val2 << std::endl;

	return 0;
}

