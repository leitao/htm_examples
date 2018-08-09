#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>

//#define SPRN_DSCR       0x11
#define SPRN_DSCR       0x3
uint64_t counter = 0x0ff000000;

unsigned long get_dscr(void)
{
        unsigned long ret;

        asm volatile("mfspr %0,%1" : "=r" (ret) : "i" (SPRN_DSCR));

        return ret;
}

void set_dscr(unsigned long val)                                                                           
{
	printf("Setting the dscr to %lx\n", val);
	asm volatile("mtspr %1,%0" : : "r" (val), "i" (SPRN_DSCR));
}

void tm_read_mid(){
	set_dscr(0x4);

	asm __volatile__ (
		"tbegin.	;"
		"beq 	2f;"
		"tsuspend. ;"
                "mtctr %[counter];"
                "1:     bdnz 1b ;"
		:
		: [counter] "r" (counter)
		:
	);
	printf("DSCR value is %lx\n", get_dscr());
	asm __volatile__ (
		"tresume.	;"
		"2: ;"
		:
		:[sprn_dscr]"i"(SPRN_DSCR), [counter] "r" (counter)
		: 
	);
	printf("After failure DSCR value is %lx\n", get_dscr());

}

void tm_write_mid(){
	set_dscr(0x7);

	asm __volatile__ (
		"tbegin.	;"
		"beq 	2f;"
		"tsuspend. ;"
	);
	set_dscr(0x4);
	asm __volatile__ (
		"tresume.	;"
		"2: ;"
		:
		:[sprn_dscr]"i"(SPRN_DSCR), [counter] "r" (counter)
		: 
	);

	printf("DSCR value is %lx\n", get_dscr());
}

void tm_suspend(){
	set_dscr(0x5);

	asm __volatile__ (
		"tbegin.	;"
		"beq 	2f;"
		"tsuspend. ;"
		"mtctr %[counter];"
		"1:     bdnz 1b ;"
		"tresume.	;"
		"2: ;"
		:
		:[sprn_dscr]"i"(SPRN_DSCR), [counter] "r" (counter)
		: 
	);

	printf("DSCR value is %lx\n", get_dscr());
}

void tm(){
	set_dscr(0x2);

	asm __volatile__ (
		"tbegin.	;"
		"beq 	2f;"
		"mtctr %[counter];"
		"1:     bdnz 1b ;"
		"tend.	;"
		"2: ;"
		:
		:[sprn_dscr]"i"(SPRN_DSCR), [counter] "r" (counter)
		: 
	);

	printf("DSCR value is %lx\n", get_dscr());
}

int main(){
/*
	tm();
	tm_suspend();
	tm_write_mid();
*/
	tm_read_mid();
}
