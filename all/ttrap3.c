#include <stdio.h>

int main(){
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("trap\n\t");
	asm ("tabort. 3\n\t");

	return 0;

failure:
	printf("Failure\n");
	return 1;
}
