#include <stdio.h>

int main(){
	printf("Hello\n");
	asm ("tend.\n\t");


	printf("End\n");
	return 0;

failure:
	printf("Failure\n");
	return 1;
}
