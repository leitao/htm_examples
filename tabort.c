#include <stdio.h>

int main(){
	printf("Hello\n");
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm ("tabort. 1\n\t");


	//asm ("trap \n\t");
	printf("End\n");
	return 0;

failure:
	printf("Failure\n");
	return 1;
}
