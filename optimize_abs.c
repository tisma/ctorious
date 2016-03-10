#include <stdio.h>

static inline int abs(int num)
{
	int tmp = num;

	num = num >> 31;
	tmp = tmp ^ num;
	tmp -= num;

	return tmp;
}

int main(int argc, char* argv[])
{
	int n;
	scanf("%d", &n);
	printf("%d\n", abs(n));

	return 0;
}

