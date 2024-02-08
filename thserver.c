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
const int BACKLOG = 10;
const int LISTENQ = 6666;
const int MAX_CONNECT = 20;

// receive message of client and print in thread
void *recv_message(void *fd) {
	int sockfd = *(int *) fd;
	char buf[MAX_LINE];

	while(1) {
		memset(buf, 0, MAX_LINE);
		int n;
		if ((n=recv(sockfd, buf, MAX_LINE, 0)) == -1) {
			perror("recv error.\n");
			exit(1);
		}
		buf[n] = '\0';

		// client suddenly shutdown
		if(n==0) {
			printf("Client closed.\n");
			close(sockfd);
			exit(1);
		}
		//quit str => exit
		if (strcmp(buf, "exit") == 0) {
			printf("Client closed.\n");
			close(sockfd);
			exit(1);
		}
		printf("\nClient : %s\n", buf);
	}
}

int main() {
	// 1
	int listenfd, connfd;
	// 2
	pthread_t recv_tid;
	// 3
	struct sockaddr_in servaddr, cliaddr;
	// 4 - sock create
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket error.\n");
		exit(1);
	}
	// 5 - set sockaddr_in
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// bind error solve.
	int val = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof val) < 0) {
		perror("setsockopt");
		close(listenfd);
		return -1;
	}
	// 6 - sock create
	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind error.\n");
		exit(1);
	}
	// 7
	if (listen(listenfd, LISTENQ) < 0) {
		perror("listen error.\n");
		exit(1);
	}
	// 8 - client access accept
	socklen_t clilen = sizeof(cliaddr);
	if((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0) {
		perror("accept error.\n");
		exit(1);
	}
	// 9 - client addr print
	printf("server : got connection frm %s\n",  inet_ntoa(cliaddr.sin_addr));
	// 10 - message thread create
	if(pthread_create(&recv_tid, NULL, recv_message, &connfd)==-1) {
		perror("pthread create error.\n");
		exit(1);
	}
	// 11 - message send
	char msg[MAX_LINE];
	memset(msg, 0 , MAX_LINE);
	while(fgets(msg, MAX_LINE, stdin) != NULL) {
		if (strcmp(msg, "exit\n") == 0) {
			close(connfd);
			exit(0);
		}
		if (send(connfd, msg, strlen(msg), 0) == -1) {
			perror("send error.\n");
			exit(1);
		}
	}
}
