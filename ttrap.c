#include <stdio.h>

int main(){
	printf("Hello\n");
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("trap\n\t");
	asm ("tend.\n\t");


	//asm ("trap \n\t");
	printf("End\n");
	return 0;

failure:
	printf("Failure\n");
	return 1;
}
