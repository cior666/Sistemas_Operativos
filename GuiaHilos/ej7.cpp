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
const int N=3;
int A[N][N];
int B[N][N];
int C[N][N];

void*mult_fila(void*arg){
	int*valor=(int*)arg;
	int fila=*valor;
	for(int i=0;i<N;i++) { 
			C[fila][i]=A[fila][i]*B[fila][i];
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	//inicializo

vector<pthread_t>hilos(N);
vector<int>id_fila(N);
//creo
for(int i=0;i<N;i++) { 
	id_fila[i]=i;//creo mi vector de fila
	pthread_create(&hilos[i],NULL,mult_fila,(void*)&id_fila[i]);//creo mis hilos con mi vector fila
}
//sincronizo
for(int i=0;i<N;i++) { 
	pthread_join(hilos[i],NULL);
}
//muestro resultados
cout<<"MATRIZ RESULTADO OBTENIDA: "<<endl;
for(int i=0;i<N;i++) { 
	for(int j=0;j<N;j++) { 
		cout<<C[i][j];
	}
	cout<<endl;
}
return 0;
}



