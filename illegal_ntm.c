#include <stdio.h>
#include <signal.h>

int htm(){
	asm ("trap \n\t");
	return 0;
}

void signal_handler(int signo, siginfo_t *si, void *data) {
	// Do nothing
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
