#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;
int main(int argc, char *argv[]) {
	int arreglo[20]={15, 42, 8, 33, 2, 19, 7, 56, 11, 4,90, 23, 14, 67, 88, 30, 5, 12, 39, 100};
	int nro_buscar;
	cout<<"Ingrese el nro a buscar: "<<endl;
	cin>>nro_buscar;
	pid_t pid;
	pid=fork();
	if(pid<0){
		cerr<<"error al crear el hijo"<<endl;
		return 1;
	}
	if(pid==0){
		//HIJO
		bool encontrado=false;
		for(int i=0;i<10;i++) { 
			if(arreglo[i]==nro_buscar){
				encontrado=true;
				cout<<"Soy el hijo y encontre el nro a buscar: "<<nro_buscar<<" en la pos: "<<(i+1)<<endl;
				break;
			}
		}
	}else{
		//PADRE
		bool encontrado=false;
		for(int i=10;i<20;i++) { 
			if(arreglo[i]==nro_buscar){
				encontrado=true;
				cout<<"soy el padre y encontre el nro a buscar: "<<nro_buscar<<" en la pos"<<(i+1)<<endl;
			}
		}
		if(!encontrado){
			cout<<"soy el padre y no encontre el nro a buscar en la 2da mitad"<<endl;
		}
		wait(NULL);
	}
	return 0;
}



