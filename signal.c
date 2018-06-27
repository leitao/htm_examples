#include <stdio.h>
#include <signal.h>

int htm(){
	asm goto ("tbegin.  		\n\t"
		  "beq %l[failure]	\n\t" 
		  ".long 0x0 		\n\t"
		  "tend. 		\n\t"
		  : : : : failure);

	printf("Success. This is an error!\n");
	return 0;
failure:
	printf("Failure. Expected state\n");
	return 1;
}

void signal_handler(int signo, siginfo_t *si, void *data) {
	printf("Signal called. Returning\n");
}

int main(){
	int a = 0;

	struct sigaction sa;

        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = signal_handler;
        sigaction(SIGTRAP, &sa, NULL);
        sigaction(SIGILL,  &sa, NULL);


	return htm();
}
