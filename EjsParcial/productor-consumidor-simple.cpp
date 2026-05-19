#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
//variable global
int buffer;
//semaforos a usar
sem_t sem_vacio;
sem_t sem_lleno;
void*productor(void*arg){
	for(int i=0;i<5;i++) { 
		int nro_gen=rand()%100+1;
		sem_wait(&sem_vacio);//espero que el buffer este vacio
		//secc critica
		buffer=nro_gen;
		cout<<"el prod genero y guardo en el buffer el nro: "<<nro_gen<<endl;
		sem_post(&sem_lleno);//doy el ok para avisarle a consumidor q ya hay un dato
		sleep(1);
	}
	pthread_exit(NULL);
}
void* consumidor(void*arg){
	for(int i=0;i<5;i++) { 
		sem_wait(&sem_lleno);//espero que el buffer tenga un dato creado por productor
		int dato_leido=buffer;
		cout<<"el consumidor leyo del buffer el nro: "<<dato_leido<<endl;
		sem_post(&sem_vacio);//aviso q el dato ya fue leido esto el buffer vuelve a estar vacio
		sleep(1);
	}
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
	pthread_t hilo1,hilo2;
	sem_init(&sem_vacio,0,1);//arranca en 1 porq hay 1 espacio al iniciar
	sem_init(&sem_lleno,0,0);//arranca en 0 porq no hay espacios al iniciar
	pthread_create(&hilo1,NULL,productor,NULL);
	pthread_create(&hilo2,NULL,consumidor,NULL);
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	sem_destroy(&sem_vacio);
	sem_destroy(&sem_lleno);
	cout<<"fin de simulacion"<<endl;
}



