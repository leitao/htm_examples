#include <stdio.h>
#include <signal.h>

int htm(){
	printf("Hello\n");
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm (".long 0x0 \n\t");
	asm ("tend. \n\t");
	printf("End\n");
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
