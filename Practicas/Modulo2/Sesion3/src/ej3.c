#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int nprocs=20;
	pid_t pid;
	pid=fork();
	for(int i=1;i< nprocs;i++){
		if(pid==-1)
			fprintf(stderr,"Could not create child % d: %s\n",i,strerror(errno));
			exit(-1);

		if(pid)
			printf("Proceso hijo, pid: %d ; pid del padre: %d\n",getpid(),getppid());
			
	}
exit(0);
}
