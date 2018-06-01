#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Hello\n");
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	
	sleep(1);


	printf("End\n");
	
	return 0;

failure:
	printf("Failure\n");
	return 1;
}
