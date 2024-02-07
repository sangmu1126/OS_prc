#include <pthread.h>
#include <stdio.h>

void *threadRoutine(void *arg) {
	int count = 0;
	pthread_t tid = pthread_self(); // return and print tid
	printf("thread ID :: %lu\n", tid);
	while(count < 2000000) {
		printf("a\n");
		count++;
	}
	pthread_exit(arg); // extra change
}

int main() {
	pthread_t threadID;
	int status;
	void *result;
	char tmp[10];

	scanf("%s", tmp);
	pthread_create(&threadID, NULL, threadRoutine, NULL);

	// thread detach
	scanf("%s", tmp);

	status = pthread_join(threadID, &result);
	if(status != 0) {
		exit(1);
	}
	while(1) printf("b\n");
}
