#include <sys/ipc.h>
#include <sys/shm.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(int c, char *v)
{
	key_t key = ftok("/tmp/mem.temp",1);
	if (key<0) perror("ftok");
	long int size = 1024*1024*5;

	int shmid = shmget(key, size, IPC_CREAT | O_EXCL | 0777);
	if (shmid <0 ) perror("shmget");

	int *p = shmat(shmid,NULL,0);
	if (*p==-1) perror("shmat");

	long int i;
	int  meg = 1024;
	//int step = meg/sizeof(char);
	
	for (i=0; i< meg; ++i)
	{
		p[i]=42;
	}
	
	return 0;
}
