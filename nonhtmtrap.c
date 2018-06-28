#include <stdio.h>

int main(){
	asm ("trap\n\t");
 	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm ("tend.\n\t");

	return 0;
failure:

	return 1;
}
