#include <stdio.h>

int bracket_match(char *bracket_string) 
{
	int num1 = 0, num2 = 0;
	int res = 0;

	char* p = bracket_string;

	while (*p != '\0') {
		if (*p == '(')
			num1++;
		else if (*p == ')')
			num2++;
		p++;
	}

	res = num1 - num2;
	return res > 0 ? res : -res;
}

const char* test[] = {
	"(()())",
	"((())",
	"())"
};

int main()
{
	int i = 0;
	for (i = 0; i < sizeof(test) / sizeof(test[0]); i++) {
		printf("%s %d\n", test[i], bracket_match((char*)test[i]));
	}
	return 0;
}