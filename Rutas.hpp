#include <fstream> 
#include <iostream> 
#include <stdlib.h> 
#include<string>
#include"Paises.hpp"
#include"TipoTren.hpp"
#include "Trenes.hpp"
#include "CodRutas.hpp"
#include "Reservacion.hpp"
#include "UsuarioReservacion.hpp"
#include "Boleteria.hpp"
#pragma once 
using namespace std;

class Nodo {
    public:
        int codTipTren; 
	    int codTren; 
	    int codRutas ;
	    int codConexion;
	    int precio;
		int reservacion; 
        Nodo *siguiente;
        Nodo *ant;
    	friend class listaC;
    };
    typedef Nodo* pnodoCir;
    
class listaC {
public:
    Nodo *primero;
    friend class Nodo;
    listaC();
    ~listaC();
    void InsertarInicio(int v, int trenc, int rutac, int conexionc, int precioc);
	void insertarUltimo(int codTipTren, int trenc, int rutac, int conexionc, int precioc);
	void InsertarPos(int v, int trenc, int rutac, int conexionc, int precioc, int pos);
	bool vacia();	
	void ConsultarRuta();
	void BorrarFinal();
	void BorrarInicio();
	void borrarPosicion(int pos);
	int largoLista();
	void CargarRutas(pNodoBinario& paises, pNodoTipoTren& tipoTrenes);
	bool ExisteRuta(int codRuta);
	void InsertarRutas(pNodoBinario& paises, pNodoTipoTren& tipoTrenes);
	void ModificarRutas(pNodoBinario& paises);
	void ModificarPrecio(pNodoBinario& paises);
	void ConsultarPrecio(pNodoTipoTren& tipoTrenes);
	void DevolverRuta(int codRuta, pnodoCir &ruta);
};
listaC::listaC()
{
    primero = NULL;
}

listaC::~listaC()
{
    if (primero != NULL) {
        Nodo *reco = primero->siguiente;
        Nodo *bor;
        while (reco != primero)
        {
            bor = reco;
            reco = reco->siguiente;
            delete bor;
        }
        delete primero;
    }
}
/*
void ListaCircular::insertarPrimero(int codTipTren, int trenc, int rutac, int conexionc, int precioc)
{
    Nodo *nuevo = new Nodo();
    nuevo->codTipTren = codTipTren;
    if (raiz == NULL) 
    {
        nuevo->sig = nuevo;
        nuevo->ant = nuevo;
        raiz = nuevo;
    }
    else 
    {
        Nodo *ultimo = raiz->ant;
        nuevo->sig = raiz;
        nuevo->ant = ultimo;
        raiz->ant = nuevo;
        ultimo->sig = nuevo;
        raiz = nuevo;
    }
}
*/
void listaC::insertarUltimo(int codTipTren, int trenc, int rutac, int conexionc, int precioc) 
{
    Nodo *nuevo = new Nodo();
    nuevo->codTipTren = codTipTren; nuevo->codTren = trenc; nuevo->codRutas = rutac; nuevo->codConexion = conexionc; nuevo->precio= precioc;
    if (primero == NULL) 
    {
        nuevo->siguiente = nuevo;
        nuevo->ant = nuevo;
        primero = nuevo;
    }
    else 
    {
        Nodo *ultimo = primero->ant;
        nuevo->siguiente = primero;
        nuevo->ant = ultimo;
        primero->ant = nuevo;
        ultimo->siguiente = nuevo;
    }
}

bool listaC::vacia()
{
    if (primero == NULL)
        return true;
    else
        return false;
}
/*
void ListaCircular::imprimir()
{
    if (!vacia()) {
        Nodo *reco = raiz;
        do {
            cout<<reco->codTipTren  <<"-";
            reco = reco->sig;
        } while (reco != raiz);
        cout << "\n";
    }
}

int ListaCircular::cantidad()
{
    int cant = 0;
    if (!vacia()) 
    {
        Nodo *reco = raiz;
        do {
            cant++;
            reco = reco->sig;
        } while (reco != raiz);
    }
    return cant;
}

void ListaCircular::borrar(int pos)
{
    if (pos <= cantidad())
    {
        if (pos == 1) 
        {
            if (cantidad() == 1) 
            {
                delete raiz;
                raiz = NULL;
            }
            else 
            {
                Nodo *bor = raiz;
                Nodo *ultimo = raiz->ant;
                raiz = raiz->sig;
                ultimo->sig = raiz;
                raiz->ant = ultimo;
                delete bor;
            }
        }
        else {
            Nodo *reco = raiz;
            for (int f = 1; f <= pos - 1; f++)
                reco = reco->sig;
            Nodo *bor = reco;
            Nodo *anterior = reco->ant;
            reco = reco->sig;
            anterior->sig = reco;
            reco->ant = anterior;
            delete bor;
        }
    }
}
 */
