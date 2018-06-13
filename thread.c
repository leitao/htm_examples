#include <stdio.h>
#include <pthread.h>

void *loop(void *p){
	printf("Hello\n");
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm (".long 0x0 \n\t");
	asm ("tend. \n\t");
	printf("End\n");
	return NULL;

failure:
	printf("Failure\n");
	return NULL;
}

int main(){
	int a = 0;
	pthread_t threads[1024];

	for (int i = 0; i < 1024; i++) {
		pthread_create(&threads[i], NULL, &loop, NULL);
	}
}
