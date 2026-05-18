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
#include <fcntl.h>      
#include <sys/stat.h>   
#include <unistd.h>
#include <semaphore.h>
using namespace std;
//el ej nos pide calcular la operatoria de multiplicacion de los nros q se encuentren entre dos numeros
//enteros q se leen por teclado y cree dos procesos ligeros que se estaran ejecutando concurrentemente.
//a) realizar la multiplicacion de los enteros comprendidos de la primera mitad del intervalo (entre ini y fin-ini/2).
//el resultado parcial obtenido lo acumulara sobre la variable de operacion global
//b) realizar la mult de los enteros comprenddos en la segunda mitad del intervalo (entre fin-ini/2 )+1 y fin. El resultado parcial
//obtenido lo acumulara sobre la variable global de operacion


//procedo a definir variables globales
long long operacion=1; //si es suma seria 0.
int ini,fin;
sem_t semaforo;//asi se declara el semaforo

//como me pide que cree dos procesos ligeros q se ejecutan concurrentemente, hago dos hilos
void*mitad1(void*arg){
	int mitad=ini+(fin-ini)/2;
	long long subtotal=1;
	//multiplico localmente para no bloquear nada de los otros procesos
	for(int i=ini;i<mitad;i++) { 
		subtotal*=i;
	}
	//parte del semaforo
	sem_wait(&semaforo);//pedimos la llave osea bloqueamos
	operacion=operacion*subtotal;//modificamos la variable global
	sem_post(&semaforo);//devolvemos la llave osea desbloqueamos
	return NULL;
}
void*mitad2(void*arg){
	int mitad=ini+(fin-ini)/2;//ahora va a empezar desde aca
	long long subtotal=1;
	for(int i=mitad;i<fin;i++) { 
		subtotal*=i;
	}
	//parte del semaforo
	sem_wait(&semaforo);//bloqueamos
	operacion=operacion*subtotal;//modificamos variable global
	sem_post(&semaforo);//desbloqueamos
	return NULL;
}
int main(int argc, char *argv[]) {
	pthread_t hilo1,hilo2;
	cout<<"Ingrese el nro inicial: "<<endl;
	cin>>ini;
	cout<<"Ingrese el nro final: "<<endl;
	cin>>fin;
	//inicializo el semaforo
	//como es compartido se pone un 0, valor inicial 1.
	sem_init(&semaforo,0,1);
	//creo los hilos
	pthread_create(&hilo1,NULL,mitad1,NULL);
	pthread_create(&hilo2,NULL,mitad2,NULL);
	//joineo los hilos
	pthread_join(hilo1,NULLSoperacion es: "<<operacion<<endl;
	//como con tuberias y mensajes, hay que destruir el semaforo cuando terminamos de usarlo.
	sem_destroy(&semaforo);
	return 0;
}



