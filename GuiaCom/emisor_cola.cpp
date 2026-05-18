#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>

using namespace std;

struct mensaje{
	long tipo_mensaje;
	char texto[100];
};



int main() {
struct mensaje msj;
int id_cola;
key_t clave;
//creo la clave unica
clave=ftok("/tmp",65);
//ahora hay q crear la cola de mensajes o conectarse a la existente
//el ipc_creat indica q se crea si no existe y el 0666 son los permisos de escritura y lectura.
id_cola=msgget(clave,0666|IPC_CREAT);
if(id_cola==-1){
	cerr<<"error al crear la cola de mensajes"<<endl;
	return 1;
}
//ahora hay q hacer la preparacion del msj
msj.tipo_mensaje=1;//asignamos tipo 1
cin.getline(msj.texto,100);
//5 envio el mensaje a la cola
//los parametros son: id, puntero al struct y tamanio del dato, flags.
msgsnd(id_cola,&msj,sizeof(msj.texto),0);
cout<<"[Emisor] mensaje enviado satisfactoriamente"<<endl;
return 0;

}
