#include <stdio.h>

typedef unsigned long ul;

void g()
{
	printf("Gotcha!\n");
}

char* f(char* x)
{
	int i;
	char* ptr;
	printf("Made it into f - returning now\n");
	return x;
}

int main()
{
	int i;
	char s[8];
	printf("main=%lx, g=%lx\n", (ul)main, (long)g);
	for (i = 0; i < 24; s[i++] = 'A');
	s[24] = 0x7d;
	s[25] = 0x5;
	s[26] = 0x40;
	for (i = 27; i < 31; s[i++] = 0x0);
	f(s);
	printf("Done with f\n");
	return 0;
}

