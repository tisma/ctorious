#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <ucontext.h>

static void signal_handler(int signo, siginfo_t* si, void* v_context)
{
	ucontext_t* context = v_context;
	context->uc_mcontext.gregs[REG_RIP] += 10;
}

int *null_pointer = NULL;

int main()
{
	struct sigaction psa;
	psa.sa_sigaction = signal_handler;
	sigaction(SIGSEGV, &psa, NULL);

	printf("Before NULL pointer dereference\n");

	*null_pointer = 1;
	__asm__ __volatile__("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");

	printf("After NULL pointer dereference. Still alive!\n");

	return 0;
}

