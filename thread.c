#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *loop1(void *p){
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm ("tend. \n\t");
	exit(1);

failure:
	printf("Failure\n");
	return NULL;
}
void *loop(void *p){
	asm ("tbegin.  \n\t");
        asm goto ("beq %l[failure] \n\t" : : : : failure);
	asm ("li 3, 3\n\t");
	asm ("trap \n\t");
	asm ("tend. \n\t");
	exit(1);

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

	for (int i = 0; i < 1024; i++) {
		pthread_join(threads[i], NULL);
	}

	for (int i = 0; i < 1024; i++) {
		pthread_create(&threads[i], NULL, &loop, NULL);
	}

	for (int i = 0; i < 1024; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}
