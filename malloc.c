#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{

	void* ptr = malloc(5 * sizeof(int));

	// int i = 0;
	// for (i = 0; i < 32; i++) {
	// 	printf("%u\n", *((int*)(ptr - i)));
	// }

	printf("%s returns: %d\n", __FUNCTION__, malloc_usable_size(ptr));

	free(ptr);

	return EXIT_SUCCESS;
}