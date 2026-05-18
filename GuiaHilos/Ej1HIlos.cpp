#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

// Funcion primer hilo
void* imprimir_numeros(void* arg) {
	for (int i = 1; i <= 10; i++) {
		cout <<i << " ";
	}
	cout << endl;
	pthread_exit(NULL); // Finalizo el hilo.
}

void *genera_abecedario(void*arg){
	for(char c='A';c<='Z';c++){
		cout<<c<<" ";
	}
	cout<<endl;
	pthread_exit(NULL); //termino el hilo
}


int main(int argc, char *argv[]) {
	//ahora que ya tengo las funciones que los hilos van a usar tengo que crear ambos hilos.
	pthread_t hilo1,hilo2; //los inicializo
	pthread_create(&hilo1,NULL,imprimir_numeros,NULL);
	pthread_create(&hilo2,NULL,genera_abecedario,NULL);
	//una vez que estan creados los hilos debo unirlos hasta que terminen los dos de ejecutarse.
	//El hilo ppal se suspende hasta que hilo1 e hilo2 terminen de ejecutarse.
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	cout<<"Ambos hilos terminaron"<<endl;
	return 0;
}



