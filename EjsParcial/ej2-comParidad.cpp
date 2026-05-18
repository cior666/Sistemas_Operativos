#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
int main(int argc, char *argv[]) {
int fd[2];
pid_t pid;
//hay q crear el pipe antes de forkear y crear el hijo
if(pipe(fd)==-1){
	cerr<<"error al crear el pipe"<<endl;
	return 1;
}
srand(time(NULL));
pid=fork();
if(pid<0){
	cout<<"error al crear el hijo"<<endl;
	return 1;
}
if(pid==0){
	close(fd[1]);//porq no escribe
	int nro_recibido;
	read(fd[0],&nro_recibido,sizeof(nro_recibido));
	cout<<"soy el hijo y recibi el nro: "<<nro_recibido<<endl;
	if(nro_recibido%2==0){
		cout<<"El nro que recibi es par"<<endl;
	}else{
		cout<<"El nro es impar"<<endl;
	}
	close(fd[0]);//cierro lectura del hijo
}else{
	//codigo del padre
	close(fd[0]);//porq no lee solo escribe
	int nro_gen=rand()%100+1;
	cout<<"Soy el padre y genere el nro: "<<nro_gen<<" enviandolo a mi hijo..."<<endl;
	write(fd[1],&nro_gen,sizeof(nro_gen));
	close(fd[1]);//cerramos extremo escritura
	wait(NULL);
	cout<<"Soy el padre y mi hijo ha terminado con su tarea.."<<endl;
}
return 0;

}
