/*
 * =====================================================================================
 *
 *       Filename:  calloc.c
 *
 *    Description:  calloc vs malloc
 *
 *        Version:  1.0
 *        Created:  12/11/2016 11:46:10 AM
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Tisma tisma.etf@gmail.com
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	size_t huge = INTPTR_MAX;

	void* buf = malloc(huge * huge);
	if (!buf)
		perror("malloc failed");
	printf("malloc(huge * huge) returned: %p\n", buf);
	free(buf);

	buf = calloc(huge, huge);
	if (!buf)
		perror("calloc failed");
	printf("calloc(huge, huge) returned: %p\n", buf);
	free(buf);

	return 0;
}

