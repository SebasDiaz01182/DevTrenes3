#include <iostream>
#include <fstream>
#include <stdlib.h>
#include<string>
#pragma once
using namespace std;

class nodoReservacion { 

public:
    nodoReservacion(int tipTren, int tren, int ruta, int asientos, int precio ) {
        codtipTren = tipTren;
        codTren = tren;
        codRuta = ruta;
        cantAsientos = asientos;
        precioU = precio;
        siguiente = NULL;
    }

    nodoReservacion(int tipTren , int tren, int ruta, int asientos, int precio ,nodoReservacion* signodoReservacion) {
        codtipTren = tipTren;
        codTren = tren;
        codRuta = ruta;
        cantAsientos = asientos;
        precioU = precio;
        siguiente = signodoReservacion;
    }

public: // atributos
    int codtipTren;
    int codTren;
    int codRuta;
    int cantAsientos;
    int precioU;
    nodoReservacion* siguiente;
};
typedef nodoReservacion* pnodoReservacion; 

class ListaReservacion {
public:
    ListaReservacion(){
        primero = NULL;
    }
    ~ListaReservacion();
    void InsertarInicio(int tipTren, int tren, int ruta, int asientos, int precio );
    void InsertarFinal(int tipTren, int tren, int ruta, int asientos, int precio );
    bool ListaVacia() { return primero == NULL; }
    void Imprimir();
    void Mostrar();
    void Primero();
    int largoLista();
public:
    pnodoReservacion primero; 

};

ListaReservacion::~ListaReservacion(){
    pnodoReservacion aux;
    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
}

int ListaReservacion::largoLista() { 
    int cont = 0;
    pnodoReservacion aux; 
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

void ListaReservacion::InsertarInicio(int tipTren, int tren, int ruta, int asientos, int precio ){
    if (ListaVacia())
        primero = new nodoReservacion(tipTren, tren, ruta, asientos, precio);
    else
        primero = new nodoReservacion(tipTren, tren, ruta, asientos, precio);
}

void ListaReservacion::InsertarFinal(int tipTren, int tren, int ruta, int asientos, int precio ){
    if (ListaVacia())
        primero = new nodoReservacion(tipTren, tren, ruta, asientos, precio);
    else
    {
        pnodoReservacion aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = new nodoReservacion(tipTren, tren, ruta, asientos, precio);
    }
}

void ListaReservacion::Mostrar(){
    nodoReservacion* aux;
    if (primero == NULL)
        cout << "No hay elementos";
    else{
        aux = primero;
        while (aux)
        {
            cout << aux->codtipTren <<" - "<< aux->codTren<< " - "<< aux->codRuta<<" - "<< aux->cantAsientos<<" - "<<aux->precioU<< " ->";
            aux = aux->siguiente;
        }
        cout << endl;
    }
}
