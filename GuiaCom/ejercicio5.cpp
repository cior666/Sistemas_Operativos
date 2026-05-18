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
int fd_p[2];//estructura para la ida
int fd_h[2];//estructura para la vuelta
pid_t pid;
	// Mensajes a enviar
	char mensaje_del_padre[] ="Hola wachin como estas?";
	char mensaje_del_hijo[] = "¡Hola Padre! Todo bien por aqui.";
	char buffer[100]; //ambos usan este espacio de memoria compartido 
	if(pipe(fd_p)==-1 || pipe(fd_h)==-1){
		cerr<<"error al crear la pipe"<<endl;
		return 1;
	}
//creo el proceso hijo
	pid=fork();
	if(pid<0){
		cout<<"error al crear el hijo"<<endl;
		
	}else if(pid>0){
		//codigo del padre
		//el padre no lee su propia tuberia pero si la del hijo. ademas
		//escribe en su tuberia pero no en la del hijo
		close(fd_p[0]);
		close(fd_h[1]);
		cout<<"enviando mensaje hijito:"<<endl;
		write(fd_p[1],mensaje_del_padre,strlen(mensaje_del_padre)+1);
		//a su vez, el padre recibe el mensaje del hilo
		read(fd_h[0],buffer,sizeof(buffer));
		cout<<"Soy el padre y el mensaje que me envia mi hijo es: "<<buffer<<endl;
		//cerramos los extremos ya q los terminamos de usar
		close(fd_p[1]);
		close(fd_h[0]);
		wait(NULL);
		cout<<"soy el Padre y el proceso de mi hijo a terminado"<<endl;
	}else{
		//codigo del hijo
		close(fd_p[1]);
		close(fd_h[0]);
		cout<<"recibiendo mensaje de mi padre:..."<<endl;
		read(fd_p[0],buffer,sizeof(buffer));
		cout<<"El mensaje que me envia mi padre es: "<<buffer<<endl;
		//ahora escribo el mensaje que le mando al padre
		cout<<"Soy el hijo y la rta a mi padre es:..."<<endl;
		write(fd_h[1],mensaje_del_hijo,strlen(mensaje_del_hijo)+1);
		//cierro los extremos usados:
		close(fd_p[1]);
		close(fd_h[0]);
	}
	return 0;
}



