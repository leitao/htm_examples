#include <stdio.h>
#include <signal.h>

#define MAX 1024

int htm(){
	asm goto ("tbegin.  		\n\t"
		  "beq %l[failure]	\n\t" 
		  ".long 0x0 		\n\t"
		  "tend. 		\n\t"
		  : : : : failure);

	printf("Failure. \n");
	return 1;
failure:
	return 0;
}

void signal_handler(int signo, siginfo_t *si, void *data) {
	printf("Signal called. Returning\n");
	printf("Trap = %d\n", si->si_value);
}

int main(){
	int a;
	int ret;

	struct sigaction sa;

        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = signal_handler;
        sigaction(SIGTRAP, &sa, NULL);
        sigaction(SIGILL,  &sa, NULL);

	for (a = 0; a < MAX; a++)
		ret += htm();

	return ret;
}
