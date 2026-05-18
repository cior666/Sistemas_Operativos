S#include <iostream>
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

//este ejercicio es de pipe, pero la logica de definirlo es parecida, debo usar size
#define SIZE 512
using namespace std;
int main(int argc, char *argv[]) {
	pid_t pid;
	int fd[2], largo;
	char buffer[SIZE];
	//1 creo la tuberia
	if(pipe(fd)==-1){
		cerr<"Error al crear la pipa"<<endl;
		return 1;
	}
	//creo el proceso hijo
	pid=fork();
	if(pid==-1){
		cerr<<"Error al crear el proceso hijo"<<endl;
		return 1;
	}
	if(pid!=0)
	{
		//esta parte corresponde al PADRE
		//esto es buena practica no debo hacerlo siempre siempre.
		//Cierro el lado de lectura del pipe (no lo va a usar)
		close(fd[0]);
		//ahora defino el mensaje a usar.
		strcpy(buffer,"Sist Op-Mensaje de prueba");
		//envio el mensaje por el lado de escritura del pipe.
		//se suma +1 en el strlen porq debo incluir el tamanio nulo '\0'
		write(fd[1],buffer,(strlen(buffer)+1));
		cout<<"Mensaje enviado por el padre"<<endl;
		//esto es buena practica no debo hacerlo siempre siempre.
		close(fd[1]);
		//ahora debo esperar que el hijo termine para evitar procesos zombis
		waitpid(pid,NULL,0);
	}else{
		//esta parte corresponde al HIJO
		close(fd[1]);
		//leo el msj del lado de lectura del pipe.
		largo=read(fd[0],buffer,sizeof(buffer));
		cout<<"Mensaje recibido por el hijo"<<endl;
		cout<<"Mensaje: "<<buffer<endl;
		close(fd[0]);
	}
	return 0;
}



