#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <sys/ipc.h>   // Para las constantes IPC
#include <sys/shm.h>   // Para shmget, shmat, shmdt, shmctl
#include <unistd.h>    // Para fork()
#include <sys/wait.h>  // Para wait()
#include <cstdlib>     // Para exit()

using namespace std;
int main(int argc, char *argv[]) {
	//la memoria compartida siempre se crea antes de forkear.
	// IPC_PRIVATE: Clave especial para compartir solo entre procesos emparentados (Padre e Hijo)
	// sizeof(int): Solo necesitamos espacio para guardar un nro entero
	// IPC_CREAT | 0666: Permisos de lectura y escritura
	int shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
	if (shm_id < 0) {
		cerr << "Error al solicitar memoria compartida." << endl;
		return 1;
	}
	pid_t pid = fork();
	if(pid==0){
		//HIJO: escritor
		int*memoria_compartida=(int*)shmat(shm_id,NULL,0);//acoplamos a la memoria compartida y casteamos
		cout<<"Soy el hijo y naci. Ahora mismo estoy escribiendo el nro en la memoria compartida..."<<endl;
		*memoria_compartida=2024;
		//una vez que escribo tengo q desacomplarme porq termine de usarla
		shmdt(memoria_compartida);
		//salgo del hijo
		exit(0);
	}else{
		//estoy en el padre osea leo
		wait(NULL);//sincronizo con el padre
		//ahora debo acomplarme a la memoria compartida
		int*memoria_compartida=(int*)shmat(shm_id,NULL,0);
		cout<<"Soy el padre y estoy leyendo la memoria compartida..."<<endl;
		cout<<"El valor que guardo mi hijo es: "<<*memoria_compartida<<endl;
		//desacoplo memoria_compartida
		shmdt(memoria_compartida);
		//por ultimo destruyo la memoria compartida para devolversela al SO
		shmctl(shm_id,IPC_RMID,NULL);
	}
	return 0;
}



