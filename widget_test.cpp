#include "widget.h"
#include <vector>

int main() {
	std::vector<Widget> v{};
	v.reserve(5);

	printf("- push_back\n");

	v.push_back(Widget{3});

	printf("- emplace_back\n");

	v.emplace_back(Widget{3});

	printf("- emplace_back\n");

	v.emplace_back(3); // construct object in place

	printf("--------\n");

	return 0;
}

