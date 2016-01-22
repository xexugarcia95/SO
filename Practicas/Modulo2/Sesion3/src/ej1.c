#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		perror("\nError, parametro = un numero a comprobar\n");
		exit(-1);
	}
	pid_t pid;
	pid=fork();

	if(pid<0)
	{
		perror("Error en el fork\n");
		exit(-1);
	}	

	if(pid==0)
	{
		//Entramos en el proceso hijo
		printf("Proceso hijo, pid: %d ; pid del padre: %d. Comprueba si el numero introducido es par o impar\n",getpid(),getppid());
		int n=atoi(argv[1]); //atoi convierte un string en integer
		if(n%2==1)
			printf("EL numero %d es impar\n",n);
		else printf("El numero %d es par\n",n);
	}else if(pid)
	  {
		printf("\n Proceso padre, pid: %d , es igual al del proceso hijo. Comprobando si el numero es divisible por 4\n",getpid());
		int n=atoi(argv[1]);
	  	if(n%4==0)
			printf("El numero %d introducido es divisible por 4\n",n);
		else printf("El numero %d introducido es indivisible por 4\n",n);
	
 	  }
return 0;
}
