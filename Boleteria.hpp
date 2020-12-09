#include <iostream>
#include <fstream>
#include <stdlib.h>
#include<string>
#include "Usuarios.hpp"
#include "UsuarioReservacion.hpp"
#pragma once
using namespace std;

class nodoBoleteria { 

public:
    nodoBoleteria(int iD , int cTren) 
    {
        codTren = cTren;
        identificacion = iD;
        siguiente = NULL;
        reservacion = 0;
    }

    nodoBoleteria(int iD , int cTren , nodoBoleteria* signodoBoleteria) 
    {
        identificacion = iD;
        codTren = cTren;
        siguiente = signodoBoleteria;
    }


public: // atributos
    int identificacion;
    int codTren;
    int reservacion;
    nodoBoleteria* siguiente; 
};
typedef nodoBoleteria* pnodoBoleteria; 

class listaBoleteria {
public:
    listaBoleteria()
    {
        primero = NULL;

    }
    ~listaBoleteria();
    void InsertarInicio(int identificacion,  int codTren);
    void InsertarFinal(int identificacion,  int codTren);
    void InsertarPos(int identificacion,  int codTren, int pos);
    bool ListaVacia() { return primero == NULL; }
    void Imprimir();
    void Mostrar();
    void Primero();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    int largoLista();
    void CrearColaPasajeros();
    bool InsertarCiudad(int codCiudad, int codPais);
    void ModCiudad(int codCiudad, int codPais);
public:
    pnodoBoleteria primero; 

};

listaBoleteria::~listaBoleteria(){
    pnodoBoleteria aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }

}

int listaBoleteria::largoLista() { 
    int cont = 0;

    pnodoBoleteria aux; 
    aux = primero;
    if (ListaVacia()) {
        return cont;
    }
    else {
        while (aux != NULL) {
            aux = aux->siguiente;
            cont++;
        }
        return cont;
    }

}

void listaBoleteria::InsertarInicio(int identificacion,  int codTren){
    if (ListaVacia())
        primero = new nodoBoleteria(identificacion, codTren);
    else
        primero = new nodoBoleteria(identificacion, codTren, primero);
}

void listaBoleteria::InsertarFinal(int identificacion,  int codTren){
    if (ListaVacia())
        primero = new nodoBoleteria(identificacion, codTren);
    else
    {
        pnodoBoleteria aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = new nodoBoleteria(identificacion, codTren);
    }
}

void listaBoleteria::InsertarPos(int identificacion,  int codTren, int pos){
    if (ListaVacia())
        primero = new nodoBoleteria(identificacion, codTren);
    else {
        if (pos <= 1) {                    
            pnodoBoleteria nuevo = new nodoBoleteria(identificacion, codTren);
            nuevo->siguiente = primero;
            primero = nuevo;
        }
        else
        {
            if (pos >= largoLista())
                InsertarFinal(identificacion, codTren);
            else
            {

                pnodoBoleteria aux = primero;
                int i = 2;
                while ((i != pos) && (aux->siguiente != NULL)) {
                    i++;
                    aux = aux->siguiente;
                }
                pnodoBoleteria nuevo = new nodoBoleteria(identificacion, codTren); 
                nuevo->siguiente = aux->siguiente; 
                aux->siguiente = nuevo;
            }

        }
    }
}

void listaBoleteria::BorrarFinal(){
    if (ListaVacia()) {
        cout << "No hay elementos en la lista" << endl;

    }
    else {
        if (primero->siguiente == NULL) {
            primero = NULL;
        }
        else {

            pnodoBoleteria aux = primero;
            while (aux->siguiente->siguiente != NULL) {
                aux = aux->siguiente;

            }

            pnodoBoleteria temp = aux->siguiente;
            aux->siguiente = NULL;


            delete temp;
        }
    }
}

void listaBoleteria::BorrarInicio(){
    if (ListaVacia()) {
        cout << "No hay elementos en la lista" << endl;

    }
    else
    {
        if (primero->siguiente == NULL)
        {
            pnodoBoleteria temp = primero;
            primero = NULL;
            delete temp;
        }
        else
        {

            pnodoBoleteria aux = primero;
            primero = primero->siguiente;
            delete aux;
        }
    }
}


void listaBoleteria::borrarPosicion(int pos) {
    if (ListaVacia()) {
        cout << "Lista vacia" << endl;
    }
    else {
        if ((pos > largoLista()) || (pos < 0)) {
            cout << "Error en posicion" << endl;
        }
        else {
            if (pos == 1) {
                primero = primero->siguiente;
            }
            else {
                int cont = 2;
                pnodoBoleteria aux = primero;
                while (cont < pos) {
                    aux = aux->siguiente;
                    cont++;
                }
                aux->siguiente = aux->siguiente->siguiente;
            }
        }
    }
}


void listaBoleteria::Mostrar(){
    nodoBoleteria* aux;
    if (primero == NULL)
        cout << "No hay elementos";
    else
    {
        aux = primero;
        while (aux)
        {
            cout << aux->identificacion <<" / "<<aux->codTren<< "-> ";
            aux = aux->siguiente;
        }
        cout << endl;
    }
}

void listaBoleteria::CrearColaPasajeros(){
	bool eleccion = true;
	int eleccion2;
	while(eleccion){
		int iDPasajeros; cout<<"Ingrese su identificacion: "; cin>>iDPasajeros; cout<<endl;
		int tipoTren; cout<<"Ingrese el tipo de tren al que desea abordar: "; cin>>tipoTren; cout<<endl;
		//Cola inserto al final y elimino al inicio
		InsertarInicio(iDPasajeros, tipoTren);
		cout<<"Si desea seguir ingresando usuarios digite 1 de lo contrario digite 2: "; cin>>eleccion2; cout<< endl;
		if(eleccion2==2){
			eleccion= false;
		}
	}
}


bool listaBoleteria::InsertarCiudad(int codCiudad, int codPais){
	if (ListaVacia()){
		primero = new nodoBoleteria(codPais, codCiudad);
	}
    else{
    	pnodoBoleteria aux = primero;
    	while(aux != NULL){
    		if(aux->codTren==codCiudad){
    			return false;
			}else{
				aux= aux->siguiente;
			}
		}primero = new nodoBoleteria(codPais, codCiudad, primero);
		return true;
	}
}

void listaBoleteria::ModCiudad(int codCiudad, int codPais){
	pnodoBoleteria aux = primero;
	while(aux != NULL){
		if(aux->codTren==codCiudad){
			aux->reservacion++;
			break;
		}else{
			aux= aux->siguiente;
		}
	}
}

string Ciudad(listaBoleteria &ciudad, pNodoBinario &paises){
	pnodoBoleteria aux = ciudad.primero;
	pnodoBoleteria mayor = ciudad.primero;
	while(aux!=NULL){
		if(aux->reservacion>mayor->reservacion){
			mayor = aux; 
		}
		aux= aux->siguiente;
	}
	return DevolverCiudad2(DevolverPais(paises, mayor->identificacion)->ciudad,mayor->codTren);
}



