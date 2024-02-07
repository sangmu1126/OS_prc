#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *cancel_thread(void *arg) {
	int i, state;
	while(1) {
		// make thread cannot cancel
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		printf("Thread: cancel state disabled\n");
		sleep(1);
		// make thread can cancel againg
		pthread_setcancelstate(state, &state);
		printf("Thread: cancel state abled\n");
		if (i%5==0)	pthread_testcancel;
	}
	return arg;
}

int main(int argc, char *argv[]) {
	pthread_t tid;
	int arg, status;
	void *result;
	int a=0;
	if (argc < 2) {
		fprintf(stderr, "USAGE: cancelthread time(sec)\n");
		exit(1);
	}
	status = pthread_create(&tid, NULL, cancel_thread, NULL);

	if (status != 0) {
		fprintf(stderr, "create thread: %d", status);
		exit(1);
	}
	pthread_detach(tid);
	arg = atoi(argv[1]);
	sleep(arg);

	status = pthread_cancel(tid);

	if (status != 0) {
		fprintf(stderr, "Join thread: %d", status);
		exit(1);
	}
	while(1) {
		a++;
	}
	return (int)result;
}
