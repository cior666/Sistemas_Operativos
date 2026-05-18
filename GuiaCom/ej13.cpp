#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
//primero debo declarar los recursos compartidos
const int tam_vec=5;
int vector_compartido[tam_vec];
int pos_productor=0;
int pos_consumidor=0;
//declaro los semaforos
sem_t sem_vector_vacio;//controla los huecos libres para producir_dato
sem_t sem_vector_lleno;//controla los elementos listos para consumir
sem_t mutex_sc;//controla el acceso a la sec critica.
void*productor(void*arg){
	for(int i=0;i<15;i++) { 
		int dato=rand()%100;//produzco el dato
		sem_wait(&sem_vector_vacio);//espero si el vector esta totalmente lleno
		sem_wait(&mutex_sc);//pido permiso p la sec critica
		//secc critica
		vector_compartido[pos_productor&tam_vec]=dato;
		cout<<"el productor almaceno el valor: "<<dato<<"en la pos: "<<(pos_productor%tam_vec)<<endl;
		pos_productor++;
		sem_post(&mutex_sc);//salgo de la secc critica
		sem_post(&sem_vector_lleno);//aviso que hay un nuevo vector lleno (elemnto listo)
		sleep(rand()%2);//pausa aleatoria
	}
	return NULL;
}
void*consumidor(void*arg){
	for(int i=0;i<15;i++) { 
		sem_wait(&sem_vector_lleno);//esperar si el vector esta totalmente vacio
		//pido permiso a la secc critica
		sem_wait(&mutex_sc);
		int dato_extraido=vector_compartido[pos_consumidor%tam_vec];
		cout<<"el consumidor extrajo el valor: "<<dato_extraido<<"de la pos: "<<(pos_consumidor%tam_vec)<<endl;
		pos_consumidor++;
		sem_post(&mutex_sc);//salgo de la secc critica
		sem_post(&sem_vector_vacio);//avisa q hay un hueco libre
		sleep(rand()%2);
	}
	return NULL;
}
int main(int argc, char *argv[]) {
	pthread_t hilo_prod,hilo_cons;
	srand(time(NULL));
	sem_init(&sem_vector_vacio,0,tam_vec);//empieza en 5 osea todo vacio
	sem_init(&sem_vector_lleno,0,0);//empieza en 0 osea nada q consumir
	sem_init(&mutex_sc,0,1);//empieza en 1 osea llave disponible
	//creo los hilos
	pthread_create(&hilo_prod,NULL,productor,NULL);
	pthread_create(&hilo_cons,NULL,consumidor,NULL);
	//los joineo como siempre
	pthread_join(hilo_prod,NULL);
	pthread_join(hilo_cons,NULL);
	//destruyo los semaforos
	sem_destroy(&sem_vector_lleno);
	sem_destroy(&sem_vector_vacio);
	sem_destroy(&mutex_sc);
	return 0;
}



