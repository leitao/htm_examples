#include <stdio.h>

int loop(){
	printf("Hello\n");
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm (".long 0x0 \n\t");
	asm ("tend. \n\t");
	printf("End\n");
	return 0;

failure:
	printf("Failure\n");
	return 1;
}

int main(){
	int a = 0;

	for (a =0; a < 1000; a++)
		loop();
}
