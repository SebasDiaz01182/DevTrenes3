
#include<string.h>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include <stdlib.h>
#include "Conexiones.hpp"
#pragma once
using namespace std;

class NodoAVL{  
    public: 
    int codCiudad;
	string nombre;
	int reservacion;
	ArbolRN conexiones;
    NodoAVL *izquierda;  
    NodoAVL *derecha;  
    int FB;  
};  

//Funcion para obtener el balance de un nodo
  
int FB(NodoAVL *N){  
    if (N == NULL)  
        return 0;  
    return N->FB;  
}
int balanceo(NodoAVL *N){  
    if (N == NULL)  
        return 0;  
    return FB(N->izquierda) - FB(N->derecha);  
}  
  
//Obtiene el numero mayor para identificar a la hora de ingresar en el arbol
int numeroMayor(int a, int b); 

int numeroMayor(int a, int b){  
    return (a > b)? a : b;  
}  
 
NodoAVL* newNodoAVL(int codCiudad,string pnombre){  
    NodoAVL *nodoAVL = new NodoAVL(); 
    nodoAVL->codCiudad = codCiudad;
	nodoAVL->nombre = pnombre;
	nodoAVL->reservacion = 0; 
    nodoAVL->izquierda = NULL;  
    nodoAVL->derecha = NULL;  
    nodoAVL->FB = 1; 
    return(nodoAVL);  
}  
   
NodoAVL *RotacionDerecha(NodoAVL *y)  {  
    NodoAVL *raizN = y->izquierda;  
    NodoAVL *T2 = raizN->derecha;  
  
    raizN->derecha = y;  
    y->izquierda = T2;  
  
    y->FB = numeroMayor(FB(y->izquierda), 
    FB(y->derecha)) + 1;  
    raizN->FB = numeroMayor(FB(raizN->izquierda), 
    FB(raizN->derecha)) + 1;
    
    return raizN;  
}  
   
NodoAVL *RotacionIzquierda(NodoAVL *x) {  
    NodoAVL *raizN = x->derecha;  
    NodoAVL *T2 = raizN->izquierda;  
   
    raizN->izquierda = x;  
    x->derecha = T2;  
   
    x->FB = numeroMayor(FB(x->izquierda),     
    FB(x->derecha)) + 1;  
    raizN->FB = numeroMayor(FB(raizN->izquierda),  
    FB(raizN->derecha)) + 1;  
  
    return raizN;  
}  
  

NodoAVL* insertarnodoAVL(NodoAVL* nodo, int codCiudad,string nombre)  {  
	//Si la raiz es nula
    if (nodo == NULL){
    	return(newNodoAVL(codCiudad,nombre));  
	}//else
	if (codCiudad < nodo->codCiudad){
    	nodo->izquierda = insertarnodoAVL(nodo->izquierda, codCiudad ,nombre);  
	}else if (codCiudad > nodo->codCiudad){
    	nodo->derecha = insertarnodoAVL(nodo->derecha, codCiudad,nombre);  
	}else{
		return nodo;  
	}   
    nodo->FB = 1 + numeroMayor(FB(nodo->izquierda),  
    FB(nodo->derecha));  
  
    int balance = balanceo(nodo);  //Esta variable sera la del balance
    
    //Casos de las rotaciones
    //ROTACION IZQUIERDA 
    if (balance > 1 && codCiudad < nodo->izquierda->codCiudad){
    	return RotacionDerecha(nodo);  
	}
    // ROTACION DERECHA
    if (balance < -1 && codCiudad > nodo->derecha->codCiudad){
    	return RotacionIzquierda(nodo);  
	} 
    //ROTACION DOBLE IZQUIERDA 
    if (balance > 1 && codCiudad > nodo->izquierda->codCiudad){  
        nodo->izquierda = RotacionIzquierda(nodo->izquierda);  
        return RotacionDerecha(nodo);  
    } 
    //ROTACION DOBLE DERECHA
    if (balance < -1 && codCiudad < nodo->derecha->codCiudad){  
        nodo->derecha = RotacionDerecha(nodo->derecha);  
        return RotacionIzquierda(nodo);  
    }  
  
    return nodo;  
} 


bool ExisteCiudad(NodoAVL *R,int ciudad){
	 if(R==NULL){
	 	return false;
	 }
	 else if(R->codCiudad==ciudad){
	 	return true;
	 }
	 else if(ciudad<=R->codCiudad){
	 	return ExisteCiudad(R->izquierda,ciudad);
	 }
	 else{
	 	return ExisteCiudad(R->derecha,ciudad);
	 }
}

