#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 3

void *hello(void *arg) {
	printf("Thread %d:Hello, World!\n", arg);
	return arg;
}

void main() {
	pthread_t tid[NUM_THREADS];
	int i, status;

	for(i=0; i < NUM_THREADS; i++) {
		status = pthread_create(&tid[i], NULL, hello, (void *) i);
		if (status != 0){
			fprintf(stderr, "Create thread %d: %d", i, status);
			exit(1);
		}
	}
	pthread_exit(NULL);
}
