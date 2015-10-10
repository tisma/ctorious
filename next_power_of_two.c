#include <stdio.h>

unsigned int next_power_of_two(unsigned int n) {
	if (n && !(n & (n - 1))) {
		return n;
	}
	
	unsigned int p = 1;
	
	while (p < n) {
		p <<= 1;
	}
	return p;
}

unsigned int next_power_of_two2(unsigned int n) {
	n = n - 1;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	return n + 1;
}

int main(int argc, char** argv) {
	unsigned int x[] = { 1, 17, 32 };
	int i;
	printf("sizeof int: %ld\n", sizeof(unsigned int));
	for (i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
		printf("%d -> %d\n", x[i], next_power_of_two(x[i]));
		printf("%d -> %d\n", x[i], next_power_of_two2(x[i]));
	}
	printf("\n");
	return 0;
}