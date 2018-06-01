#include <stdio.h>

void tm(){
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm ("tend.\n\t");

	return;
failure:
	printf("Failure\n");
	exit(-1);
}
int main(){
	tm();
	sleep(1);
	tm();
	return 0;

}
