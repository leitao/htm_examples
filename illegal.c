#include <stdio.h>
#include <signal.h>

int htm(){
	asm goto ("tbegin.  		\n\t"
		  "beq %l[failure]	\n\t" 
		  "li 3, 3		\n\t"
		  "trap 		\n\t"
		  "tend. 		\n\t"
		  : : : : failure);

	return 0;
failure:
	printf("Failure\n");
	return 1;
}

void signal_handler(int signo, siginfo_t *si, void *data) {
	// Do nothing
	printf("Inside the signal\n");

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
