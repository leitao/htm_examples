#include <stdio.h>
#include <unistd.h>


long long mfspr() {
	long long reg;

#define        SPR_TEXASR              0x082   /* Transaction EXception And Status Register */
	asm ("mfspr %0, 0x82" : "+r" (reg));

	return reg;
}

int main(){
	long long texasr_ = 0x0;

	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm ("tabort. 3\n\t");

	// Should never be reached
	printf("End\n");
	return 0;

failure:
	texasr_ = mfspr();
	printf("Failure due to tabort.\n");
	printf("TEXASR: %llx\n", texasr_);

	/* Wait for a context switch */
	sleep(1);
	texasr_ = mfspr();
	#define TEXASR_CAUSE 0xFF00000000000000UL
	if (texasr_ & (TEXASR_CAUSE >> 56) != 3) {
		printf("TEXASR: %lx\n", texasr_);
		printf("CAUSE: %lx\n", (texasr_ & TEXASR_CAUSE) >> 56);
	}

	return 0;
}
