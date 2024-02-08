#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	struct mq_attr attr;
	// attr can be error
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 8192;
	char buf[8192] = {0,};

	mqd_t mq;
	mq = mq_open("/mq", O_WRONLY, 0666, &attr);
	if (mq ==-1) {
		perror("open error");
		exit(0);
	}
	scanf("%s", buf);
	if ((mq_send(mq, buf, strlen(buf), 1)) == -1) {
		perror("mq_send error");
		exit(-1);
	}
	mq_close(mq);
}
