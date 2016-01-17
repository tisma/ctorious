#include <iostream>
#include <algorithm>
#include <cstring>

int main(int argc, char* argv[])
{
	std::string str = "HELLO WORLD";

	std::cout << "Before: " << str << std::endl;

	std::transform(str.begin(), str.end(), str.begin(), tolower);

	std::cout << "After: " << str << std::endl;

	return 0;
}

