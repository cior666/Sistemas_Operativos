#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <cstring>     // Para strlen()
#include <cctype>      // Para toupper()

using namespace std;
int main(int argc, char *argv[]) {
	int padre_hijo[2];
	int hijo_padre[2];
	pid_t pid;
	if(pipe(padre_hijo)==-1){
		cerr<<"error al crear la pipe padre-hjo"<<endl;
		return 1;
	}
	if(pipe(hijo_padre)==-1){
		cerr<<"error al crear la pipe hijo_padre"<<endl;
		return 1;
	}
	pid=fork();
	if(pid<0){
		cerr<<"error al crear el hijo"<<endl;
		return 1;
	}
	if(pid==0){
		//HIJO
		//como no voy a escribir en la pipe del padre 
		close(padre_hijo[1]);
		//y tmp voy a leer en la del hijo
		close(hijo_padre[0]);
		char buffer[256];
		//primero debo leer el msj del padre:
		read(padre_hijo[0],buffer,sizeof(buffer));
		cout<<"El mensaje que me envia mi padre es: "<<buffer<<endl;
		for(int i=0;i<=sizeof(buffer);i++) { 
			buffer[i]=toupper(buffer[i]);
		}
		cout<<"Enviando mensaje convertido: "<<endl;
		write(hijo_padre[1],buffer,strlen(buffer)+1);
		//cerramos por convencion
		close(padre_hijo[0]);
		close(hijo_padre[1]);
		exit(0);
	}else{
		//PADRE 
		//no voy a escribir en el hijo asique:
		close(hijo_padre[1]);
		//tmp va a leer de su propia tuberia
		close(padre_hijo[0]);
		string mensaje_ingresado;
		char buffer_rta[256];
		cout<<"Ingrese el texto a transmitir: "<<endl;
		getline(cin,mensaje_ingresado);
		//ahora debo enviarle el mensaje al hijo
		write(padre_hijo[1],mensaje_ingresado.c_str(),mensaje_ingresado.length()+1);
		//luego debo leer la rta en mayuscula del hijo 
		read(hijo_padre[0],buffer_rta,sizeof(buffer_rta));
		cout<<"Soy el padre y la rta de mi hijo es: "<<buffer_rta<<endl;
		close(hijo_padre[0]);
		close(padre_hijo[1]);
		wait(NULL);
	}
	return 0;
}



