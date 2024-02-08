#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>

const int MAX_LINE = 2048;
const int PORT = 6001;

// receive message from server and print in thread

void *recv_message(void *fd) {
	int sockfd = *(int *) fd;
	char buf[MAX_LINE];

	while(1) {
		memset(buf, 0, MAX_LINE);
		int n;
		if ((n = recv(sockfd, buf, MAX_LINE, 0)) == -1) {
			perror("recv error.\n");
			exit(1);
		}
		buf[n]='\0';

		// suddenly server shutdown
		if (n==0) {
			printf("Server is closed\n");
			close(sockfd);
			exit(0);
		}
		printf("\nServer: %s\n", buf);
	}
}

int main(int argc, char **argv) {
	// 1
	int sockfd;

	// 2
	pthread_t recv_tid;

	// 3
	struct sockaddr_in servaddr;

	// 4
	if (argc != 2) {
		perror("usage:tcpcli <IPaddress>");
		exit(1);
	}

	// 5
	if (sockfd = socket(AF_INET, SOCK_STREAM, 0) == -1) {
		perror("socket error");
		exit(1);
	}

	// 6
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	// 7
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0) {
		printf("inet_pton error for %s\n", argv[1]);
		exit(1);
	}

	// 8
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		perror("connect error");
		exit(1);
	}

	// 9 - message receive thread
	if (pthread_create(&recv_tid, NULL, recv_message, &sockfd) == -1) {
		perror("pthread create error.\n");
		exit(1);
	}

	// 10 - client message send
	char msg[MAX_LINE];
	memset(msg, 0, MAX_LINE);

	while(fgets(msg, MAX_LINE, stdin) != NULL) {
		if (strcmp(msg, "exit\n") == 0) {
			close(sockfd);
			exit(0);
		}
		if (send(sockfd, msg, strlen(msg), 0) == -1) {
			perror("send error.\n");
			exit(1);
		}
	}
}
