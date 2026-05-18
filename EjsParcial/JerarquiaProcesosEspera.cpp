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
	int cant_hijos=3;
	pid_t pid;
	srand(time(NULL));
	cout<<"el padre de todos es: "<<getpid()<<"y voy a crear: "<<cant_hijos<<endl;
	for(int i=0;i<cant_hijos;i++) { 
		pid=fork();
		if(pid<0){
			cerr<<"error al crear los hijos"<<endl;
			return 1;
		}
		if(pid==0){
			//hijo: generamos un t aleatorio entre 1 y 3 seg
			int t_sueno=rand()%3+1;
			cout<<"soy el hijo: "<<(i+1)<<" Mi PID es: "<<getpid()<<" y el PID de mi padre es: "<<getppid()<<" voy a dormir: "<<t_sueno<<" seg"<<endl;
			sleep(t_sueno);
			exit(0);//tengo q terminar siosi el hijo aca, sino voy a tener nietos.
		}
	}
	//padre
	cout<<"soy el padre y ya cree los: "<<cant_hijos<<endl;
	//el padre hace un wait por cada hijo creado
	for(int i=0;i<cant_hijos;i++) { 
		wait(NULL);//cada llamada a wait pausa al padre hasta q muere el hijo
	}
	cout<<"soy el padre y todos mis hijos finalizaron..."<<endl;
	return 0;
}



