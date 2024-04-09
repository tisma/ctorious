#include <iostream>
#include <array>
#include <random>

void print_array(const std::array<int, 40>& arr) {
	for (int i : arr) {
		std::cout << i << ' ';
	}
	std::cout << '\n';
}

void insertion_sort(std::array<int, 40>& arr) {
	for (size_t i = 1; i < arr.size(); ++i) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

int main() {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random generator

    // Define the range for the random integers
    std::uniform_int_distribution<> dis(1, 100); // Random integers between 1 and 100

    // Create a std::array to hold the random integers
    std::array<int, 40> arr;

    // Populate the array with random integers
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = dis(gen); // Generate a random integer and assign it to the array
    }

    // Print the contents of the array
    std::cout << "Random array elements:" << std::endl;
    print_array(arr);

    std::cout << "Sorted array elements:" << std::endl;
    insertion_sort(arr);
    print_array(arr);

    return 0;
}

