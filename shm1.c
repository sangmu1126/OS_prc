#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int shmid;
	key_t key;
	char *shmAddr;

	key = ftok("hello shm", 1);
	shmid = shmget(key, 1023, IPC_CREAT|0644); // shared memory create
	// Create shared memory with "size" using key, and return ID of shm
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}
	printf("shmid : %d\n", shmid);
	shmAddr = (char*) shmat(shmid, NULL, 0); // shm connect
	// connect shmid in shmAddr, and return address
	strcpy(shmAddr, "hello Shared memory");
	
	return 0;
}
