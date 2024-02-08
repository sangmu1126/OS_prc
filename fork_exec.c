#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(){
	int pid;
	int counter = 1;
	pid = fork();
	if (pid < 0) {
	// error occured
		fprintf(stderr,"Fork failed");
		exit(-1);
	}
	else if(pid==0) {
	// child process
		printf("child here\n");
		printf("execl start!!\n");
		execl("/bin/ls", "ls", "-l", NULL);
		printf("if you read this message, fail creating execl func..\n");
	}
	else {
	// parent process
		printf("I'm parent!\n");
		wait(NULL);
		printf("process complete!\n");
	}
	return 0;
}
