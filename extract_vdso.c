#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	char buf[256], *mem;
	const char *range_name;
	FILE *rd, *wr;
	long long start_addr, end_addr;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <file> <string>\n"
						"\t<file>:   File to write the vdso data to.\n"
						"\t<string>: Name of the mapped in region, e.g. vdso\n", argv[0]);
		abort();
	}

	range_name = argv[2];

	if (!(wr = fopen(argv[1], "w")))
	{
		perror("Error: fopen() - output file");
		abort();
	}

	if (!(rd = fopen("/proc/self/maps", "r")))
	{
		perror("Error: fopen() - /proc/self/maps");
		abort();
	}

	while (fgets(buf, sizeof(buf), rd))
	{
		if (strstr(buf, range_name))
			break;
	}

	fclose(rd);

	end_addr = strtoll((strchr(buf, '-') + 1), NULL, 16);
	*(strchr(buf, '-')) = '\0';
	start_addr = strtoll(buf, NULL, 16);

	if (!(rd = fopen("/proc/self/mem", "r")))
	{
		perror("Error: fopen() - /proc/self/mem");
		abort();
	}

	fseek(rd, start_addr, SEEK_SET);

	mem = (char*)malloc(end_addr - start_addr);
	if (!fread(mem, 1, end_addr - start_addr, rd))
	{
		perror("Error: read() - /proc/self/mem");
		abort();
	}

	if (!fwrite(mem, 1, end_addr - start_addr, wr))
	{
		perror("Error: fwrite() - output file");
		abort();
	}

	free(mem);
	fclose(rd);
	fclose(wr);

	printf("Start: %p\nEnd:   %p\nBytes: %d\n",
			(void*)start_addr, (void*)end_addr, (int)(end_addr - start_addr));

	return 0;
}