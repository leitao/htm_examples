#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Calling a syscall inside a htm\n");
	asm ("tbegin.  \n\t");
	asm ("li 3, 3\n\t");
	write(STDOUT_FILENO, "Hi!", 3);	
	asm ("trap\n\t");
	asm ("tend.\n\t");


	return 1;
	printf("Failure\n");

failure:
	return 0;
}
