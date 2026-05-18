#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <vector>

using namespace std;
//el ej 5 me pide modificar el codigo del ej 4 para q no este limitado solo a 2
//factoriales para calcular sino q sean mas de forma concurrente.
int factorial(int num1){
	int result=1;
	for(int i=1;i<=num1;i++) {  
		result*=i;
	}
	return result;
}
//ahora creo el hilo
void*hilo(void*arg){
	int *valor=(int*)arg;//aca apunto el puntero a la caja generica arg q es donde esta la direcc
	//de memoria de mi dato. EL (int*)arg se llama "Casting".
	//el int*valor lo q hacemos es guardar la direccion de memoria en ese valor
	int numero=*valor;
	//aca lo q digo es anda a la direcc guardada en valor y traeme lo q esta almacenado
	int res=factorial(numero);
	cout<<"el factorial de: "<<numero<<"es: "<<res<<endl;
	return NULL;
}

int main(int argc, char *argv[]) {
	//verificacion de que el usuario haya ingresado al menos un numero
	if(argc<2){
		cerr<<"Error.Uso correcto: ./programa num1,num2,num3.."<<endl;
		return 1;
	}
//primero hay que determinar cuantos hilos tengo que crear, a esto lo hago con:
	int cantidad_hilos=argc-1;
//dsp tengo q hacer la creacion de los arreglos dinamicos segun cant de param.
	vector<pthread_t>hilos(cantidad_hilos);//digamos q hago un vector para almacenar hilos
	vector<int> numeros(cantidad_hilos);
//ahora que ya tengo creados los slots donde van los hilos y los slots de cant de numeros puedo crear los hilos.
for(int i=0;i<cantidad_hilos;i++) { 
	//argv es el nombre del programa como tal, los nros comienzan en pos [1]
	numeros[i]=atoi(argv[i+1]);
	// envio la direc de posicion del arreglo, asegurando que cada hilo tenga su propio dato
	pthread_create(&hilos[i],NULL,hilo,(void*)&numeros[i]);
}
//como siempre una vez q los creo debo joinearlos.
for(int i=0;i<cantidad_hilos;i++) { 
	//bloqueo el main hasta que el hilo en la pos 'i' termine
	pthread_join(hilos[i],NULL);
	//a medida q se van desbloqueando el hilo principal avisa quien termino.
	cout<<"[Hilo principal] el hilo con ID: "<<hilos[i]<<"q calculaba el fact de: "<<numeros[i]<<"ha finalizado"<<endl;
}
cout<<"todos los hilos terminaron. Proceso principal finalizado"<<endl;
}



