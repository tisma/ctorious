#include <iostream>
#include <stdexcept>
#include <string_view>

void* operator new(std::size_t n) {
	std::cout << "new() " << n << " bytes\n";
	return malloc(n);
}

int main() {
	std::string_view str_view("abcdef");

	try {
		for (std::size_t i = 0; true; i++) {
			std::cout << i << ": " << str_view.at(i) << '\n';
		}
	} catch (const std::out_of_range& e) {
		std::cout << "Whooops. Index is out of range.\n";
		std::cout << e.what() << '\n';
	}

	return 0;
}

