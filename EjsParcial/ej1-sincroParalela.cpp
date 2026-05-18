#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <vector>

using namespace std;
int nros[10];
sem_t sem_datos_listos;

void* H1(void*arg){
	cout<<"Ingrese los valores al vector: "<<endl;
	for(int i=0;i<10;i++) { 
		cin >> nros[i];
	}
	sem_post(&sem_datos_listos);//incrementa el semaforo para activar el hilo 2
	pthread_exit(NULL);
}
void*suma(void*arg){
	sem_wait(&sem_datos_listos);//cuando los datos esten listos en hilo1 puedo ejecutar la suma
	int sum=0;
	for(int i=0;i<10;i++) { 
		sum+=nros[i];
	}
	cout<<"la suma del vector es: "<<sum<<endl;
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
	//inicializo los hilos
	pthread_t hilo1,hilo2;
	//inicializo el semaforo
	sem_init(&sem_datos_listos,0,0);//arranca en 0 porq va a estar en 1 cuando este lleno
	//creo los hilos
	pthread_create(&hilo1,NULL,H1,NULL);
	pthread_create(&hilo2,NULL,suma,NULL);
	//los joineo
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	//borro el semaforo
	sem_destroy(&sem_datos_listos);
	return 0;

}



