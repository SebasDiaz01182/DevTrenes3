#ifndef _NODOBINARIO_H
#define	_NODOBINARIO_H
#include<string.h>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include<queue>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <cstdio>
#include "Ciudades.hpp"
#include "Conexiones.hpp"

using namespace std;
class NodoBinario {
   public:
	NodoBinario(int v,string pnombre){
		valor = v;
		nombre =pnombre;
		reservacion= 0;
		ciudad = NULL;
		Hder = NULL;
		Hizq = NULL;
		siguiente = NULL;
		anterior = NULL;
	}
	
	//Atributos
    int valor,reservacion;
    string nombre;
    NodoBinario *Hizq, *Hder, *siguiente, *anterior;
    NodoAVL *ciudad;

    friend class Pila;
    friend class Binario;
};

typedef NodoBinario *pNodoBinario;

bool ExistePais(pNodoBinario &R,int pais){
	 if(R == NULL){
	 	return false;
	 }
	 else if(R->valor==pais){
	 	return true;
	 }
	 else if(pais<=R->valor){
	 	return ExistePais(R->Hizq,pais);
	 }
	 else{
	 	return ExistePais(R->Hder,pais);
	 }
}
void PreordenR(NodoBinario *R){
    ofstream archivo;
    archivo.open("ReportePaises.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }
    if(R==NULL){
        return;
    }
	else{
        cout<<R->valor<<" - "<<R->nombre<<endl;
        archivo<<R->nombre<<" , codigo: "<<R->valor<<endl;
        PreordenR(R->Hizq);
        PreordenR(R->Hder);
    }
}

void InsertarNodoPais(pNodoBinario &paises,int num, string nombre){
	if(paises==NULL){
		paises = new NodoBinario(num,nombre);
	}
	else{
		if(num<=paises->valor){
			InsertarNodoPais(paises->Hizq,num, nombre);
		}
		else{
			InsertarNodoPais(paises->Hder,num, nombre);
		}
	}
}

void InsertarPais(pNodoBinario &paises, string &ultimoPais){
	int codPais;
	string nombrePais;
	cout<<"Ingrese el codigo del pais nuevo: "; cin>>codPais; cout<<endl;
	cout<<"Ingrese el nombre del pais: "; cin>>nombrePais; cout<<endl;
	if(ExistePais(paises,codPais)){
		cout<<"El codigo del pais ingresado ya existe."<<endl;
	}
	else{
		InsertarNodoPais(paises,codPais,nombrePais);
		stringstream ss;
		ss<<codPais;
		string codPaisS = ss.str();
		ultimoPais = ("Ultimo pais insertado: " + nombrePais + "\n" + "Codigo: " + codPaisS);
		cout<<"El pais fue ingresado con exito."<<endl;
	}
	
}

pNodoBinario CargarPaises(){
	pNodoBinario paises = NULL;
	ifstream archivo;
    string texto;
    archivo.open("Paises.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		if(paises==NULL){
    			int posPC = texto.find(";");
		        int codPais = atoi(texto.substr(0, posPC).c_str());
		        string nomPais = texto.substr(posPC + 1, texto.length());
    			paises = new NodoBinario(codPais,nomPais);
			}
			else{
				int posPC = texto.find(";");
		        int codPais = atoi(texto.substr(0, posPC).c_str());
		        string nomPais = texto.substr(posPC + 1, texto.length());
		        if(ExistePais(paises,codPais)){
		        	continue;
				}
				else{
					InsertarNodoPais(paises,codPais,nomPais);
				}
			}
    		
    		
    		
    	}//llave del while
    	archivo.close();
	}
	return paises;
}
//Devuelve un pais
pNodoBinario DevolverPais(pNodoBinario &R,int pais){
	 if(R->valor==pais){
	 	return R;
	 }
	 else if(pais<=R->valor){
	 	return DevolverPais(R->Hizq,pais);
	 }
	 else{
	 	return DevolverPais(R->Hder,pais);
	 }
}


