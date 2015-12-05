#include <stdio.h>
#include <stdlib.h>

int is_multiple_of_three(int n) {
	int odd_bits_cnt = 0;
	int even_bits_cnt = 0;

	if (n < 0) n = -n;
	if (n == 0) return 1;
	if (n == 1) return 0;

	while (n) {
		if (n & 0x1) {
			odd_bits_cnt++;
		}

		n >>= 1;

		if (n & 0x1) {
			even_bits_cnt++;
		}

		n >>= 1;
	}

	return is_multiple_of_three(abs(odd_bits_cnt - even_bits_cnt));
}

int main(int argc, char** argv) {

	printf("Enter a number to test is it multiple of 3: ");
	int n = 0;
	scanf("%d", &n);
	printf(is_multiple_of_three(n) ? "true\n" : "false\n");

	return 0;
}