void listaC::ConsultarRuta() { 
    pnodoCir aux = primero;
    if(aux== NULL){
    	cout<<"No hay ninuna ruta registrada"<<endl;
	}else{
		while (aux->siguiente != primero) {
        cout <<"Tipo tren: "<<aux->codTipTren << " Tren: " << aux->codTren << " Ruta: " << aux->codRutas << " Conexion: "<< aux->codConexion <<" Precio: "<< aux->precio << "-> "<<endl; 
        aux = aux->siguiente; 
	    } 
		cout <<"Tipo tren: "<<aux->codTipTren << " Tren: " << aux->codTren << " Ruta: " << aux->codRutas << " Conexion: "<< aux->codConexion <<" Precio: "<< aux->precio << "-> "<<endl; 
	    cout << endl; 	
	}
}

//CargarRutas
bool listaC::ExisteRuta(int codRuta){
	pnodoCir aux = primero; bool bandera = false;
	if(aux==NULL){
		return false;
	}else{
		while(aux->siguiente != primero){
			if(aux->codRutas==codRuta){
				return true;
			}
			else{
				aux = aux->siguiente; 
			}
		}
		if(aux->codRutas==codRuta){
			return true;
		}
		else{
			return false;
		}
	}
}
NodoAVLTren* DevolverTren(NodoAVLTren* &R,int codTren){
	 if(R->codTren==codTren){
	 	return R;
	 }
	 else if(codTren<=R->codTren){
	 	return DevolverTren(R->izquierda,codTren);
	 }
	 else{
	 	return DevolverTren(R->derecha,codTren);
	 }
}



void listaC::DevolverRuta(int codRuta, pnodoCir &ruta){
	pnodoCir aux = primero; bool bandera = false;
	while(aux->siguiente != primero){
		if(aux->codRutas==codRuta){
			ruta = aux;
		}
		else{
			aux = aux->siguiente; 
		}
	}
	if(aux->codRutas==codRuta){
		ruta = aux;
	}
}
bool ExisteConexionG3(pNodoBinarioRN Rcx, int &codConexion,bool &flag){
	if(Rcx==NULL){
    return flag;
	}
	else{
	
	    ExisteConexionG3(Rcx->Hizq,codConexion, flag);
	    if (codConexion==Rcx->valor){
	        flag=true;
	    }
	    ExisteConexionG3(Rcx->Hder,codConexion, flag);
	}
	return flag;
}

bool ExisteConexionG2(NodoAVL *ciudades, int &codConexion,bool &flag){ 
    if(ciudades==NULL){
    	return flag;
	}
	else{
	
	    ExisteConexionG2(ciudades->izquierda,codConexion, flag);
	    ExisteConexionG3(ciudades->conexiones.raiz,codConexion,flag);
	    ExisteConexionG2(ciudades->derecha,codConexion, flag);
	}
	return flag;
}

bool ExisteConexionG(pNodoBinario paises,int &codConexion, bool &flag){
    if(paises==NULL){
    	return flag;
	}
	else{
	
	    ExisteConexionG(paises->Hizq,codConexion, flag);
	    ExisteConexionG2(paises->ciudad,codConexion,flag);
	    ExisteConexionG(paises->Hder,codConexion, flag);
	}
	return flag;
}

