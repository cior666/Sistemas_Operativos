#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <cstring>     // Para strlen()


using namespace std;
int main(int argc, char *argv[]) {
	int fd[2];
	pid_t pid;
	srand(time(NULL));
	//primero creo el pipe
	if(pipe(fd)==-1){
		cerr<<"error al crear el pipe"<<endl;
		return 1;
	}
	//dsp forkeo
	pid=fork();
	if(pid<0){
		cerr<<"error al crear el hijo"<<endl;
		return 1;
	}
	if(pid>0){
		int arreglo[15];
		close(fd[0]);//el padre no lee
		for(int i=0;i<15;i++) { 
			arreglo[i]=rand()%100+1;
			cout<<"los nros enviados fueron: "<<arreglo[i]<<endl;
		}
		write(fd[1],arreglo,sizeof(arreglo));//el padre escribe
		close(fd[1]);
		wait(NULL);
	}else{
		//hijo
		int arreglo_recib[15];
		close(fd[1]);//el hijo no escribe
		read(fd[0],arreglo_recib,sizeof(arreglo_recib));
		for(int i=0;i<15;i++) { 
			if(arreglo_recib[i]%5==0){
				cout<<"El nro recibido divisible por 5 es: "<<arreglo_recib[i]<<endl;
			}
		}
		close(fd[0]);
	}
	return 0;
}



