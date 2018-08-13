#include <stdio.h>
#include <stdlib.h>

int main(int *argc, char **argv){
	unsigned long res = -1; 
	unsigned long rs = -1;

	if (argv[1] != NULL)
		rs = atol(argv[1]);
	
	printf("rs = %lx\n", rs);

	asm __volatile__ (
		" mr 4, %[rs] ;  \n"
		" rldicl %[res], 4, 1, 60; \n"
		: [res] "=r" (res)
		: [rs] "r" (rs)
		: "memory", "r4", "r3");

	printf("1. res = %lx\n", res);

	return 0;
}
