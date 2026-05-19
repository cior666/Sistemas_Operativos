#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
pthread_mutex_t mutex;//declaro el mutex
void*H1(void*arg){
	for(int i=0;i<50;i++) { 
		pthread_mutex_lock(&mutex);//bloqueo hasta que imprimo los 50
		cout<<"Hola soy el hilo 1"<<endl;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}
void* H2(void*H2){
	for(int i=0;i<50;i++) { 
		pthread_mutex_lock(&mutex);
		cout<<"Hola soy el hilo 2"<<endl;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
	pthread_t hilo1,hilo2;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&hilo1,NULL,H1,NULL);
	pthread_create(&hilo2,NULL,H2,NULL);
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	pthread_mutex_destroy(&mutex);
}



