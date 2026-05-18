#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
int contador=0;
pthread_mutex_t mutex_contador;//declaro el mutexS
void*incremento(void*arg){
	for(int i=0;i<1000;i++) { 
		pthread_mutex_lock(&mutex_contador);//es loq nos permite bloquear hasta q lo soltemos
		//secc critica
		contador++;
		//desbloqueamos
		pthread_mutex_unlock(&mutex_contador);
	}
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
	//inicializo los hilos
	pthread_t hilos[5];
	//inicializo el mutex
	pthread_mutex_init(&mutex_contador,NULL);
	//creo los hilos
	for(int i=0;i<5;i++) { 
		pthread_create(&hilos[i],NULL,incremento,NULL);
	}
	//joineo los hilos
	for(int i=0;i<5;i++) { 
		pthread_join(hilos[i],NULL);
	}
	//destruimos el mutex
	pthread_mutex_destroy(&mutex_contador);
	cout<<"el valor final del contador es: "<<contador<<endl;
	cout<<"el esperado es: 5000"<<endl;
}
