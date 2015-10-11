#include <stdio.h>
#include <stdbool.h>

bool is_power_of_two(unsigned int n) {
	return n && !(n & (n - 1));
}

unsigned int next_power_of_two1(unsigned int n) {
	if (n && !(n & (n - 1))) {
		return n;
	}

	unsigned int count = 0;
	while (n != 0) {
		n >>= 1;
		count++;
	}

	return 1 << count;
}

unsigned int next_power_of_two2(unsigned int n) {
	if (n && !(n & (n - 1))) {
		return n;
	}
	
	unsigned int p = 1;
	
	while (p < n) {
		p <<= 1;
	}
	return p;
}

unsigned int next_power_of_two3(unsigned int n) {
	n = n - 1;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	return n + 1;
}

int main(int argc, char** argv) {
	unsigned int x[] = { 1, 17, 32, 43, 121 };
	int i;
	printf("sizeof int: %ld\n", sizeof(unsigned int));
	for (i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
		printf(is_power_of_two(x[i]) ? "true\n" : "false\n");
		printf("%d -> %d\n", x[i], next_power_of_two1(x[i]));
		printf("%d -> %d\n", x[i], next_power_of_two2(x[i]));
		printf("%d -> %d\n", x[i], next_power_of_two3(x[i]));
	}
	printf("\n");
	return 0;
}