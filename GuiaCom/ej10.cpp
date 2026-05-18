#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <stdio.h>
#include <wait.h>
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
#include <semaphore.h>
using namespace std;
	sem_t sem_h1;
	sem_t sem_h2;
	sem_t sem_padre;
void*H1(void*arg){
	sem_wait(&sem_h1);//pide permiso para actuar. como sem_h1 inicia en 1, pasa de largo y lo deja en 0.
	for(int i=0;i<=5;i++) {
		sleep(rand()%2);
		cout<<"soy el hilo 1 e imprimo: "<<i<<endl;
	}
	sem_post(&sem_h2);//cuando termina su trabajo le avisa al semaforo de h2
	return NULL;
}
void*h2(void*arg){
	sem_wait(&sem_h2);//se queda bloqueado hasta que h1 haga el sem_post
	for(int i=6;i<=10;i++) { 
		sleep(rand()%2);
		cout<<"soy el hilo H2 e imprimo: "<<i<<endl;
	}
	sem_post(&sem_padre);//cuando termina el trabajo le avisa al padre.
	return NULL;
}
int main(int argc, char *argv[]) {
	pthread_t hilo1,hilo2;
	//seteamos la semilla del rand
	srand(time(NULL));
	//declaramos los semaforos
	sem_init(&sem_h1,0,1);//va en 1 porq es el q arranca prendido
	sem_init(&sem_h2,0,0);//va en 0 porq tiene el rojo p ejecutarse
	sem_init(&sem_padre,0,0);//misma logica, se va a poner en verde cuando h2 habilite.
	//creamos los hilos
	pthread_create(&hilo1,NULL,H1,NULL);
	pthread_create(&hilo2,NULL,h2,NULL);
	//ahora viene la logica del padre
	sem_wait(&sem_padre);// se va a ejecutar cuando h2 termine
	for(int i=11;i<=15;i++) { 
		sleep(rand()%2);
		cout<<"soy el padre e imprimo: "<<i<<endl;
	}
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	//destruimos los semaforos
	sem_destroy(&sem_h1);
	sem_destroy(&sem_h2);
	sem_destroy(&sem_padre);
	return 0;
	
}



