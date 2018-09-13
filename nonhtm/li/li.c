#include <stdio.h>
#include <stdlib.h>

#define MSR_TS_LG       33              /* Trans Mem state (2 bits) */            

void display_binary(unsigned long n)
{
    long int arr[64];
    int arr_counter=0;
    while(n>=1)
    {
        arr[arr_counter++]=n%2;
        n/=2;
    }
    for(int i=arr_counter-1;i>=0;i--)
    {
        printf("%d",arr[i]);
    }
	printf("\n");
}

int li(unsigned long reg){
	unsigned long res = 0;
	unsigned long register r = 0xdeadbeefbaddcafe;

	asm volatile (
			"li %[res], 0;"
			" li %[res], 0xdeadbeef@high"
			: [res] "=r" (res)
			: [reg] "r" (reg)
			:
	);

	printf("HEx: %x\n", res);
	display_binary(res);


}

int main(int *argc, char **argv){
	unsigned long rs = -1;

	if (argv[1] != NULL)
		rs = strtol(argv[1], NULL, 0);
	

	li(rs);
}
