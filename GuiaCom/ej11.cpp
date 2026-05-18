#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
sem_t sem_h1;
sem_t sem_h2;
sem_t sem_padre;
void*H1(void*arg){
	sem_wait(&sem_h1);//espero que me den el verde para arrancar
	for(int i=0;i<=10;i++) { 
		sleep(rand()%2);
		cout<<"Soy el hilo 1 e imprimo mi primera tanda: "<<i<<endl;
	}
	sem_post(&sem_h2);//habilitamos a H2
	sem_wait(&sem_h1);//esperamos habilitacion de h2 para volver a ejecutar
	for(int i=21;i<30;i++) { 
		sleep(rand()%2);
		cout<<"soy el hilo 1 e imprimo mi segunda tanda: "<<i<<endl;
	}
	sem_post(&sem_h2);//paso el verde para la 2da iteracion de h2
	return NULL;
}
void*H2(void*arg){
	sem_wait(&sem_h2);//espero el primer verde de h1
	for(int i=10;i<=20;i++) { 
		sleep(rand()%2);
		cout<<"soy el hilo 2 e imprimo mi primera tanda: "<<i<<endl;
	}
	sem_post(&sem_h1);//doy el verde para la 2da tanta de h1
	sem_wait(&sem_h2);
	for(int i=31;i<=40;i++) { 
		sleep(rand()%2);
		cout<<"soy el hilo 2 e imprimo mi sda tanda: "<<i<<endl;
	}
	sem_post(&sem_padre);//le doy el verde al padre
	return NULL;
}
int main(int argc, char *argv[]) {
	pthread_t hilo1,hilo2;
	sem_init(&sem_h1,0,1);//arranca en verde porq es el primero
	sem_init(&sem_h2,0,0);
	sem_init(&sem_padre,0,0);
	pthread_create(&hilo1,NULL,H1,NULL);
	pthread_create(&hilo2,NULL,H2,NULL);
	//logica del padre
	sem_wait(&sem_padre);
	for(int i=41;i<=50;i++) { 
		sleep(rand()%2);
		cout<<"soy el proceso padre e imprimo: "<<i<<endl;
	}
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	//destruyo semaforos
	sem_destroy(&sem_h1);
	sem_destroy(&sem_h2);
	sem_destroy(&sem_padre);
	return 0;

}



