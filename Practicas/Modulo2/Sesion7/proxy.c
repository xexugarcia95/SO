#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

//Constantes
#define tamanio 1024
#define longitud 50

void bloqueodesbloqueo(int dbloqueo, int orden) {
	
	struct flock cerrar;
	
	cerrar.l_type= orden;
	cerrar.l_whence= SEEK_SET;
	cerrar.l_start= 0;
	cerrar.l_len = 0;
	
	if (fcntl(dbloqueo, F_SETLKW, &cerrar) == -1) {
		perror ("Proxy: problemas al bloquear para la impresion");
		exit(1);
	}
}

//Punto de entrada al programa
int main(int argc, char **argv){
 
	dup2(STDOUT_FILENO, STDERR_FILENO);

	int buf[tamanio];
	int nb;

	FILE *tmpFile = tmpfile();
	int orden=0;

	//Leer datos de la entrada estándar
	nb=read(STDIN_FILENO,buf,sizeof(buf));
	

	//Comprobamos si hay algo en el FIFO
	if(nb==-1){
		perror("Error en la lectura, en el proxy.\n");
		exit(EXIT_FAILURE);
	}
	
	//Si no da error se empieza a leer
	while(nb>0){

		if(fwrite(buf,sizeof(char),nb,tmpFile)==-1){

			perror("Error en fwrite la escritura del proxy1\n");
			exit(EXIT_FAILURE);

		}

		nb=read(STDIN_FILENO,buf,sizeof(buf));
		if(nb==-1){

			perror("Error en la lectura, en el proxy2\n");
			exit(EXIT_FAILURE);

		}
	}
	

	if(nb==0){
			
		nb=fread(buf,sizeof(char),sizeof(buf),tmpFile);

		if(nb==-1){
			perror("Error en fread la lectura en del proxy.\n");
			exit(EXIT_FAILURE);
		}

		while(nb>0){
			
			//comento el desbloqueo un momento
			//bloqueodesbloqueo(STDOUT_FILENO, F_WRLCK);
			if(write(STDOUT_FILENO,buf,nb)==-1){
				perror("Error en la escritura del proxy_1\n");
				exit(EXIT_FAILURE);
			}

			nb=fread(buf,sizeof(char),sizeof(buf),tmpFile);
			if(nb ==- 1) {
				perror("Error en la fread lectura en el proxy_2\n");
				exit(EXIT_FAILURE);
			}
			orden++;
			
		}

		if(nb==0){
			//bloqueodesbloqueo(STDOUT_FILENO, F_UNLCK);
			fclose(tmpFile);
			exit(EXIT_FAILURE);
		}
				
	}//if(nb==0)

}
