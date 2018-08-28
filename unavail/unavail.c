#define _GNU_SOURCE
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <pthread.h>
#include <sched.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

uint64_t counter = 0x00f000000;
void *tm(void *);
void *pong(void *);

static inline long failure_code(void)                                                  
{
        return __builtin_get_texasru() >> 24;
}

void thread(){
	pthread_t t1, t0; 
	pthread_attr_t attr; 
        cpu_set_t cpuset; 
	int rc, i;
	void *ret_value;
	pthread_t array[10];
	counter = rand() % 0xffffff;
   
	printf("Starting\n");
	/* Set only CPU 0 in the mask. Both threads will be bound to CPU 0. */ 
	CPU_ZERO(&cpuset); 
	CPU_SET(0, &cpuset); 

	/* Init pthread attribute. */ 
	rc = pthread_attr_init(&attr); 
	if (rc) 
		printf("pthread_attr_init()"); 

	/* Set CPU 0 mask into the pthread attribute. */ 
	rc = pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset); 
	if (rc) 
		  printf("pthread_attr_setaffinity_np()"); 

	for (i = 0 ; i< 10; i++) {
		rc = pthread_create(&array[i], &attr /* Bind to CPU 0 */, tm, NULL); 
		if (rc)
			printf("pthread_create()"); 
	}

	rc = pthread_create(&t1, &attr /* Bind to CPU 0 */, pong, NULL); 
	if (rc) 
		printf("pthread_create()"); 


	for (i = 0 ; i< 10; i++) {
		rc = pthread_join(array[i], &ret_value);
		if (rc)
                          printf("pthread_join");
	}
	rc = pthread_join(t1, &ret_value);                                   

}


 void *pong(void *not_used)
  {
  
          /* Classed as an interactive-like thread. */
          while (1)
                  sched_yield();
  }


void *tm(void *foo){

	pid_t tid = syscall(SYS_gettid);
	printf("Thread id %d\n", tid);
	printf("Original falure cause: (%x)\n", failure_code());

	asm volatile goto(
		"mtctr %[counter];"
		"1:     bdnz 1b ;"
		"tbegin.	;"
		"beq 	%[fail];"
		"fadd   10,10, 10 ;"
		"tend.	;"
		:
		:[counter] "r" (counter)
		: 
		:fail
	);

	printf("Succeed\n");

	
	return 0;
fail:
	printf("Failed. (%x)\n", failure_code());
	return 0;
}

int main(){
	printf("Process %ld\n", getpid());
	thread();
}