string DevolverPais2(pNodoBinario &R,int pais){
	 if(R->valor==pais){
	 	return R->nombre;
	 }
	 else if(pais<=R->valor){
	 	return DevolverPais2(R->Hizq,pais);
	 }
	 else{
	 	return DevolverPais2(R->Hder,pais);
	 }
}
//Devuelve una ciudad
NodoAVL* DevolverCiudad(NodoAVL* &R,int codCiudad){
	 if(R->codCiudad==codCiudad){
	 	return R;
	 }
	 else if(codCiudad<=R->codCiudad){
	 	return DevolverCiudad(R->izquierda,codCiudad);
	 }
	 else{
	 	return DevolverCiudad(R->derecha,codCiudad);
	 }
}

string DevolverCiudad2(NodoAVL* &R,int codCiudad){
	 if(R->codCiudad==codCiudad){
	 	return R->nombre;
	 }
	 else if(codCiudad<=R->codCiudad){
	 	return DevolverCiudad2(R->izquierda,codCiudad);
	 }
	 else{
	 	return DevolverCiudad2(R->derecha,codCiudad);
	 }
}
//Cargar Ciudades
void CargarCiudades(pNodoBinario& paises ){
	ifstream archivo;
    string texto;
    archivo.open("Ciudades.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		int posPC = texto.find(";");
		    int codPais = atoi(texto.substr(0, posPC).c_str());
		    if(ExistePais(paises,codPais)){
		    	pNodoBinario pais = DevolverPais(paises,codPais);
		    	string CiudadTotal = texto.substr(posPC + 1, texto.length());
		        int auxPC = CiudadTotal.find(";");
		        int codCiudad = atoi(CiudadTotal.substr(0, auxPC).c_str());
		        string nomCiudad = CiudadTotal.substr(auxPC+1, CiudadTotal.length());
		    	if(!ExisteCiudad(pais->ciudad,codCiudad)){
		    		pais->ciudad = insertarnodoAVL(pais->ciudad,codCiudad,nomCiudad);
				}
				else{
					continue;
				}
			}
			else{
				continue;
			}
    		
    	}//llave del while
    	archivo.close();
	}
}


void InsertarCiudad(pNodoBinario& paises, string &ultimaCiudad){
    int codPais; cout<<"Ingrese el codigo del pais al que pertenece la ciudad: "; cin>>codPais; cout<<endl;
    if(ExistePais(paises,codPais)){
    	pNodoBinario pais = DevolverPais(paises,codPais);
        int codCiudad; cout<<"Ingrese el codigo de la ciudad: "; cin>>codCiudad; cout<<endl;
        string nomCiudad; cout<<"Ingrese el nombre de la ciudad: "; cin>>nomCiudad; cout<<endl;
    	if(!ExisteCiudad(pais->ciudad,codCiudad)){
    		pais->ciudad = insertarnodoAVL(pais->ciudad,codCiudad,nomCiudad);
    		stringstream ss;
			ss<<codCiudad;
			string codCiudadS = ss.str();
			ultimaCiudad = ("Ultima ciudad insertada: " + nomCiudad + "\n" + "Codigo: " + codCiudadS);
			cout<<"La ciudad fue ingresada con exito."<<endl;
		}
		else{
			cout<<"El codigo de la ciudad ya existe"<<endl;
		}
	}
	else{
		cout<<"El pais no existe"<<endl;
	}
}


//Consultar Paises
void ReportePaises(pNodoBinario &paises){
	remove("ReportePaises.txt");
	ofstream archivo; archivo.open("ReportePaises.txt", ios::app); archivo<<"------------------Registro Paises------------------"<<endl; archivo.close();
	PreordenR(paises);
	cout<<endl;
}

