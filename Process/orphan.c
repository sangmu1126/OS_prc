#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t childPid;
	int i;
	childPid = fork();
	if (childPid > 0) { // parent
		printf("Parent's pid : %d\n", getpid());
		sleep(2);
		printf("Parent terminates\n");
		exit(0);
	}
	else if(childPid == 0){
		printf("Children\n");
		for(i=0;i<10;i++) {
			printf("Children's pid : %d, Parent's pid : %d\n", getpid(), getppid());
			sleep(1);
		}
		printf("Children terminates\n");
		exit(0);
	}
	else {
		return -1;
	}
	return 0;
}
