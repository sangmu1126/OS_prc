#include <stdio.h>
#include <unistd.h>

int main() {
	char *argv[] = {"ls", "-l", NULL};
	printf("execv start!!\n");
	execv("/bin/ls", argv); // execl call para one by one, but execv call pointer array
	// execl("/bin/ls", "ls", "-l", NULL);
	printf("if you read this message, fail creating execv func..\n");
	return 0;
}
