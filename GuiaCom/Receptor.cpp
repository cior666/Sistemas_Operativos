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

#define SHMKEY 75 //vuelvo a definir la key.
using namespace std;
struct MemoriaCompartida { //este es el espacio de memoria compartido.
	int numeros[10];
	int listo; // 1 listo, 0 no listo.
};
int main(int argc, char *argv[]) {
	int shmid;
	MemoriaCompartida*datos; 
	//-1 debo obtener el ID de la memoria comaprtida (sin el ipc create porq ya lo tengo creado)
	shmid=shmget(SHMKEY,sizeof(MemoriaCompartida),0777);
	if(shmid==-1){
		cerr<<"Error al crear la memoria compartida"<<endl;
		return 1;
	}
	//2- debo volver a enlazar la region al espacio de memoria del proceso.
	datos=(MemoriaCompartida*)shmat(shmid,0,0);
	cout<<"--Proceso del Receptor--"<<endl;
	cout<<"Esperando a que el Emisor escriba los datos..." << endl;
	
	//3- ahora debo ver el codigo de sicronizacion (digamos esperar hasta que este listo==1)
	while(datos->listo==0){
		sleep(1); //tiro pausa para no saturar.
	}
	//4- ahora que ya enlace puedo mostrar los valores almacenados.
	cout<<" Los valores recibidos desde la memoria compartida son: "<<endl;
	for(int i=0;i<10;i++) { 
		cout<<datos->numeros[i]<<" ";
	}
	cout<<endl;
	//5- debo desenlazar la region de memoria del proceso
	shmdt(datos);
	//6- eliminar la region de memoria compartida.
	shmctl(shmid,IPC_RMID,0);
	cout<<"Memoria compartida liberda."<<endl;
	return 0;
}



