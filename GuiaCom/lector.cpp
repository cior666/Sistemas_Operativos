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
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>      
#include <sys/stat.h>   
#include <unistd.h>

using namespace std;
int main(int argc, char *argv[]) {
	const char* nombre_tuberia="mi_tuberia_fifo";
	char buffer[100];
	cout<<"[Lector] esperando para conectar con la tuberia.."<<endl;
	//siguiendo la logica q usabamos para pipes, abrimos la tuberia solo para lectura
	//esto se hace con el comando O_RDONLY
	int fd=open(nombre_tuberia,O_RDONLY);
	//ahora procedemos a leer lo que hay en la tuberia
	read(fd,buffer,sizeof(buffer));
	cout<<"[Lector] el mensaje recibido es: "<<buffer<<endl;
	//ceramos
	close(fd);
	//deslinkeamos la tuberia
	unlink(nombre_tuberia);
	cout<<"[Lector] tuberia destruida"<<endl;
	return 0;
}



