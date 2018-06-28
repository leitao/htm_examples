#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	printf("Calling a syscall inside a htm\n");
	asm ("tbegin.  \n\t");
	asm ("li 3, 3\n\t");
	exit(-1);
	asm ("tend.\n\t");

	printf("Failure\n");
	return 1;

failure:
	return 0;
}
