#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Calling a syscall inside a htm\n");
	asm ("tbegin.  \n\t");
	asm ("li 3, 3\n\t");
	write(STDOUT_FILENO, "Hi!", 3);	
	asm ("trap\n\t");
	asm ("tend.\n\t");


	//asm ("trap \n\t");
	printf("End\n");
	return 0;

failure:
	printf("Failure\n");
	return 1;
}
