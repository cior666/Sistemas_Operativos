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
//para resolver de manera generica:
int N;
vector<vector<int>> A;
vector<vector<int>> B;
vector<vector<int>> C;
void*sumar_fila(void*arg){
	//primero tenemos que ver que fila toca
	int*valor=(int*)arg;
	int fila=*valor;
	//2do el hilo suma SOLO los elementos de su fila
	for(int i=0;i<N;i++){ 
		C[fila][i]=A[fila][i]+B[fila][i];
	}
	return NULL;
}

int main(int argc, char *argv[]) {
cout<<"Ingrese el tamanio de la matriz a crear: "<<endl;
cin>>N;
// usamos resize para declarar las matrices nuevas
A.resize(N, vector<int>(N, 1)); // Crea matriz NxN llena de 1s
B.resize(N, vector<int>(N, 2)); // Crea matriz NxN llena de 2s
C.resize(N, vector<int>(N, 0)); // Crea matriz NxN llena de 0s
vector<pthread_t> hilos(N);
vector<int>id_filas(N);
cout << "Creando " << N << " hilos..." << endl;

// creo hilos
for(int i = 0; i < N; i++) { 
	id_filas[i] = i; 
	pthread_create(&hilos[i], NULL, sumar_fila, (void*)&id_filas[i]);
}
// sincronizo
for(int i = 0; i < N; i++) { 
	pthread_join(hilos[i], NULL);
}
// Mostrar el resultado
cout << "\nResultado de la suma (Matriz C):" << endl;
for(int i = 0; i < N; i++) { 
	for(int j = 0; j < N; j++) { 
		cout << C[i][j] << " ";
	}
	cout << endl;
}
return 0;
}



