#include <stdio.h>
#include <signal.h>
#include <pthread.h>

#define MAX 1024

int ret = 0;
void *htm(void *ptr){
	asm goto ("tbegin.  		\n\t"
		  "beq %l[failure]	\n\t" 
		  ".long 0x0 		\n\t"
		  "tend. 		\n\t"
		  : : : : failure);

	printf("Failure. \n");
	ret += 1;
failure:
	printf(".");
}

void signal_handler(int signo, siginfo_t *si, void *data) {
	//printf("Signal called. Returning\n");
	//printf("Trap = %d\n", si->si_value);
}

int main(){
	int a;

	struct sigaction sa;
	pthread_t thr[MAX];

        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = signal_handler;
        sigaction(SIGTRAP, &sa, NULL);
        sigaction(SIGILL,  &sa, NULL);


	// Parallel
	for (a = 0; a < MAX; a++) {
		if (pthread_create(&thr[0], NULL, &htm, NULL)) {
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}

		if (pthread_join(thr[0], NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
	}

	printf("\nParallel\n");

	for (a = 0; a < MAX; a++) {
		if (pthread_create(&thr[a], NULL, &htm, NULL)) {
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}

	}

	for (a = 0; a < MAX; a++) {
		if (pthread_join(thr[a], NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
	}
	printf("\n");

	return ret;
}
