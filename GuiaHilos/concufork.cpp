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
cout<<"Soy el padre el PID es: "<<getpid()<<endl;

for(int i=0;i<8;i++){
	pid_t pid=fork(); //forkeo y creo un nuevo proceso
	if(pid==0){
		//si el pid es 0 sabemos q estamos en un proceso hijo
		cout<<"Sistemas OPerativos(Hijo PID: "<<getpid()<<endl<<")";
		sleep(10);
		return 0;//esto es onligatorio porq el hijo termina aca y no sigue ejecutando.
	}else if(pid<0){
		cerr<<"Error al crear el proceso manito"<<endl;
	}
}
//Ahora hago el codigo del proceso padre
//el padre tiene que esperar que todos sus hijos terminen.
//para ello uso la funcion wait() que solo atrapa un proceso hijo por cada vez
for(int i=0;i<8;i++) { 
	wait(NULL); 
}
return 0;
}









