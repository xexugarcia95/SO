#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

        //Comprobamos si se le ha pasado un pathname y unos permisos como parámetros
        if(argc<3) {
                //Si no se le han pasado los parámetros correctos muestra un mensaje de ayuda
                printf("Modo de uso: %s <programa> <simbolo> <archivo>\n\n", argv[0]);
                exit(1);
        } else {

                //Declaracion de variables
                char *str_command;
                char *str_file;
                int fd;

                //Extraemos el comando
                str_command = argv[1];
                str_file = argv[3];

                //Comprobamos el segundo parametro, tiene que ser < o >
                if (strcmp(argv[2], "<") == 0) {

                        //Redireccion de entrada
                        fd = open (str_file, O_RDONLY);
                        close(STDIN_FILENO);
                        if (fcntl(fd, F_DUPFD, STDIN_FILENO) == -1 ) perror ("fcntl falló");

                } else if (strcmp(argv[2], ">") == 0) {

                        //Redireccion de salida
                        fd = open (str_file, O_CREAT|O_WRONLY);
                        close (STDOUT_FILENO);
                        if (fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1 ) perror ("fcntl falló");


                } else {

                        printf("Debe pasarse \"<\" o \">\" con las comillas %s\n\n", argv[2]);

                        //Si no se le han pasado los parámetros correctos muestra un mensaje de ayuda
                        printf("Modo de uso: %s <programa> [opciones] [bg]\n\n", argv[0]);
                        exit(1);

                }

                //Ejecutamos el comando
            if( (execlp(str_command, "", NULL) < 0)) {

                        perror("Error en el execlp\n");
                        exit(-1);
                }

                //Cerramos el fichero
                close(fd);

        }

}
