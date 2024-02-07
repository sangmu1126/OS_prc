#include <pthread.h>
#include <stdio.h>

void *threadRoutine(void *arg) {
	int count = 0;
	pthread_t tid = pthread_self();
	// return tid
	printf("thread ID :: %lu\n", tid);
	while(count < 100000000000) {
		printf("a\n");
		count++;
	}
	pthread_exit(arg); // extra change
}

int main() {
	pthread_t threadID;
	char tmp[10];

	scanf("%s", tmp); // stop process to check pstree
	pthread_create(&threadID, NULL, threadRoutine, NULL);

	// thread detach
	scanf("%s", tmp);
	pthread_detach(threadID);

	while(1) {
		printf("b\n");
	}
}
