#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Hi there -> iH ereht

void reverse(char* begin, char* end)
{
	char tmp;
	while (begin < end) {
		tmp = *begin;
		*begin++ = *end;
		*end-- = tmp;
	}
}

void mirror_words(char* words)
{
	if (!words) {
		return;
	}
	char* word_begin = words;
	char* tmp = words;

	while (*tmp) {
		tmp++;
		if (*tmp == '\0') {
			reverse(word_begin, tmp - 1);
		} else if (*tmp == ' ') {
			reverse(word_begin, tmp - 1);
			word_begin = tmp + 1;
		}
	}

	reverse(words, tmp - 1);
}

int main(int args, char** argv)
{
	char words[] = "I like this program very much";
	char* tmp = words;
	mirror_words(words);

	fprintf(stdout, "%s\n", words);
	return EXIT_SUCCESS;
}