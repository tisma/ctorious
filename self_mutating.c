#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

int change_page_permission_of_address(void* addr) {
	int page_size = getpagesize();
	addr -= (unsigned long)addr % page_size;

	if (mprotect(addr, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
		return -1;
	}

	return 0;
}

void foo(void);
void bar(void);
void print_function_instructions(void* func_ptr, size_t func_len);

int main(void) {
	void *foo_addr = (void*)foo;
	//void *bar_addr = (void*)bar;

	//print_function_instructions(foo_addr, bar_addr - foo_addr);

    if (change_page_permission_of_address(foo_addr) == -1) {
		fprintf(stderr, "Error while changing page permissions of foo(): %s\n", strerror(errno));
		return 1;
	}

	puts("Calling foo...");
	foo();

	//unsigned char* instruction = (unsigned char*)foo_addr + 18;
	//*instruction = 0x2A;
	//
	char shellcode[] = 
		"\x48\x31\xd2"                              // xor    %rdx, %rdx
		"\x48\x31\xc0"                              // xor    %rax, %rax
		"\x48\xbb\x2f\x62\x69\x6e\x2f\x73\x68\x00"  // mov    $0x68732f6e69622f2f, %rbx
		"\x53"                                      // push   %rbx
		"\x48\x89\xe7"                              // mov    %rsp, %rdi
		"\x50"                                      // push   %rax
		"\x57"                                      // push   %rdi
		"\x48\x89\xe6"                              // mov    %rsp, %rsi
		"\xb0\x3b"                                  // mov    $0x3b, %al
		"\x0f\x05";                                 // syscall

	memcpy(foo_addr, shellcode, sizeof(shellcode)-1);
	puts("Calling foo...");
	foo();

	return 0;
}

void foo(void) {
	int i = 0;
	i++;
	printf("i: %d\n", i);
}

void bar(void) { }

void print_function_instructions(void* func_ptr, size_t func_len) {
	for (unsigned char i = 0; i < func_len; i++) {
		unsigned char *instruction = (unsigned char*)func_ptr + i;
		printf("%p (%2u): %x\n", func_ptr + i, i, *instruction);
	}
}