void listaC::CargarRutas(pNodoBinario &paises,pNodoTipoTren &tipoTrenes){
	ifstream archivo;
    string texto;
    archivo.open("Rutas.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	bool flag = false; 
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		int posPC = texto.find(";"); int codTipTren = atoi(texto.substr(0, posPC).c_str()); 
	        string Todo = texto.substr(posPC + 1, texto.length()); int posPC2 = Todo.find(";"); int codTren = atoi(Todo.substr(0, posPC2).c_str()); 
	        string Todo2 = Todo.substr(posPC2 + 1, Todo.length()); int posPC3 = Todo2.find(";"); int codRuta = atoi((Todo2.substr(0, posPC3).c_str())); 
	        string Todo3 = Todo2.substr(posPC3 + 1, Todo2.length()); int posPC4 = Todo3.find(";"); int codConexion = atoi((Todo3.substr(0, posPC4).c_str())); 
	        string Todo4 = Todo3.substr(posPC4 + 1, Todo3.length()); int posPC5 = Todo4.find(";"); int codPrecio = atoi((Todo4.substr(0, posPC5).c_str()));
	        if(ExisteConexionG(paises,codConexion, flag)){
	        	flag = false;
	        	if(ExisteTipoTren(tipoTrenes,codTipTren)){
					pNodoTipoTren trenAux = DevolverTipoTren(tipoTrenes,codTipTren);
					if(ExisteTren(trenAux->tren,codTren)){
						if(!ExisteRuta(codRuta)){
							insertarUltimo(codTipTren,codTren,codRuta,codConexion,codPrecio);					
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
			else{
				continue;
			}
    	}
    	archivo.close();
    }
}

void listaC::InsertarRutas(pNodoBinario &paises,pNodoTipoTren &tipoTrenes){
	int codTipTren; cout<<"Ingrese el codigo tipo de tren: "; cin>>codTipTren; cout<<endl;
	int codTren; cout<<"Ingrese el codigo de tren: "; cin>>codTren; cout<<endl;
	int codRuta; cout<<"Ingrese el codigo de la ruta: "; cin>>codRuta; cout<<endl;
	int codConexion; cout<<"Ingrese el codigo nuevo de la conexion: "; cin>>codConexion; cout<<endl;
	int codPrecio; cout<<"Ingrese el precio de la ruta: "; cin>>codPrecio; cout<<endl;
	bool flag = false;
	if(ExisteConexionG(paises,codConexion,flag)){
		if(ExisteTipoTren(tipoTrenes,codTipTren)){
			pNodoTipoTren trenAux = DevolverTipoTren(tipoTrenes,codTipTren);
			if(ExisteTren(trenAux->tren,codTren)){
				NodoAVLTren *TrenA = DevolverTren(trenAux->tren,codTren);
				if(!ExisteRuta(codRuta)){
					insertarUltimo(codTipTren,codTren,codRuta,codConexion ,codPrecio);
					TrenA->codRutas.insertarBalanceado(codRuta);
					cout<<"Ruta insertada con exito"<<endl;				
				}
				else{
					cout<<"El codigo de ruta ya existe"<<endl;
				}
			}
			else{
				cout<<"El codigo de tren no existe"<<endl;
			}
		}
		else{
			cout<<"El codigo de tipo de tren no existe"<<endl;
		}
	}
	else{
		cout<<"El codigo de conexion no existe"<<endl;
	} 
}

void listaC :: ModificarRutas(pNodoBinario &paises){
	int codRuta; cout<<"Ingrese el codigo de la ruta: "; cin>>codRuta; cout<<endl;
	int codConexion; cout<<"Ingrese el codigo nuevo de la conexion: "; cin>>codConexion; cout<<endl;
	int codPrecio; cout<<"Ingrese el precio nuevo de la ruta: "; cin>>codPrecio; cout<<endl;
	if(ExisteRuta(codRuta)){
		pnodoCir cambio ; DevolverRuta(codRuta,cambio);
		cambio->codConexion = codConexion;
		cambio->precio = codPrecio;	
		cout<<"Modificacion exitosa"<<endl;			
	}
	else{
		cout<<"El codigo de ruta no existe"<<endl;
	}
}

void listaC :: ModificarPrecio(pNodoBinario &paises){
	int codRuta; cout<<"Ingrese el codigo de la ruta: "; cin>>codRuta; cout<<endl;
	int codPrecio; cout<<"Ingrese el precio nuevo de la ruta: "; cin>>codPrecio; cout<<endl;
	if(ExisteRuta(codRuta)){
		pnodoCir cambio ; DevolverRuta(codRuta, cambio);
		cambio->precio = codPrecio;	
		cout<<"Modificacion exitosa"<<endl;			
	}
	else{
		cout<<"El codigo de ruta no existe"<<endl;
	}
}

void listaC :: ConsultarPrecio(pNodoTipoTren &tipoTrenes){
	int codTipTren; cout<<"Ingrese el codigo tipo de tren: "; cin>>codTipTren; cout<<endl;
	int codTren; cout<<"Ingrese el codigo de tren: "; cin>>codTren; cout<<endl;
	pnodoCir aux = primero;
	if(ExisteTipoTren(tipoTrenes,codTipTren)){
		pNodoTipoTren trenAux = DevolverTipoTren(tipoTrenes,codTipTren);
		if(ExisteTren(trenAux->tren,codTren)){
			cout<<"Los precios de las rutas del tren "<<codTren<<" son: " <<endl;
			while(aux->siguiente != primero){
				if((aux->codTipTren == codTipTren)&&(aux->codTren == codTren)){
					cout<<"Ruta: "<<aux->codRutas<<" Precio: "<<aux->precio<<endl;
					aux= aux->siguiente;
				}else{
					aux= aux->siguiente;
				}
			}if((aux->codTipTren == codTipTren)&&(aux->codTren == codTren)){
					cout<<"Ruta: "<<aux->codRutas<<" Precio: "<<aux->precio<<endl;
				}
		}else{
			cout<<"El codigo de tren no existe"<<endl;
		}
	}else{
		cout<<"El codigo de tipo de tren no existe"<<endl;
	}
}

int ContarSeparadores(string cadena){
	int i = 0, cont = cadena.length(), cantidad = 0;
	while(cont!=0){
		if(cadena[i]==';'){
			cantidad++;
		}
		i++;
		cont--;
	}
	return cantidad;
}


void CargarCodRutas(pNodoTipoTren &tipoTrenes, listaC &rutas){
	ifstream archivo;
    string texto;
    archivo.open("Trenes.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		int posPC = texto.find(";"); int codTipTren = atoi(texto.substr(0, posPC).c_str()); 
	        string Todo = texto.substr(posPC + 1, texto.length()); int posPC2 = Todo.find(";");int codTren = atoi(Todo.substr(0, posPC2).c_str()); 
	        string Todo2 = Todo.substr(posPC2 + 1, Todo.length()); int posPC3 = Todo2.find(";");string nomTren = (Todo2.substr(0, posPC3)); 
	        string Todo3 = Todo2.substr(posPC3 + 1, Todo2.length()); int posPC4 = Todo3.find(";"); int numAsientos = atoi((Todo3.substr(0, posPC4).c_str())); 
	        string Todo4 = Todo3.substr(posPC4 + 1, Todo3.length());
	         if(ExisteTipoTren(tipoTrenes,codTipTren)){
		    	pNodoTipoTren tipoTren = DevolverTipoTren(tipoTrenes,codTipTren);
		    	if(ExisteTren(tipoTren->tren,codTren)){
		    		NodoAVLTren* trenAux = DevolverTren(tipoTren->tren,codTren);
		    		int cantidad = ContarSeparadores(Todo4);
		    		if(cantidad==0){
		    			int aux = atoi((Todo4).c_str());
						if(!ExisteCodRuta(trenAux->codRutas.raiz,aux)){
			    			trenAux->codRutas.insertarBalanceado(aux);
						}
						else{
							continue;
						}
					}
					else{
			    		while (cantidad!=0){
			    			int posPC = Todo4.find(";");
			    			int codRuta = atoi((Todo4.substr(0, posPC).c_str()));
			    			if(ExisteCodRuta(trenAux->codRutas.raiz,codRuta)){
			    				trenAux->codRutas.insertarBalanceado(codRuta);
							}
			    			Todo4 = Todo4.substr(posPC + 1, Todo4.length());
			    			cantidad--;
						}
						int aux = atoi((Todo4).c_str());
						if(ExisteCodRuta(trenAux->codRutas.raiz,aux)){
			    			trenAux->codRutas.insertarBalanceado(aux);
						}
						else{
							continue;
						}
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


pnodoUsuario DevolverUsuario(listaUsuario &lista, int id){
	pnodoUsuario aux = lista.primero;
	while(aux != NULL){
		if(aux->identificacion== id){
			return aux;
		}else{
			aux= aux->siguiente;
		}
	}
}

int DevolverPrecio(listaC &rutas, int codRuta){
	pnodoCir aux = rutas.primero; bool bandera = false;
	while(aux->siguiente != rutas.primero){
		if(aux->codRutas==codRuta){
			return aux->precio;
		}
		else{
			aux = aux->siguiente; 
		}
	}
	if(aux->codRutas==codRuta){
		return aux->precio;
	}
}

void PaisMayor(NodoBinario *R,int mayor,string &paisAux){

    if(R==NULL){
        return;
    }
    else{
        if(R->reservacion>mayor){
        	paisAux = R->nombre;
        	mayor = R->reservacion;
		}
        PaisMayor(R->Hizq,mayor,paisAux);
        PaisMayor(R->Hder,mayor,paisAux);
    }
}

bool ExisteUsuarioL(listaUsuario &listaUsuarios,int id){
	pnodoUsuario aux = listaUsuarios.primero;
	while(aux!=NULL){
		if(aux->identificacion==id){
			return true;
		}
		else{
			aux=aux->siguiente;
		}
	}
	return false;
}

pnodoUsuario UsuarioMayor(listaUsuario &listaUsuarios){
	pnodoUsuario aux = listaUsuarios.primero;
	pnodoUsuario usuario = listaUsuarios.primero;
	int cantMayor = aux->reservacion.largoLista();
	while(aux!=NULL){
		if(cantMayor<aux->reservacion.largoLista()){
			cantMayor = aux->reservacion.largoLista();
			usuario = aux;
		}
		aux = aux->siguiente;
	}
	return usuario;
}
pnodoUsuario UsuarioMenor(listaUsuario &listaUsuarios){
	pnodoUsuario aux = listaUsuarios.primero;
	pnodoUsuario usuario = listaUsuarios.primero;
	int cantMayor = aux->reservacion.largoLista();
	while(aux!=NULL){
		if(cantMayor>aux->reservacion.largoLista()){
			cantMayor = aux->reservacion.largoLista();
			usuario = aux;
		}
		aux = aux->siguiente;
	}
	return usuario;
}

void ReservasUsuarios(listaUsuario &listaUsuarios){
	ofstream archivo;
    archivo.open("ReporteCompras.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }
	pnodoUsuario aux = listaUsuarios.primero;
	while(aux!=NULL){
		archivo<<"Usuario: "<<aux->identificacion<<" Cantidad de Reservas: "<<aux->reservacion.largoLista()<<endl;
		cout<<"Usuario: "<<aux->identificacion<<" Cantidad de Reservas: "<<aux->reservacion.largoLista()<<endl;
		aux=aux->siguiente;
	}
}

void DevolverConexionG3(pNodoBinarioRN &R,bool &flag,pNodoBinarioRN &ConexionAux, int codConexion){
	if(R==NULL){
		return;
	}
	else{
    	if(R->valor==codConexion){
    		flag = true;
    		ConexionAux = R;
    		return;
		}
        DevolverConexionG3(R->Hizq,flag,ConexionAux, codConexion);
        DevolverConexionG3(R->Hder,flag,ConexionAux, codConexion);
    }
}

void DevolverConexionG2(NodoAVL *&ciudades,bool &flag,pNodoBinarioRN &ConexionAux, int codConexion){ 
    if((ciudades != NULL) && (flag != true)) {
		pNodoBinarioRN conexionAux = ciudades->conexiones.raiz; 
		DevolverConexionG3(conexionAux,flag,ConexionAux, codConexion);
	
		DevolverConexionG2(ciudades->izquierda,flag,ConexionAux, codConexion);  
    	DevolverConexionG2(ciudades->derecha,flag,ConexionAux, codConexion);
    }
	else{
		return;
	}  
}

void DevolverConexionG(pNodoBinario &paises,bool &flag,pNodoBinarioRN &ConexionAux, int codConexion){
    if((paises==NULL) || (flag == true)){
        return;
    }
	else{
		NodoAVL* ciudadAux = paises->ciudad;
        DevolverConexionG2(ciudadAux,flag,ConexionAux, codConexion);
        DevolverConexionG(paises->Hizq,flag,ConexionAux, codConexion);
        DevolverConexionG(paises->Hder,flag,ConexionAux, codConexion);
    }
}

void Reservacion (pNodoTipoTren &tipoTrenes,pNodoBinario &paises,listaUsuario &listaUsuarios, listaC &rutas, listaBoleteria &reporteCiudad, listaBoleteria &reporteTren){
	int codVentanilla; cout<<"Ingrese el codigo de la ventana que desea atender: "; cin>>codVentanilla; cout<<endl;
	if(ExisteTipoTren(tipoTrenes,codVentanilla)){
		pNodoTipoTren atender = DevolverTipoTren(tipoTrenes,codVentanilla);
		if(!atender->ventanilla.ListaVacia()){
			cambio:
			int codTren; cout<<"Ingrese el codigo del tren para su reservacion: "; cin>>codTren; cout<<endl;
			if(ExisteTren(atender->tren, codTren)){
				NodoAVLTren *TrenA = DevolverTren(atender->tren,codTren);
				int codRuta; cout<<"Ingrese el codigo de ruta que desea reservar: "; cin>>codRuta; cout<<endl;
				pnodoCir aux; rutas.DevolverRuta(codRuta,aux);
				if((rutas.ExisteRuta(codRuta)) && ((aux->codTipTren)== codVentanilla) && ((aux->codTren)==codTren)){
					int cantAsientos; cout<<"Ingrese la cantidad de asientos que desea reservar: "; cin>>cantAsientos; cout<<endl;
					if(cantAsientos<=TrenA->cantAsientos){
						int reservar; cout<<"Si desea finalizar la reservacion digite 1 de lo contrario un 2: "; cin>>reservar; cout<<endl;
						if(reservar==1){
							TrenA->cantAsientos = (TrenA->cantAsientos) - cantAsientos;
							if(!ExisteUsuarioL(listaUsuarios,atender->ventanilla.primero->identificacion)){
								listaUsuarios.InsertarFinal(atender->ventanilla.primero->identificacion);
							}
							pnodoUsuario usuario = DevolverUsuario(listaUsuarios,atender->ventanilla.primero->identificacion);
							int precio = DevolverPrecio(rutas, codRuta);
							usuario->reservacion.InsertarFinal(atender->ventanilla.primero->codTren,codTren,codRuta,cantAsientos,precio);
							atender->ventanilla.BorrarInicio();
							//REPORTES-------------------------------------------------------------------------
							pnodoCir auxRuta; rutas.DevolverRuta(codRuta, auxRuta);
							auxRuta->reservacion++;
							pnodoCir auxRutas; rutas.DevolverRuta(codRuta,auxRutas);
							pNodoBinarioRN conexionAux; bool flag = false;
							DevolverConexionG(paises,flag,conexionAux, auxRutas->codConexion);
							DevolverPais(paises,conexionAux->codPais)->reservacion++;
							bool bandera = reporteCiudad.InsertarCiudad(conexionAux->codCiudad,conexionAux->codPais);
							if(!bandera){
								reporteCiudad.ModCiudad(conexionAux->codCiudad,conexionAux->codPais);
							}
							bool bandera1 = reporteTren.InsertarCiudad(codTren, codVentanilla);
							if(!bandera1){
								reporteTren.ModCiudad(codTren, codVentanilla);
							}
							//REPORTES-------------------------------------------------------------------------
							cout<<"Reservacion agendada con exito"<<endl;
						}else{
							//continue;
						}
					}else{
						cout<<"La cantidad de asientos solicitados excede la cantidad de asientos disponibles"<<endl;
						cout<<"Se dispone de "<<TrenA->cantAsientos<<" asientos disponibles"<<endl;
						int eleccion; cout<<"Si desea cambiar de tren digite 1 de lo contrario un 2: "; cin>>eleccion; cout<<endl;
						if(eleccion==1){
							goto cambio;
						}else{
							//continue;
						}
					}
				}else{
					cout<<"La ruta ingresada no existe"<<endl;
				}
			}else{
				cout<<"El codigo de tren ingresado no existe"<<endl;
			}
		}else{
			cout<<"No se han registrado usuarios en este tipo de tren"<<endl;
		}
	}else{
		cout<<"El tipo de tren ingresado no existe"<<endl;
	}
}


int RutaMayor(listaC &rutas){
	pnodoCir aux = rutas.primero;
	pnodoCir mayor = rutas.primero;
	while(aux->siguiente!=rutas.primero){
		if(aux->reservacion>mayor->reservacion){
			mayor = aux; 
		}
		aux= aux->siguiente;
	}
	if(aux->reservacion>mayor->reservacion){
			mayor = aux; 
		}
	return mayor->codRutas;
}

int RutaMenor(listaC &rutas){
	pnodoCir aux = rutas.primero;
	pnodoCir mayor = rutas.primero;
	while(aux->siguiente!=rutas.primero){
		if(aux->reservacion<mayor->reservacion){
			mayor = aux; 
		}
		aux= aux->siguiente;
	}
	if(aux->reservacion<mayor->reservacion){
			mayor = aux; 
		}
	
	return mayor->codRutas;
}


//Eliminaciones
//---------------------------------------------------------



pNodoBinario unirABB(pNodoBinario izq, pNodoBinario der){
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    pNodoBinario centro = unirABB(izq->Hder, der->Hizq);
    izq->Hder = centro;
    der->Hizq = izq;
    return der;
}

void EliminarPais(pNodoBinario &paises, int x){
     if(paises==NULL) return;

     if(x<paises->valor)
         EliminarPais(paises->Hizq, x);
     else if(x>paises->valor)
         EliminarPais(paises->Hder, x);

     else{
         pNodoBinario p = paises;
         paises = unirABB(paises->Hizq, paises->Hder);
         delete p;
     }
}

 pNodoBinarioRN unirRN(pNodoBinarioRN izq, pNodoBinarioRN der){
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    pNodoBinarioRN centro = unirRN(izq->Hder, der->Hizq);
    izq->Hder = centro;
    der->Hizq = izq;
    return der;
}

void EliminarRN(pNodoBinarioRN &conexiones, int x){
    if(conexiones==NULL){
    	cout<<"NULL"<<endl;
    	return;
	}
    if(x<conexiones->valor){
    	EliminarRN(conexiones->Hizq, x);
	}
    else if(x>conexiones->valor){
    	EliminarRN(conexiones->Hder, x);
	}
    else{
        pNodoBinarioRN p = conexiones;
        conexiones = unirRN(conexiones->Hizq, conexiones->Hder);
        delete p;
    }
}
//-----------------------BORRADOS-----------------------
void deleteNode(pNodoBinarioRN root, int data)
{
    if(root == NULL){
       
    }

    queue<pNodoBinarioRN> q;
    q.push(root);

    while(!q.empty())
    {
        pNodoBinarioRN temp = q.front();
        q.pop();

        if(temp->valor == data)
        {
            pNodoBinarioRN current = root;
            pNodoBinarioRN prev;

            while(current->Hder != NULL)
            {
                prev = current;
                current = current->Hder;
            }

            temp->valor = current->valor;
            prev->Hder = NULL;
            free(current);

            cout << "Deleted\n";

            
        }

        if(temp->Hizq != NULL)
            q.push(temp->Hizq);
        if(temp->Hder != NULL)
            q.push(temp->Hder);
    }

}
//-----------------

void EliminarCiudad(pNodoBinario &paises,listaC &rutas){
	int codPais; cout<<"Ingrese el codigo del pais: "; cin>>codPais; cout<<endl;
	int codCiudad; cout<<"Ingrese el codigo de la ciudad: "; cin>>codCiudad; cout<<endl;
	if(ExistePais(paises,codPais)){
		pNodoBinario paisAux = DevolverPais(paises,codPais);
		if(ExisteCiudad(paisAux->ciudad,codCiudad)){
					
		}
		else{
			cout<<"La ciudad de origen o destino de la conexion no existe"<<endl;
		}
	}
	else{
		cout<<"El pais de origen o destino de la conexion no existe"<<endl;
	}
}

/*
void EliminarConexion(pNodoBinario &paises, listaC &rutas){
	int codPais; cout<<"Ingrese el codigo del pais: "; cin>>codPais; cout<<endl;
	int codCiudad; cout<<"Ingrese el codigo de la ciudad: "; cin>>codCiudad; cout<<endl;
	int codConexion; cout<<"Ingrese el codigo de la conexion: "; cin>>codConexion; cout<<endl;
	if(ExistePais(paises,codPais)){
		pNodoBinario paisAux = DevolverPais(paises,codPais);
		if(ExisteCiudad(paisAux->ciudad,codCiudad)){
			NodoAVL *ciudadAux = DevolverCiudad(paisAux->ciudad,codCiudad);
			if(ExisteConexion(ciudadAux->conexiones.raiz,codConexion)){
				EliminarRN(ciudadAux->conexiones.raiz,codConexion);
				rutas.BorrarRuta(codConexion);
				cout<<"Conexion eliminada con exito."<<endl;
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
*/
