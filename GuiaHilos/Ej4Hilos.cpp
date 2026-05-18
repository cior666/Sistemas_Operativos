#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

int factorial(int num1){
	int result=1;
	for(int i=1;i<num1;i++) { 
		result*=i;
	}
	return result;
	//esto es una funcion pura de c++, no es un hilo, es una funcion aux para
	//calcular algo nomas.
}

void* hilo(void* arg){
	//este es el hilo que uso
	//declaro el valor como la referencia * para poder hallarlo.
	int* valor = (int*)arg;	
	int numero = *valor;
	int res = factorial(numero);
	cout << "El factorial de " << numero<< " es: " << res << endl;
	return NULL;
};
int main(int argc, char *argv[]) {
	pthread_t hilo1,hilo2;
	int num1;
	int num2;
	cout<<"Ingrese el primer numero: ";
	cin>>num1;
	cout<<" Ingrese el sdo numero: ";
	cin>>num2;
	pthread_create(&hilo1,NULL,hilo,(void*)&num1);
	pthread_create(&hilo1,NULL,hilo,(void*)&num2);
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);

}



