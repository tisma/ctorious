#include <cstring>
#include <iostream>

struct S
{
	float f;
	char c;
	int i;
};

int main()
{
	S s1 = { 1.1f, 'a', 99 };
	S s2 = { 1.1f, 'a', 99 };

	bool bSame = memcmp(&s1, &s2, sizeof(S)) == 0;

	std::cout << bSame;
}