#include <stdlib.h>
#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sstream>
#include <math.h>
#include "Paises.hpp"
#pragma once
using namespace std;

class NodoUsuario {	
  //Atributuos
  int *keys;
  string *nombres;
  int *pais;
  int *ciudad;
  int *estado;
  
  int t;
  NodoUsuario **C;
  int n;
  bool leaf;

   public:
  NodoUsuario(int temp, bool bool_leaf);

  	void insertNonFull(int k,string pnombre,int ppais,int pciudad,int pestado);
  	void splitChild(int i, NodoUsuario *y);
  	void traverse();
	bool ModEstMigratorio(int k, int estMigratorio);
	bool DevolverMigra(int k);
  

  NodoUsuario *search(int k);
  bool ExisteUsuario(int k);

  friend class ArbolUsuario;
};

class ArbolUsuario {
  NodoUsuario *root;
  int t;

   public:
  ArbolUsuario(int temp) {
    root = NULL;
    t = temp;
  }

  void traverse() {
    if (root != NULL)
      root->traverse();
  }

  NodoUsuario *search(int k) {
    return (root == NULL) ? NULL : root->search(k);
  }
  bool ExisteUsuario(int k){
  	return (root==NULL) ? false : root->ExisteUsuario(k);
  }

  	void insert(int k,string pnombre,int ppais,int pciudad,int pestado);
  	
	bool ModEstMigratorio(int k, int estMigratorio){
		return (root== NULL) ? false : root->ModEstMigratorio(k, estMigratorio);
	}
	bool DevolverMigra(int k){
		return (root == NULL) ? false : root->DevolverMigra(k);
	}
};

NodoUsuario::NodoUsuario(int t1, bool leaf1) {
  t = t1;
  leaf = leaf1;

  keys = new int[2 * t - 1];
  C = new NodoUsuario *[2 * t];
  nombres = new string[2 * t - 1];
  pais = new int[2 * t - 1];
  ciudad =new int[2 * t - 1];
  estado = new int[2 * t - 1];

  n = 0;
}

void NodoUsuario::traverse() {
  int i;
  for (i = 0; i < n; i++) {
    if (leaf == false)
      C[i]->traverse();
    cout <<"Nombre: "<<nombres[i]<<" Pais: "<<pais[i]<<" Ciudad: "<<ciudad[i]<<" CodPasaporte: "<<keys[i]<<" Estado Migratorio: "<<estado[i]<<endl;
  }

  if (leaf == false)
    C[i]->traverse();
}

NodoUsuario *NodoUsuario::search(int k) {
  int i = 0;
  while (i < n && k > keys[i])
    i++;

  if (keys[i] == k)
    return this;

  if (leaf == true)
    return NULL;

  return C[i]->search(k);
}

void ArbolUsuario::insert(int k,string pnombre,int ppais,int pciudad,int pestado) {
  if (root == NULL) {
    root = new NodoUsuario(t, true);
    root->keys[0] = k;
    root->nombres[0] = pnombre;
    root->pais[0] = ppais;
    root->ciudad[0] = pciudad;
    root->estado[0] = pestado;
    root->n = 1;
  } else {
    if (root->n == 2 * t - 1) {
      NodoUsuario *s = new NodoUsuario(t, false);

      s->C[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->C[i]->insertNonFull(k,pnombre,ppais,pciudad,pestado);

      root = s;
    } else
      root->insertNonFull(k,pnombre,ppais,pciudad,pestado);
  }
}

void NodoUsuario::insertNonFull(int k,string pnombre,int ppais,int pciudad,int pestado) {
  int i = n - 1;

  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      keys[i + 1] = keys[i];
      nombres[i+1] = nombres[i];
      pais[i+1] = pais[i];
      ciudad[i+1] = ciudad[i];
      estado[i+1] = estado[i];
      i--;
    }
    keys[i + 1] = k;
    nombres[i+1] = pnombre;
    pais[i+1] = ppais;
    ciudad[i+1] =pciudad;
    estado[i+1] = pestado;
    n = n + 1;
  } else {
    while (i >= 0 && keys[i] > k)
      i--;

    if (C[i + 1]->n == 2 * t - 1) {
      splitChild(i + 1, C[i + 1]);

      if (keys[i + 1] < k)
        i++;
    }
    C[i + 1]->insertNonFull(k,pnombre,ppais,pciudad,pestado);
  }
}

void NodoUsuario::splitChild(int i, NodoUsuario *y) {
  NodoUsuario *z = new NodoUsuario(y->t, y->leaf);
  z->n = t - 1;

  for (int j = 0; j < t - 1; j++){
  	z->keys[j] = y->keys[j + t];
  	z->nombres[j] = y->nombres[j+t];
  	z->pais[j] = y->pais[j+t];
  	z->ciudad[j] = y->ciudad[j+t];
  	z->estado[j] = y->estado[j+t];
  }
    

  if (y->leaf == false) {
    for (int j = 0; j < t; j++)
      z->C[j] = y->C[j + t];
  }

  y->n = t - 1;
  for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

  C[i + 1] = z;

  for (int j = n - 1; j >= i; j--){
  	keys[j + 1] = keys[j];
  	nombres[j+1] = nombres[j];
  	pais[j+1] = pais[j];
  	ciudad[j+1] = ciudad[j];
  	estado[j+1] = estado[j];
  }
  keys[i] = y->keys[t - 1];
  nombres[i] = y->nombres[t-1];
  pais[i] = y->pais[t-1];
  ciudad[i] = y->ciudad[t-1];
  estado[i] = y->estado[t-1];
  n = n + 1;
}

