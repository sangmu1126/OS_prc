#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	if(mkfifo(argv[1], 0666) != 0) {
		perror("mkfifo failure : ");
	}
	return 0;
}
