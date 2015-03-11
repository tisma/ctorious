#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <unistd.h>

int main()
{
	pid_t child;
	long orig_eax;

	child = fork();

	if (child == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "ls", NULL);
	} else {
		wait(NULL);
		orig_eax = ptrace(PTRACE_PEEKUSER, child, 4 * ORIG_EAX, NULL);
		
		printf("The child made a system call %ld\n", orig_eax);

		ptrace(PTRACE_COUNT, child, NULL, NULL);
	}

	return 0;
}