bool NodoUsuario::ExisteUsuario(int k) {
  int i = 0;
  while (i < n && k > keys[i])
    i++;

  if (keys[i] == k){
  	return true;
  }
    

  if (leaf == true){
  	return false;
  }
  return C[i]->ExisteUsuario(k);
}



void CargarUsuarios(ArbolUsuario &usuarios, pNodoBinario paises){
	ifstream archivo;
    string texto;
    archivo.open("Usuarios.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		int posPC = texto.find(";");int codPais = atoi(texto.substr(0, posPC).c_str());
	        string Todo = texto.substr(posPC + 1, texto.length());int posPC2 = Todo.find(";");int codCiudad = atoi(Todo.substr(0, posPC2).c_str());
	        string Todo2 = Todo.substr(posPC2 + 1, Todo.length());int posPC3 = Todo2.find(";");int codPasaporte = atoi((Todo2.substr(0, posPC3).c_str()));
	        string Todo3 = Todo2.substr(posPC3 + 1, Todo2.length());int posPC4 = Todo3.find(";");string nombre = (Todo3.substr(0, posPC4));
	        string Todo4 = Todo3.substr(posPC4 + 1, Todo3.length()); int posPC5 = Todo4.find(";");int estMigracion = atoi((Todo4.substr(0, posPC5).c_str()));
			if(ExistePais(paises,codPais)){
				pNodoBinario paisAux = DevolverPais(paises, codPais);
				if(ExisteCiudad(paisAux->ciudad,codCiudad)){
					if((estMigracion == 0)||(estMigracion == 1)){
						if(!usuarios.ExisteUsuario(codPasaporte)){
				    		usuarios.insert(codPasaporte,nombre,codPais,codCiudad,estMigracion);
						}
						else{
							//cout<<"El pasaporte que ingreso ya existe"<<endl;
							continue;
						}
					}else{
						//cout<<"El estado migratorio debe de ser 1 o 0"<<endl;
						continue;
					}
				}else{
					//cout<<"El codigo de ciudad no existe"<<endl;
					continue;
				}
			}else{
				//cout<<"El codigo del pais no existe"<<endl;
				continue;
			}
    	}
    	archivo.close();
    }
}

void RegistrarUsuario(ArbolUsuario &usuarios, pNodoBinario &paises){
	int codPais; cout<<"Ingrese el codigo de su pais de procedencia: "; cin>>codPais; cout<<endl;
	int codCiudad; cout<<"Ingrese el codigo de su ciudad de procedencia: "; cin>>codCiudad; cout<<endl;
	int codPasaporte; cout<<"Ingrese su pasaporte: "; cin>>codPasaporte; cout<<endl;
	string nombre; cout<<"Ingrese su nombre: "; cin>>nombre; cout<<endl;
	int estMigracion; cout<<"Ingrese su estado migratorio actual : "; cin>>estMigracion; cout<<endl;
	if(ExistePais(paises,codPais)){
		pNodoBinario paisAux = DevolverPais(paises, codPais);
		if(ExisteCiudad(paisAux->ciudad,codCiudad)){
			if((estMigracion == 0)||(estMigracion == 1)){
				if(!usuarios.ExisteUsuario(codPasaporte)){
			    	usuarios.insert(codPasaporte,nombre,codPais,codCiudad,estMigracion);
			    	cout<<"Registrado con exito"<<endl;
				}
				else{
					cout<<"El pasaporte que ingreso ya existe"<<endl;
				}
			}else{
				cout<<"El estado migratorio debe de ser 1 o 0"<<endl;
			}
		}else{
			cout<<"El codigo de ciudad no existe"<<endl;
		}
	}else{
		cout<<"El codigo del pais no existe"<<endl;
	}
}

bool NodoUsuario::ModEstMigratorio(int k, int estMigratorio) {
  int i = 0;
  while (i < n && k > keys[i])
    i++;

  if (keys[i] == k){
  	estado[i] = estMigratorio;
  	return true;
  }
  if (leaf == true){
  	return false;
  }
  return C[i]->search(k);
}

bool NodoUsuario::DevolverMigra(int k) {
  int i = 0;
  while (i < n && k > keys[i])
    i++;

  if (keys[i] == k){
  	if(estado[i]== 0){
  		return false;
	  }else{
	  	return true;
	  } 
  	
  }
  if (leaf == true){
  	return false;
  }
  return C[i]->search(k);
}

void ModificarEstMigracion(ArbolUsuario &usuarios){
	int codPasaporte; cout<<"Ingrese su pasaporte: "; cin>>codPasaporte; cout<<endl;
	int estMigracion; cout<<"Ingrese el nuevo estado migratorio: "; cin>>estMigracion; cout<<endl;
	if(usuarios.ExisteUsuario(codPasaporte)){
		if((estMigracion == 0)||(estMigracion == 1)){
			if(usuarios.ModEstMigratorio(codPasaporte,estMigracion)){
				cout<<"Modificado con exito"<<endl;
			}
		}else{
			cout<<"El estado migratorio solo puede ser 1 o 0"<<endl;
		}
	}
	else{
		cout<<"El pasaporte que ingreso no existe"<<endl;
	}
}
