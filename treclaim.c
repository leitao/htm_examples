#include <stdio.h>

int main(){
	printf("Hello\n");
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("treclaim. 0\n\t");
	asm ("tend.\n\t");

	return 0;

failure:
	printf("Failure\n");
	return 1;
}