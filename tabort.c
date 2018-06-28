#include <stdio.h>

int main(){
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm ("tabort. 0\n\t");


	//asm ("trap \n\t");
	printf("Failure\n");
	return 1;

failure:
	return 0;
}
