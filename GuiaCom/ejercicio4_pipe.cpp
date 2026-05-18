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
using namespace std;
int main(int argc, char *argv[]) {
	int fd[2];//esto es para definir si es lectura o escritura
	pid_t pid;
	char mensaje_p[]="hola hijo ";
	char buffer_hijo[100]; //buffer donde el hijo guarda lo q lea.
	if(pipe(fd)==-1){
		cerr<<"error al crear la tuberia"<<endl;
		return 1;
	}
//creo proceso hijo
	pid=fork();
	if(pid<0){
		cerr<<"error al crear el hijo"<<endl;
	}else if(pid>0){
		close(fd[0]);//cerrramos el extremo de lectura ya q el padre solo va a escribir.
		cout<<"[padre] enviando msj al hijo"<<endl;
		//escribimos el mensaje en tuberia
		//y se usa strlen+1 para asegurar de enviar tb el espacio de \0
		write(fd[1],mensaje_p,strlen(mensaje_p)+1);
		//cerramos el extremo de escritura al terminar de enviar
		close(fd[1]);
		//ahora le agregamos el wait para q el hijo no quede huerfano
		wait(NULL);
		cout<<"[padre]el hijo ha terminado. finaliza programa"<<endl;
	}else{
		//codigo del hijo
		close(fd[1]);//cerramos escritura ya q solo lee
		read(fd[0],buffer_hijo,sizeof(buffer_hijo));//leemos con read y fd[0] porq es lectura y almacenamos en buffer hijo
		cout<<"[hijo] mensaje recibido: "<<buffer_hijo<<endl;
		//cerramos la lectura 
		close(fd[0]);
	}
	return 0;

	
	
}



