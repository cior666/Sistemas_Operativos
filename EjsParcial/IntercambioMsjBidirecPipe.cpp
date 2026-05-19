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
int padre_hijo[2];
int hijo_padre[2];
if(pipe(padre_hijo)==-1){
	cerr<<"error al crear el pipe padre hijo"<<endl;
	return 1;
}
if(pipe(hijo_padre)==-1){
	cerr<<"error al crear el pipe hijo padre"<<endl;
	return 1;
}
pid_t pid=fork();
if(pid<0){
	cerr<<"error al crear el hijo"<<endl;
	return 1;
}
if(pid==0){
	//HIJO 
	//el hijo no escribe en el pipe del padre ni lee el propio
	close(padre_hijo[1]);
	close(hijo_padre[0]);
	int recibido;
	read(padre_hijo[0],&recibido,sizeof(recibido));//lee lo que manda el padre
	//ahora lo multiplico por dos
	int nro_nuevo=2*recibido;
	write(hijo_padre[1],&nro_nuevo,sizeof(nro_nuevo));//escribe el nuevo numero
	close(padre_hijo[0]);
	close(hijo_padre[1]);
	exit(0);
}else{
	//PADRE 
	//el padre no lee la propia y no escribe en la del hijo
	close(padre_hijo[0]);
	close(hijo_padre[1]);
	int enviado=333;
	write(padre_hijo[1],&enviado,sizeof(enviado));//envio el primer nro
	cout<<"Esperando operacion por parte de mi hijo..."<<endl;
	int nro_hijo;
	read(hijo_padre[0],&nro_hijo,sizeof(nro_hijo));
	cout<<"El nro devuelto por mi hijo es: "<<nro_hijo<<endl;
	//cierro al usar
	close(padre_hijo[1]);
	close(hijo_padre[0]);
	wait(NULL);
}
return 0;


}
