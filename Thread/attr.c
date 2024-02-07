#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *attr_thread1(void *arg) {
	printf("Thread 1\n");
	sleep(1);
	return (void *) 1;
}

void *attr_thread2(void *arg) {
	printf("Thread 2\n");
	sleep(1);
	return (void *) 2;
}

int main() {
	pthread_attr_t attr; // thread attribution
	pthread_t tid1, tid2;
	int status;
	void *result1, *result2;

	pthread_attr_init(&attr);
	status = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	// set thread's attribution joinable from beggining

	if (status !=0){
		fprintf(stderr, "Set detachstate\n");
		exit(1);
	}
	pthread_create (&tid1, &attr, attr_thread1, NULL);

	status = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        // set thread's attribution detached from beggining

        if (status !=0){
                fprintf(stderr, "Set detachstate\n");
                exit(1);
        }
        pthread_create (&tid2, &attr, attr_thread2, NULL);

	pthread_attr_destroy(&attr);

	pthread_join(tid1, &result1);
	pthread_join(tid2, &result2);

	printf("res1 = %p\n", result1);
	printf("res2 = %p\n", result2);

	return result1 != (void *) 1 || result2 != (void *) 2;
}

