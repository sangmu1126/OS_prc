#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
	int shmid;
	char *shmptr1, *shmptr2;
	int i;

	shmid = shmget(IPC_PRIVATE, 10*sizeof(char), IPC_CREAT|0666); // shm create
	if (shmid==-1){
		printf("shmget failed\n");
		exit(0);
	}
	// ---------- process create --------------
	if (fork()==0) { // children process
		shmptr1 = (char*) shmat(shmid, NULL, 0); // shm connect,reference
		for(i=0;i<10;i++)
			shmptr1[i] = i*10;
		shmdt(shmptr1); // Delete connction&ref between children process and shm
		exit(0);
	}
	else { // parent process
		wait(NULL);
		shmptr2 = (char*) shmat(shmid, NULL, 0); // shm connect, ref
		for (i=0;i<10;i++)
			printf("%d\n", shmptr2[i]);
		shmdt(shmptr2); // Delete connection&ref between parent process and shm
		if (shmctl(shmid, IPC_RMID,NULL)==-1) // shm control, IPC_RMID : delete shm in OS
			printf("shmctl failed\n");
	}
	return 0;
}
