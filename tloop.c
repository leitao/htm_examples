#include <stdio.h>

int main(){
	int i;

	printf("Hello\n");
	
	for (i = 0 ; i < 100; i ++) {
		asm ("tbegin.  \n\t");
		asm goto ("beq %l[failure] \n\t" : : : : failure);
		asm ("lis 3, 0x1fff\n\t");
	loop:
		asm ("addi     3, 3, -1\n\t");
		asm ("cmpdi    3, 0\n\t");
		asm goto("bne      %l[loop] \n\t" : : : : loop);
		asm ("tend.\n\t");
	}

	printf("End\n");
	return 0;

failure:
	printf("Failure\n");
	return 1;
}
