#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

void*crea(void* arg){
	cout<<"Sistemas Operativos(Hilo)"<<endl;
	sleep(10);
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t hilos[8];
	cout<<"Soy el proc ppal, mi PID es: "<<getpid()<<endl;
	//creo los 8 hilos
	for(int i=0;i<8;i++) { 
		pthread_create(&hilos[i],NULL,crea,NULL);
	}
	for(int i=0;i<8;i++) { 
		pthread_join(hilos[i],NULL);
	}
	return 0;
}



