#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
const unsigned long num_iter = 10; //veces q se produce
const int tam_vector = 5;          // tamanio del buffer
int vector[tam_vector];            // recurso compartido

int pos_productor = 0;
int pos_consumidor = 0;
int doble;

// declaro los semaforos
sem_t sem_huecos;    
sem_t sem_elementos; 
sem_t mutex_sc;
int producir_dato()
{
	static int dato = 0;
	dato++;
	return dato;
}
void duplicar_dato(int dato)
{
	doble = dato * 2;
	cout << "Dato duplicado: " << doble;
}
void *productor(void *p)
{
	for (unsigned long i = 0; i < num_iter; i++)
	{
		int dato = producir_dato(); // Produce un dato
		// 2. Control de Secuencia: hay lugar en el buffer?
		sem_wait(&sem_huecos);
		// 3. Control de Acceso: Pedimos la llave de la seccion critica
		sem_wait(&mutex_sc);
		vector[pos_productor % tam_vector] = dato;
		pos_productor++;
		cout << "Dato producido: " << dato;
		// 4. Liberamos la llave de la seccion critica
		sem_post(&mutex_sc);
		// 5. Control de Secuencia: Avisamos al consumidor que hay un nuevo elemento listo
		sem_post(&sem_elementos);
	}
	return NULL;
}
void *consumidor(void *p)
{
	for (unsigned long i = 0; i < num_iter; i++)
	{
		// 1. Control de Secuencia: hay algo para consumir?
		sem_wait(&sem_elementos);
		// 2. Control de Acceso: Pedimos la llave de la seccion critica
		sem_wait(&mutex_sc);
		// Consume el valor generado
		int dato = vector[pos_consumidor % tam_vector];
		pos_consumidor++;
		// 3. Liberamos la llave de la seccion critica
		sem_post(&mutex_sc);
		// 4. Control de Secuencia: Avisamos al productor que dejamos un hueco libre
		sem_post(&sem_huecos);
		
		duplicar_dato(dato);
	}
	return NULL;
}
int main(int argc, char **argv)
{
	pthread_t h1, h2;
	// Inicializamos los semaforos(Compartido=0, Valor Inicial)
	sem_init(&sem_huecos, 0, tam_vector); // Al principio todos los espacios (5) son huecos
	sem_init(&sem_elementos, 0, 0);       // Al principio hay 0 elementos listos
	sem_init(&mutex_sc, 0, 1);            // Mutex arranca en 1 (llave disponible)
	pthread_create(&h1, NULL, productor, NULL);
	pthread_create(&h2, NULL, consumidor, NULL);
	pthread_join(h1, NULL);
	pthread_join(h2, NULL);
	return 0;
}



