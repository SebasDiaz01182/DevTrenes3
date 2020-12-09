#include <iostream>
#include <fstream>
#include <stdlib.h>
#include<string>
#include "Reservacion.hpp"
#pragma once
using namespace std;

class nodoUsuario { 

public:
    nodoUsuario(int iD ) {
        identificacion = iD;
        siguiente = NULL;
        reservacion = ListaReservacion();
        reporte = 0;
    }

    nodoUsuario(int iD , nodoUsuario* signodoUsuario) {
        identificacion = iD;
        siguiente = signodoUsuario;
    }

public: // atributos
    int identificacion;
    int reporte;
    nodoUsuario* siguiente;
    ListaReservacion reservacion;
};
typedef nodoUsuario* pnodoUsuario; 

class listaUsuario {
public:
    listaUsuario(){
        primero = NULL;
    }
    ~listaUsuario();
    void InsertarInicio(int identificacion);
    void InsertarFinal(int identificacion);
    bool ListaVacia() { return primero == NULL; }
    void Imprimir();
    void Mostrar();
    void Primero();
    int largoLista();
public:
    pnodoUsuario primero; 

};

listaUsuario::~listaUsuario(){
    pnodoUsuario aux;
    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
}

int listaUsuario::largoLista() { 
    int cont = 0;
    pnodoUsuario aux; 
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

void listaUsuario::InsertarInicio(int identificacion){
    if (ListaVacia())
        primero = new nodoUsuario(identificacion);
    else
        primero = new nodoUsuario(identificacion,  primero);
}

void listaUsuario::InsertarFinal(int identificacion){
    if (ListaVacia())
        primero = new nodoUsuario(identificacion);
    else
    {
        pnodoUsuario aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = new nodoUsuario(identificacion);
    }
}

void listaUsuario::Mostrar(){
    nodoUsuario* aux;
    if (primero == NULL)
        cout << "No hay elementos";
    else{
        aux = primero;
        while (aux)
        {
            cout << aux->identificacion <<" -> ";
            aux = aux->siguiente;
        }
        cout << endl;
    }
}

