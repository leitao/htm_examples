#include <stdio.h>

int main(){
	printf("Hello\n");
	asm ("trap\n\t");

	printf("End\n");
	return 0;

}
