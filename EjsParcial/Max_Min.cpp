#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
int arreglo[15]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
void *H1(void*arg){
	int maximo=arreglo[0];
	for(int i=0;i<15;i++) { 
		if(maximo<arreglo[i]){
			maximo=arreglo[i];
		}
	}
	cout<<"El numero mas grande del arreglo es: "<<maximo<<endl;
	pthread_exit(NULL);
}
void* H2(void*arg){
	int minimo=arreglo[0];
	for(int i=0;i<15;i++) { 
		if(arreglo[i]<minimo){
			minimo=arreglo[i];
		}
	}
	cout<<"El nro mas pequenio es: "<<minimo<<endl;
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
	pthread_t h1,h2;
	pthread_create(&h1,NULL,H1,NULL);
	pthread_create(&h2,NULL,H2,NULL);
	pthread_join(h1,NULL);
	pthread_join(h2,NULL);
}



