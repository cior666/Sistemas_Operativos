#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <stdio.h>
#include <wait.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>      
#include <sys/stat.h>   
#include <unistd.h>

using namespace std;
int main(int argc, char *argv[]) {
	const char* nombre_tuberia="mi_tuberia_fifo";
	char mensaje[100];
	//creo la tuberia con el nombre y los permisos 0666 q son lectura y escritura para todos.
	mkfifo(nombre_tuberia,0666);
	cout<<"[escritor] tuberia creada. Esperando q el lector lea..."<<endl;
	//ahora hay q seguir masomenos la logica que usabamos antes, entonces abrimos solo para escritura
	//esto se hace usando el comando O_WRONLY
	//el programa se pausara aqui hasta que el otro programa abra la tuberia para leer.
	int fd=open(nombre_tuberia,O_WRONLY);
	cout<<"Ingrese el texto a enviar: ";
	cin.getline(mensaje,100);
	//ahora hay q escribir el mensaje en la tuberia.
	write(fd,mensaje,strlen(mensaje)+1);
	cout<<"[Escritor] mensaje enviado."<<endl;
	//finalmente cerramos como siempre
	close(fd);
	return 0;
}



