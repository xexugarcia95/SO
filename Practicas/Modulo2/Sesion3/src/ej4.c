#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	int j;
	pid_t PID;

	for(int i=0;i<5;i++){
		if((PID=fork())<0){
			perror("Error en fork\n");
			exit(-1);		
		}
		if(PID==0){
			printf("Soy el hijo PID = %i\n",getpid());
			exit(0);
		}
	}

	for(int i=4;i>=0;i--){
		PID=wait(&j);
		printf("Ha finalizado mi hijo con PID = %i\n",PID);
		printf("Solo me quedan %i hijos vivos\n",i);
	}
}
