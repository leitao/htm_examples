#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX 1024

static int nerr;

void *test(void *foobar) {
        unsigned long bef;
        unsigned long aft;

        asm volatile goto(
                        "std    13, 0(%[bef])   \n"	/* Store r13 before a transaction */
                        "tbegin.                \n"
                        "beq    1f         	\n"                                                                 
                        "li     13, 0123        \n"
			"sc			\n"	/* Force a abort */
                        "tend.                  \n"
			"b	 %[success]	\n"	/* Transaction commited. Leave */
                        "1:                     \n"	/* Transaction failed */
                        "std    13, 0(%[aft])   \n"
                        "b	%[fail]		\n" 
			:
                        : [bef] "r" (&bef),
			  [aft] "r" (&aft)
                        : "r13"
                        : fail, success);

success:
	printf("FAIL: Success with r13 = %lx - %lx \n", bef, aft);
	nerr += 1;
	exit(-1);
fail:
	if (aft != bef) {
		nerr += 1;
		printf("r13 changed from %lx to %lx\n", bef, aft);
		exit(-1);
	}

#ifdef DEBUG
	printf("r13 didn't changed from %lx to %lx\n", bef, aft);
#endif
	return NULL;
}


int main(){
	unsigned long ret = 0;
	pthread_t pthread_array[MAX];

#ifdef DEBUG
	test(NULL);

	return 0;
#endif

	do {
		for (int i = 0; i < MAX ; i++) {
			if (pthread_create(&pthread_array[i],  NULL, &test, NULL)) {
				perror("Thread error\n");
				return -1;
			}
		}


		for (int i = 0; i < MAX ; i++) {
			if (pthread_join(pthread_array[i], NULL)) {
				perror("Thread join error\n");
				return -1;
			}
		}
			

		if (nerr) {	
			printf("Error! (%x)\n", nerr);
		}
			
		printf(".");
		fflush(stdout);
	} while (nerr == 0);
}
