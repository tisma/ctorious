#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	printf("Before\n");

	int i = 0;
	while (malloc(1 << 30)) {
		printf("Allocated %d GB\n", ++i);
	}

	printf("After\n");

	return 0;
}

