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
	//aca tengo q generar con la misma clave q el emisor
	clave=ftok("/tmp",65);
	//y conectarme a la misma cola
	id_cola=msgget(clave,0666|IPC_CREAT);
	cout << "[Receptor] Esperando mensajes en la cola..." << endl;
	//ahora vamos a recibir el mensaje
	//los parametros son: id, puntero al struct, tamanio,tipo de mensaje a leer(el q inicialice como 1),flags(0)
	//el programa se pausa aca hasta q llegue un mensaje de tipo 1.
	msgrcv(id_cola, &msj, sizeof(msj.texto), 1, 0); 
	//ahora procedo a mostrar el mensaje
	cout<<"[Receptor] el mensaje extraido de la cola es: "<<msj.texto<<endl;
	//por ultimo paso como hicimos en el de tuberias con nombres, hay que destruir la cola (p limpiar memoria)
	msgctl(id_cola,IPC_RMID,NULL);
	cout<<"[Receptor] cola destruida"<<endl;
	return 0;
}



