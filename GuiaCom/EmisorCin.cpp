#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <stdio.h>
#include <wait.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdlib>
#include <unistd.h>

#define SHMKEY 75

struct MemoriaCompartida { //este es el espacio de memoria compartido.
	int numeros[10];
	int listo; // 1 listo, 0 no listo.
};

using namespace std;
int main(int argc, char *argv[]) {
	int shmid;
	MemoriaCompartida *datos;
	//1 primero debo crear la region de memoria y obtener la direccion
	shmid=shmget(SHMKEY,sizeof(MemoriaCompartida),0777|IPC_CREAT);
	if(shmid==-1){
		cerr<<"Error al crear la memoria compartida"<<endl;
		return 1;
	}
	//2 una vez creada la region de memoria, debo enlazar al espacio de direccionamiento
	//del proceso. Enlazo el putero a memoria compartida.
	datos=(MemoriaCompartida*)shmat(shmid,0,0);
	datos->listo=0; //inicializo como no listo
	//3-Ahora que logre enlazar ya puedo generar los aleatorios.
	srand(time(0));
	cout<<"----Proceso emisor----"<<endl;
	cout<<"Generando y guardando los 10 : "<<endl;
	int nro=0;
	for(int i=0;i<10;i++){
		cin>>nro;
		datos->numeros[i]=nro;
		
	}
	for(int i=0;i<10;i++){
		cout<<datos->numeros[i]<<" ";
	}
	cout<<"\n Enviando seal de 'listo' al receptor...."<<endl;\
		//ahora que ya cargue y envie, debo cambiar el estado a 1.
		datos->listo=1; //cambio a listo
	//4- por ultimo separo la region del espacio de direccionamiento del proceso.
	shmdt(datos);
	return 0;
}



