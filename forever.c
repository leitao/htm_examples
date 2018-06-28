#include <stdio.h>
#include <unistd.h>

int main(){
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("trap\n\t");
	sleep(1);


	printf("Failure\n");
	
	return 1;

failure:
	return 0;
}
