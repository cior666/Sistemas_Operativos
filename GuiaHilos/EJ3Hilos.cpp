#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;  
//ejercicio 3 pide hacer 3 hilos, uno que reciba un int, otro un float y otro un struct. Ademas hacer un contador global
//entonces pasamos a crear el struct, luego el contador y por ultimo los hilos
int contador_global;
struct registro{
	string cadena;
	int valor1;
	float valor2;
};
void*hilo1(void *arg){
	int numero=*(int*)arg;//esto es un casteo de void* a int* y lo desreferencio.
	while(1){
		contador_global++;
		cout<<"Hilo 1 de enteros: "<<numero<<"Contador global en: "<<contador_global<<endl;
		sleep(1);
	}
	return NULL;
}
void *hilo2(void *arg){
	float nf=*(float*)arg;//lo mismo que arriba
	while(1){
		contador_global++;
		cout<<"Hilo 2 de flotantes: "<<nf<<"contador global en: "<<contador_global<<endl;
		sleep(1);
	}
	return NULL;
}
void*hilo3(void*arg){
	struct registro* reg=(registro*)arg;//misma logica q los otros
	while(1){
		contador_global++;
		cout<<"Hilo 3 de struct: "<<reg->cadena<<" "<<"V1: "<<reg->valor1<<"V2: "<<reg->valor2<<"COntador global: "<<contador_global<<endl;
		sleep(1);
	}
	return NULL;
}
int main(int argc, char *argv[]) {
	//como en ej 1 debo inicializar los hilos
	pthread_t h1,h2,h3;
	//creo las variables a usar:
	int numero=42;
	float nf=3.14f;
	registro reg={"Sistemas operativos",12,3.69f};
	cout<<"Iniciando hilos, mi PID es: "<<getpid()<<endl;
	//ahora procedo a crear los hilos
	pthread_create(&h1,NULL,hilo1,(void*)&numero);
	pthread_create(&h2,NULL,hilo2,(void*)&nf);
	pthread_create(&h3,NULL,hilo3,(void*SSS)&reg);
	//los sincronizo con el join
	pthread_join(h1,NULL);
	pthread_join(h2,NULL);
	pthread_join(h3,NULL);
	return 0;
}



