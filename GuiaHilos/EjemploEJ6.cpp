#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <vector>
using namespace std;
const int N=3;//defino tamanio matriz de ejemplo
//declaro las matrices de manera global para que puedan ser usadas x todos los hilos
int A[N][N];
int B[N][N];
int C[N][N];//resultado
void*sumar_fila(void*arg){
	//primero tenemos que ver que fila toca
	int*valor=(int*)arg;
	int fila=*valor;
	//2do el hilo suma SOLO los elementos de su fila
	for(int i=0;i<N;i++){ 
		C[fila][i]=A[fila][i]+B[fila][i];
	}
	sleep(5);
	return NULL;
}

int main(int argc, char *argv[]) {

	//para probar y entender la logica voy a hacerlo con dos matrices random_device
	for(int i=0;i<N;i++) { 
		for(int j=0;j<N;j++) { 
			A[i][j]=1;
			B[i][j]=1;
		}
	}
//como hicimos en ej 5, debo inicializar los vectores de hilos
// y los vectores de numeros, q en este caso serian los id de filas
vector<pthread_t> hilos(N);
vector<int>id_filas(N);
//los creo
for(int i=0;i<N;i++) { 
	id_filas[i]=i;//guardo los indices de la iteraciones para poder crear los hilos
	pthread_create(&hilos[i],NULL,sumar_fila,(void*)id_filas[i]);
}
//los sincronizo para esperar q todos terminen
for(int i=0;i<N;i++) { 
	pthread_join(hilos[i],NULL);
}
//una vez q esta todo hecho muestro la matriz
for(int i=0;i<N;i++) { 
	for(int j=0;j<N;j++) { 
		cout<<C[i][j]<<" ";
	}
	cout<<endl;
}
return 0;
}



