#include <stdio.h>
#include <signal.h>
#include <ucontext.h>
#include <stdlib.h>

int htm(){
	printf("starting htm block\n");
	asm ("li 0, 1 \n\t");
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	/* Load R0 with 0 */
	asm ("li 0, 3 \n\t");
	asm ("trap \n\t");
	asm ("tend. 0 \n\t");

	return 0;
failure:
	printf("Failure handler called\n");
	return 0;
}

void signal_handler(int signo, siginfo_t *si, void *data) {

	/* user context */
	ucontext_t *uc = (ucontext_t *) data;

	mcontext_t *mcontext = (mcontext_t *) &uc->uc_mcontext;
	printf("Checkpointed\n");
	printf("R0 = %lx\n", mcontext->gp_regs[0]);
	printf("MSR = %lx\n", mcontext->gp_regs[33]);
 
	/* transactional machine context */
	ucontext_t *tm_uc = uc->uc_link;
	if (tm_uc != NULL){
		mcontext_t *tm_mcontext = (mcontext_t *) &tm_uc->uc_mcontext;
		printf("Transactional different\n");
		printf("R0 = %lx\n", tm_mcontext->gp_regs[0]);
		printf("MSR = %lx\n", tm_mcontext->gp_regs[33]);
	}

	/* Exit the signal handler, if not transactional */
	mcontext->gp_regs[32] += 12; // skip illegal
}

int main(){

	struct sigaction sa;

        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = signal_handler;
        sigaction(SIGTRAP, &sa, NULL);
        sigaction(SIGILL,  &sa, NULL);

	htm();

	return 0;
}
