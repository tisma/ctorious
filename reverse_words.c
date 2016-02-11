#include <stdio.h>

void reverse(char* begin, char* end)
{
	char temp;
	while (begin < end)
	{
		temp = *begin;
		*begin = *end;
		*end = temp;
		begin++;
		end--;
	}
}

void reverseWords(char* str)
{
	if (!str) {
		return;
	}

	char* start = str;
	char* temp = str;

	while (*temp)
	{
		temp++;
		if (*temp == '\0') {
			reverse(start, temp - 1);
		} else if (*temp == ' ') {
			reverse(start, temp - 1);
			start = temp + 1;
		}
	}

	reverse(str, temp - 1);
}

int main(int argc, char* argv[])
{
	char str[] = "This is a reverse string example.";
	reverseWords(str);
	printf("%s\n", str);

	return 0;
}

