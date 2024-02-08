#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>

int main() {
	struct mq_attr attr;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 8192;
	char buf[8192] = {0,};

	mqd_t mq;
	struct timespec tm;

	mq = mq_open("/mq", O_RDWR | O_CREAT, 0666, &attr);
	if (mq == -1) {
		perror("message queue open error");
		exit(1);
	}

	clock_gettime(CLOCK_REALTIME, &tm);
	tm.tv_sec += 60;
	if (mq_timedreceive(mq, buf, attr.mq_msgsize, 0, &tm) == -1) {
		perror("mq_receive error");
		exit(-1);
	}
	printf("mq received : %s\n", buf);
	mq_close(mq);
}
