#include <array>
#include <iostream>

template<typename T, std::size_t N>
typename std::enable_if<N < 128 && std::is_integral<T>::value, void>::type insertion_sort(std::array<T, N>& array) {
	for (std::size_t i = 0; i < N; i++) {
		for (std::size_t j = i; j > 0 && array[j] < array[j-1]; j--) {
			std::swap(array[j], array[j-1]);
		}
	}
}

int main() {
	std::array<int, 10> arr = { 2, 3, -1, 0, 12, -4, -9, 6, 7, 1 };
	insertion_sort(arr);
	for (std::size_t i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	return 0;
}


