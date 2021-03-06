#include <stdio.h>
#include <signal.h>
#include <ucontext.h>
#include <stdlib.h>
#include <unistd.h>

#define PSL_HTM_TRA     0x0000000400000000UL    /* Hardware Transactional Memory State */
#define PSL_HTM_TSU     0x0000000200000000UL    /* Hardware Transactional Memory State */
#define PSL_HTM         0x0000000100000000UL        /* Hardware Transactional Memory available */

#define MAX 1024

#define RANDOM 0

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

void do_hack(mcontext_t *tm_mcontext, mcontext_t *mcontext) {
	int r = rand();
	int64_t msr;

	if (RANDOM) {
		msr = ((int64_t) rand()) << 32 | rand();
		// Change MSR to a random number
		tm_mcontext->gp_regs[33] = msr;
		// And also R1
		tm_mcontext->gp_regs[1] = msr;
		printf("%lx", msr);

		msr = ((int64_t) rand()) << 32 | rand();
		mcontext->gp_regs[33] = msr;
		//mcontext->gp_regs[1] = msr;
	} else {
		if (r & 0x2) {
			tm_mcontext->gp_regs[33] |= PSL_HTM_TRA;
		} else {
			tm_mcontext->gp_regs[33] &= ~PSL_HTM_TRA;
		}

		if (r & 0x4) {
			tm_mcontext->gp_regs[33] |= PSL_HTM_TSU;
		} else {
			tm_mcontext->gp_regs[33] &= ~PSL_HTM_TSU;
		}

		if (r & 0x8) {
			tm_mcontext->gp_regs[33] |= PSL_HTM;
		} else {
			tm_mcontext->gp_regs[33] &= ~PSL_HTM;
		}

		if (r & 0x10) {
			mcontext->gp_regs[33] |= PSL_HTM_TRA;
		} else {
			mcontext->gp_regs[33] &= ~PSL_HTM_TRA;
		}

		if (r & 0x20) {
			mcontext->gp_regs[33] |= PSL_HTM_TSU;
		} else {
			mcontext->gp_regs[33] &= ~PSL_HTM_TSU;
		}

		if (r & 0x40) {
			mcontext->gp_regs[33] |= PSL_HTM;
		} else {
			mcontext->gp_regs[33] &= ~PSL_HTM;
		}
	}

}

void signal_handler(int signo, siginfo_t *si, void *data) {

	/* user context */
	ucontext_t *uc = (ucontext_t *) data;
	mcontext_t *tm_mcontext;

	mcontext_t *mcontext = (mcontext_t *) &uc->uc_mcontext;
	printf("Checkpointed\n");
	printf("R0 = %lx\n", mcontext->gp_regs[0]);
	printf("MSR = %lx\n", mcontext->gp_regs[33]);
 
	/* transactional machine context */
	ucontext_t *tm_uc = uc->uc_link;
	if (tm_uc != NULL){
		tm_mcontext = (mcontext_t *) &tm_uc->uc_mcontext;
		printf("Transactional different\n");
		printf("R0 = %lx\n", tm_mcontext->gp_regs[0]);
		printf("MSR = %lx\n", tm_mcontext->gp_regs[33]);
	}

	do_hack(tm_mcontext, mcontext);
}

int main(){
	int i;
	struct sigaction sa;

        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = signal_handler;
        sigaction(SIGTRAP, &sa, NULL);
        sigaction(SIGILL,  &sa, NULL);

	for (i = 0 ; i < MAX ; i++) {
		htm();
	}

	return 0;
}
