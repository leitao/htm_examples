#include <stdio.h>
#include <signal.h>
#include <ucontext.h>

int a = 1;
int htm(){
	asm ("trap \n\t");
	return 0;
}

void signal_handler(int signo, siginfo_t *si, void *data) {
	a = 0;
	ucontext_t *uc = (ucontext_t *) data;
	ucontext_t *tm_uc = uc->uc_link;

	mcontext_t *mcontext = (mcontext_t *) &uc->uc_mcontext;
	mcontext_t *tm_mcontext = (mcontext_t *) &tm_uc->uc_mcontext;

	printf("Checkpointed\n");
	printf("R0 = %lx\n", mcontext->gp_regs[0]);
	//if (tm_mcontext != NULL){
		//printf("Transactional\n");
	//	printf("R0 = %lx\n", tm_mcontext->gp_regs[0]);
	//}

	/* Exit the signal handler */
	mcontext->gp_regs[32] += 4; // skip illegal


}

int main(){

	struct sigaction sa;

        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = signal_handler;
        sigaction(SIGTRAP, &sa, NULL);
        sigaction(SIGILL,  &sa, NULL);


	htm();

	return a;
}
