#include <stdio.h>

long long mfspr() {
	long long reg;

#define        SPR_TEXASR              0x082   /* Transaction EXception And Status Register */
	asm ("mfspr %0, 0x82" : : "r"(reg));

	return reg;
}

int main(){
	printf("Hello\n");

	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm ("tabort. 12\n\t");
	printf("End\n");
	return 0;

failure:

	printf("Failure\n");

	printf("TEXASR: %llx\n", mfspr());
#define TEXASR_CAUSE 0xFC00000000000000ULL
	printf("CAUSE: %llx\n", mfspr() & TEXASR_CAUSE);

	return 1;
}
