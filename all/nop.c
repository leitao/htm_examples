#include <stdio.h>

int loop(){
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm ("nop \n\t");
	asm ("tend. \n\t");
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
