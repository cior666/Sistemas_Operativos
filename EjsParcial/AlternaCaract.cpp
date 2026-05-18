#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
sem_t sem_H1;
sem_t sem_H2;
void*A(void*arg){

	for(int i=0;i<10;i++) { 
		sem_wait(&sem_H1);//espero habilitacion para tirar la A
		cout<<"A"<<endl;
		sem_post(&sem_H2);
	}
	pthread_exit(NULL);
}
void*B(void*arg){
	for(int i=0;i<10;i++) { 
		sem_wait(&sem_H2);//espero la habilitacion de H1 para arrancar
		cout<<"B"<<endl;
		sem_post(&sem_H1);
	}
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
	pthread_t hilo1,hilo2;
	sem_init(&sem_H1,0,1);//arranca secuencia en A
	sem_init(&sem_H2,0,0);//lo prende el hilo 1 
	pthread_create(&hilo1,NULL,A,NULL);
	pthread_create(&hilo2,NULL,B,NULL);
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	sem_destroy(&sem_H1);
	sem_destroy(&sem_H2);
}



