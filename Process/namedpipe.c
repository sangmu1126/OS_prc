#include <sys/types.h>
#include <sys/stats.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define chop(x) x{strlen(x)-1} = 0x00

int main() {
	int fp_r;
	int fp_w;
	int n;
	int i;
	char buf_r[11];
	char buf_w[11];

	if((fp_w=open("testfifo1", O_WRONLY))<0) {
		perror("open error : ");
		exit(0);
	}
	if((fp_r=open("testfifo2", O_RDONLY))<0) {
		perror("open error : ");
		exit(0);
	}

	i=1;

	memset(buf_r, 0x00, 11);
	memset(buf_w, 0x00, 11);
	sprintf(buf_w, "%d\n", i);

	while((n=write(fp_w, buf_w, 11))>0) {
		read(fp_r, buf_r, 11);

		printf("%6d^2 = %s, atoi(buf_w), buf_r);
		memset(buf_r, 0x00, 11);
		memset(buf_w, 0x00, 11);
		i++;
		sprintf(buf_w, "%d\n", i);
		sleep(1);
	}
}