//Consultar Ciudades
void preOrder(NodoAVL *raiz) { 
	ofstream archivo;
    archivo.open("ReporteCiudades.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }
    if(raiz != NULL)  {  
        cout <<raiz->codCiudad<<"-"<<raiz->nombre<<endl;
        archivo<<raiz->nombre<<" , codigo "<<raiz->codCiudad<<endl;
        preOrder(raiz->izquierda);  
        preOrder(raiz->derecha);  
    }  
}

void ConsultarCiudades(pNodoBinario &paises){
	ofstream archivo;
    archivo.open("ReporteCiudades.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }
	int paisAux; cout<<"Ingrese el codigo del pais para ver las ciudades: ";cin>>paisAux; cout<<endl;
	if(ExistePais(paises, paisAux)){
		archivo<<"------ Ciudades del pais: "<<paisAux<<" ------"<<endl;
		pNodoBinario pais = DevolverPais(paises,paisAux);
		cout<<"Ciudades de ese pais: "<<endl;
		preOrder(pais->ciudad);	
	}else{
		cout<<"El codigo de pais no existe"<<endl;
	}
	archivo.close();
}

//CargarConexiones

bool ExisteConexion(pNodoBinarioRN R,int codConexion){
	 if(R == NULL){
	 	return false;
	 }
	 else if(R->valor==codConexion){
	 	return true;
	 }
	 else if(codConexion<=R->valor){
	 	return ExisteConexion(R->Hizq,codConexion);
	 }
	 else{
	 	return ExisteConexion(R->Hder,codConexion);
	 }
}


pNodoBinarioRN DevolverConexion(pNodoBinarioRN R,int codConexion){
	if(R->valor==codConexion){
	 	return R;
	 }
	 else if(codConexion<=R->valor){
	 	return DevolverConexion(R->Hizq,codConexion);
	 }
	 else{
	 	return DevolverConexion(R->Hder,codConexion);
	 }
}

//Cargar Conexiones
void CargarConexiones(pNodoBinario &paises){
	ifstream archivo;
    string texto;
    archivo.open("Conexiones.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		int posPC = texto.find(";");int codPais = atoi(texto.substr(0, posPC).c_str());                                                         
			string ConexionTotal = texto.substr(posPC + 1, texto.length());int posPC2 = ConexionTotal.find(";");int codCiudad = atoi((ConexionTotal.substr(0, posPC2).c_str()));                            
			string Conexion = ConexionTotal.substr(posPC2 + 1, ConexionTotal.length());int posPC3 = Conexion.find(";");int codConexionAux = atoi((Conexion.substr(0, posPC3).c_str()));
			string ConexionPais = Conexion.substr(posPC3 + 1, Conexion.length());int posPC4 = ConexionPais.find(";");int codPais2 = atoi((ConexionPais.substr(0, posPC4).c_str()));
			string ConexionCiudad = ConexionPais.substr(posPC4 + 1, ConexionPais.length());int posPC5 = ConexionCiudad.find(";");int codCiudad2 = atoi((ConexionCiudad.substr(0, posPC5).c_str()));
			string Tiempo = ConexionCiudad.substr(posPC5 + 1, ConexionCiudad.length());int posPC6 = Tiempo.find(";");int codTiempo = atoi((Tiempo.substr(0, posPC6).c_str()));
			if((ExistePais(paises,codPais))&&(ExistePais(paises,codPais2))){
				pNodoBinario paisAux = DevolverPais(paises,codPais);
				pNodoBinario paisAux2 = DevolverPais(paises,codPais2);
				if((ExisteCiudad(paisAux->ciudad,codCiudad))&&(ExisteCiudad(paisAux2->ciudad,codCiudad2))){
					NodoAVL *ciudadAux = DevolverCiudad(paisAux->ciudad,codCiudad);
					if(!ExisteConexion(ciudadAux->conexiones.raiz,codConexionAux)){
						ciudadAux->conexiones.insercionRN(codConexionAux,codPais2,codCiudad2,codTiempo);
					}
					else{
						continue;
					}
				}
				else{
					continue;
				}
			}
			else{
				continue;
			}
    	}
    	archivo.close();
    }
}

void InsertarConexion(pNodoBinario &paises, string &ultimaConexion){
	int codPais; cout<<"Ingrese el codigo del pais: "; cin>>codPais; cout<<endl;
	int codCiudad; cout<<"Ingrese el codigo de la ciudad: "; cin>>codCiudad; cout<<endl;
	int codConexion; cout<<"Ingrese el codigo de la conexion: "; cin>>codConexion; cout<<endl;
	int codPais2; cout<<"Ingrese el codigo del pais destino: "; cin>>codPais2; cout<<endl;
	int codCiudad2; cout<<"Ingrese el codigo de la ciudad destino: "; cin>>codCiudad2; cout<<endl;
	int codTiempo; cout<<"Ingrese la cantidad de tiempo de la conexion: "; cin>>codTiempo; cout<<endl;
	if((ExistePais(paises,codPais))&&(ExistePais(paises,codPais2))){
		pNodoBinario paisAux = DevolverPais(paises,codPais);
		pNodoBinario paisAux2 = DevolverPais(paises,codPais2);
		if((ExisteCiudad(paisAux->ciudad,codCiudad))&&(ExisteCiudad(paisAux2->ciudad,codCiudad2))){
			NodoAVL *ciudadAux = DevolverCiudad(paisAux->ciudad,codCiudad);
			if(!ExisteConexion(ciudadAux->conexiones.raiz,codConexion)){
				ciudadAux->conexiones.insercionRN(codConexion,codPais2,codCiudad2,codTiempo);
				stringstream ss;
				ss<<codConexion;
				string codCiudadS = ss.str();
				ultimaConexion = ("Ultima conexion insertada: " + codCiudadS);
				cout<<"Conexion Ingresada con exito"<<endl;
			}
			else{
				cout<<"El codigo de la conexion ya existe"<<endl;
			}
		}
		else{
			cout<<"La ciudad de origen o destino de la conexion no existe"<<endl;
		}
	}
	else{
		cout<<"El pais de origen o destino de la conexion no existe"<<endl;
	}
}


void ConsultarConexiones(pNodoBinario &paises){
	ofstream archivo;
    archivo.open("ReporteConexiones.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }
	int paisAux; cout<<"Ingrese el codigo del pais: ";cin>>paisAux; cout<<endl;
	int codCiudad; cout<<"Ingrese el codigo de la ciudad para ver las conexiones: ";cin>>codCiudad;cout<<endl;
	if(ExistePais(paises, paisAux)){
		pNodoBinario pais = DevolverPais(paises,paisAux);
		if(ExisteCiudad(pais->ciudad,codCiudad)){
			NodoAVL *ciudadAux = DevolverCiudad(pais->ciudad,codCiudad);
			archivo<<endl<<"Conexiones de la ciudad de codigo "<<codCiudad<<" del pais "<<paisAux<<endl;
			if(ciudadAux->conexiones.raiz != NULL){
				PreordenRN(ciudadAux->conexiones.raiz);
			}
			else{
				archivo<<endl<<"No existen conexiones de la ciudad de codigo "<<codCiudad<<" del pais "<<paisAux<<endl;
				cout<<"La ciudad no tiene conexiones"<<endl;
			}
		}else{
			cout<<"El codigo de la ciudad no existe"<<endl;
		}
	}else{
		cout<<"El codigo de pais no existe"<<endl;
	}
	archivo.close();
}

void ModificarTiempo(pNodoBinario &paises){
	int codPais; cout<<"Ingrese el codigo del pais: "; cin>>codPais; cout<<endl;
	int codCiudad; cout<<"Ingrese el codigo de la ciudad: "; cin>>codCiudad; cout<<endl;
	int codConexion; cout<<"Ingrese el codigo de la conexion: "; cin>>codConexion; cout<<endl;
	int codTiempo; cout<<"Ingrese la cantidad de tiempo nueva de la conexion: "; cin>>codTiempo; cout<<endl;
	if(ExistePais(paises,codPais)){
		pNodoBinario paisAux = DevolverPais(paises,codPais);
		if(ExisteCiudad(paisAux->ciudad,codCiudad)){
			NodoAVL *ciudadAux = DevolverCiudad(paisAux->ciudad,codCiudad);
			if(ExisteConexion(ciudadAux->conexiones.raiz,codConexion)){
				pNodoBinarioRN cambio = DevolverConexion(ciudadAux->conexiones.raiz, codConexion);
				cout<<"El nuevo tiempo estimado del viaje es de "<<(cambio->tiempo = codTiempo)<< " horas"<<endl;
			}
			else{
				cout<<"El codigo de la conexion no existe"<<endl;
			}
		}
		else{
			cout<<"La ciudad de origen o destino de la conexion no existe"<<endl;
		}
	}
	else{
		cout<<"El pais de origen o destino de la conexion no existe"<<endl;
	}
}


#endif	

