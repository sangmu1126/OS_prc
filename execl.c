#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	printf("execl start\n");
	execl("/bin/ls", "ls", "-1", NULL);
	system("/bin/ls -l");
	// system function => get process name and call
	// Orgin : int system(const char *argv);
	// 0 : fail, 1+ : return
	printf("if you read this message, fail creating execl func..\n");
	// if don't use execl func, current process would be uncovered, so after system, printf
	return 0;
}
