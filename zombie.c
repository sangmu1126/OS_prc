#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	pid_t childPid;
	childPid = fork();

	if (childPid > 0) { // parent
		printf("parent's pid : %d\n", getpid());

		sleep(30);
		printf("Parent terminates\n");
		exit(0);
	}
	else if (childPid==0) { // children
		printf("children\n");
		sleep(1);
		printf("Children terminates\n");
		exit(0);
	}
	else {
		perror("fork failed!\n");
		return -1;
	}
	return 0;
}
