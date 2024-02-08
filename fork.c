#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
	int pid;
	int counter = 1;
	pid = fork();
	if (pid < 0) {
		//error occurred
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
	else if(pid==0) {
		// child process
		printf("Child here!\n");
		while(counter < 6) {
			printf("Child num: %d\n", counter); // parent and child act independently
			counter++;
			sleep(1);
		}
	}
	else {
		// parent process
		printf("I'm parent!\n");
		while(counter< 6) {
			printf("parent num: %d\n", counter);
			sleep(1);
		}
		wait(NULL);
		printf("process complete!\n");
	}
	return 0;
}
