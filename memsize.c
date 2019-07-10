#include <stdio.h>
#include <sys/sysinfo.h>
#include <stdint.h>

uint64_t get_memory_size()
{
	struct sysinfo info;
	sysinfo( &info );
	printf("total ram %lu, mem units %lu\n", (size_t)info.totalram, (size_t)info.mem_unit);
	return (size_t)info.totalram * (size_t)info.mem_unit;
}

int main(int argc, char* argv[])
{
	uint64_t total_memory = get_memory_size();
	printf("Total physical memory: %lu\n", total_memory);
	return 0;
}

