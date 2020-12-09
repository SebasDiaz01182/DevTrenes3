#ifndef _NODOTIPOTREN_H
#define	_NODOTIPOTREN_H
#include<string.h>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include <stdlib.h>
#include "Trenes.hpp" //trenes
#include "CodRutas.hpp" //codigos de ruta
#include "Boleteria.hpp" //boleteria
#include "Usuarios.hpp" // Usuarios


using namespace std;
class NodoTipoTren {
   public:
	NodoTipoTren(int v,string pnombre){
		valor = v;
		nombre =pnombre;
		tren = NULL;
		Hder = NULL;
		Hizq = NULL;
		siguiente = NULL;
		anterior = NULL;
		ventanilla = listaBoleteria();
	}
	
	//Atributos
    int valor;
    string nombre;
    NodoAVLTren *tren;
    NodoTipoTren *Hizq, *Hder, *siguiente, *anterior;
	listaBoleteria ventanilla;
    friend class Pila;
    friend class Binario;
};

typedef NodoTipoTren *pNodoTipoTren;


void PreordenR(NodoTipoTren *R){
    
    if(R==NULL){
        return;
    }
	else{
        cout<<R->valor<<" -> ";
        PreordenR(R->Hizq);
        PreordenR(R->Hder);
    }
}

void InsertarTipTren(pNodoTipoTren &tipoTrenes,int num, string nombre){
	if(tipoTrenes==NULL){
		tipoTrenes = new NodoTipoTren(num,nombre);
	}
	else{
		if(num<=tipoTrenes->valor){
			InsertarTipTren(tipoTrenes->Hizq,num, nombre);
		}
		else{
			InsertarTipTren(tipoTrenes->Hder,num, nombre);
		}
	}
}

bool ExisteTipoTren(pNodoTipoTren& R, int tipTren){
	if(R==NULL){
	 	return false;
	 }
	 else if(R->valor==tipTren){
	 	return true;
	 }
	 else if(tipTren<=R->valor){
	 	return ExisteTipoTren(R->Hizq,tipTren);
	 }
	 else{
	 	return ExisteTipoTren(R->Hder,tipTren);
	 }
}

pNodoTipoTren CargarTipoTrenes(){
	pNodoTipoTren tipoTrenes = NULL;
	ifstream archivo;
    string texto;
    archivo.open("TipoTren.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		if(tipoTrenes==NULL){
    			int posPC = texto.find(";");
		        int codTipTren = atoi(texto.substr(0, posPC).c_str());
		        string nomTipTren = texto.substr(posPC + 1, texto.length());
    			tipoTrenes = new NodoTipoTren(codTipTren,nomTipTren);
			}
			else{
				int posPC = texto.find(";");
		        int codTipTren = atoi(texto.substr(0, posPC).c_str());
		        string nomTipTren = texto.substr(posPC + 1, texto.length());
		        if(ExisteTipoTren(tipoTrenes,codTipTren)){
		        	continue;
				}
				else{
					InsertarTipTren(tipoTrenes,codTipTren,nomTipTren);
				}
			}
    		
    	}//llave del while
    	archivo.close();
	}
	return tipoTrenes;
}

void InsertarTipoTrenes(pNodoTipoTren &tipoTrenes){
	int codTipTren; cout<<"Ingrese el codigo de tipo de tren: "; cin>>codTipTren; cout<<endl;
	string nomTipTren; cout<<"Ingrese el nombre del tipo de tren: "; cin>>nomTipTren; cout<<endl;
	if(tipoTrenes==NULL){
		tipoTrenes = new NodoTipoTren(codTipTren,nomTipTren);
	}
	else{
        if(ExisteTipoTren(tipoTrenes,codTipTren)){
        	cout<<"El codigo de tipo de tren ya existe"<<endl;
		}
		else{
			InsertarTipTren(tipoTrenes,codTipTren,nomTipTren);
		}
	}		
}

pNodoTipoTren DevolverTipoTren(pNodoTipoTren &R,int tipTren){
	 if(R->valor==tipTren){
	 	return R;
	 }
	 else if(tipTren<=R->valor){
	 	return DevolverTipoTren(R->Hizq,tipTren);
	 }
	 else{
	 	return DevolverTipoTren(R->Hder,tipTren);
	 }
}

bool ExisteTren(NodoAVLTren *R,int Tren){
	 if(R==NULL){
	 	return false;
	 }
	 else if(R->codTren==Tren){
	 	return true;
	 }
	 else if(Tren<=R->codTren){
	 	return ExisteTren(R->izquierda,Tren);
	 }
	 else{
	 	return ExisteTren(R->derecha,Tren);
	 }
}
void CargarTrenes(pNodoTipoTren& tipoTrenes ){
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
	        string Todo4 = Todo3.substr(posPC4 + 1, Todo3.length()); int posPC5 = Todo4.find(";"); int ruta = atoi((Todo4.substr(0, posPC5).c_str())); 
	        
		    if(ExisteTipoTren(tipoTrenes,codTipTren)){
		    	pNodoTipoTren tipoTren = DevolverTipoTren(tipoTrenes,codTipTren);
		    	if(!ExisteTren(tipoTrenes->tren,codTren)){
		    		tipoTren->tren = insertarnodoAVLTren(tipoTren->tren,codTren,nomTren,numAsientos);
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

void RegistrarTrenes(pNodoTipoTren& tipoTrenes, string &ultimoTren){
	int codTipTren; cout<<"Ingrese el codigo de tipo de tren: "; cin>>codTipTren; cout<<endl;
	int codTren; cout<<"Ingrese el codigo de tren: "; cin>>codTren; cout<<endl;
	string nomTren; cout<<"Ingrese el nombre del tren: "; cin>>nomTren; cout<<endl;
	int numAsientos; cout<<"Ingrese la cantidad de asientos disponibles del tren: "; cin>>numAsientos; cout<<endl;
	if(ExisteTipoTren(tipoTrenes,codTipTren)){
    	pNodoTipoTren tipoTren = DevolverTipoTren(tipoTrenes,codTipTren);
    	if(!ExisteTren(tipoTrenes->tren,codTren)){
    		tipoTren->tren = insertarnodoAVLTren(tipoTren->tren,codTren,nomTren,numAsientos);
    		stringstream ss;
			ss<<codTren;
			string codCiudadS = ss.str();
			ultimoTren = ("Ultimo Tren insertado: " + nomTren+" Codigo: " +codCiudadS);
			cout<<"El tren fue regstrado con exito"<<endl;
		}else{
			cout<<"El codigo de tren ya existe"<<endl;
		}	
	}else{
		cout<<"El codigo de tipo de tren no existe"<<endl;
	}
}

//Consultar los trenes de un tipo
void preOrderTren(NodoAVLTren *raiz) {
	ofstream archivo;
    archivo.open("ReporteTipTren.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }
    if(raiz != NULL)  {
    	archivo<<raiz->nombre<<", codigo "<<raiz->codTren<<", numero de asientos "<<raiz->cantAsientos<<endl;
        cout <<raiz->codTren<<"-"<<raiz->nombre<<", numero de asientos: "<<raiz->cantAsientos<<endl;  
        preOrderTren(raiz->izquierda);  
        preOrderTren(raiz->derecha);  
    }  
}

void ConsultarTrenes(pNodoTipoTren& tipoTrenes){
	ofstream archivo;
    archivo.open("ReporteTipTren.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }
	int codTipTren; cout<<"Ingrese el codigo del tipo de tren al que pertenece el tren: "; cin>>codTipTren; cout<<endl;
	if(ExisteTipoTren(tipoTrenes, codTipTren)){
		pNodoTipoTren tipTren = DevolverTipoTren(tipoTrenes,codTipTren);
		NodoAVLTren *tipoTrenAux = tipTren->tren;
		cout<<"Trenes de ese tipo: "<<endl;
		archivo<<endl<<"Trenes del tipo de tren "<<codTipTren<<endl;
		preOrderTren(tipoTrenAux);
		cout<<endl;
	}else{
		cout<<"El codigo de tipo de tren no existe"<<endl;
	}
	
}

void CantAsientos(pNodoTipoTren& tipoTrenes ){
	int codTipTren; cout<<"Ingrese el codigo de tipo de tren: "; cin>>codTipTren; cout<<endl;
	int codTren; cout<<"Ingrese el codigo de tren: "; cin>>codTren; cout<<endl;
	if(ExisteTipoTren(tipoTrenes,codTipTren)){
    	pNodoTipoTren tipoTren = DevolverTipoTren(tipoTrenes,codTipTren);
    	if(ExisteTren(tipoTren->tren,codTren)){
    		cout<<"La cantidad de asientos del tren es: "<<tipoTren->tren->cantAsientos<<endl;
		}else{
			cout<<"El codigo de tren no existe"<<endl;
		}	
	}else{
		cout<<"El codigo de tipo de tren no existe"<<endl;
	}
}

void ModificarAsientos(pNodoTipoTren& tipoTrenes ){
	int codTipTren; cout<<"Ingrese el codigo de tipo de tren: "; cin>>codTipTren; cout<<endl;
	int codTren; cout<<"Ingrese el codigo de tren: "; cin>>codTren; cout<<endl;
	int numAsientos; cout<<"Ingrese la nueva cantidad de asientos disponibles: "; cin>>numAsientos; cout<<endl;
	if(ExisteTipoTren(tipoTrenes,codTipTren)){
    	pNodoTipoTren tipoTren = DevolverTipoTren(tipoTrenes,codTipTren);
    	if(ExisteTren(tipoTren->tren,codTren)){
    		cout<<"La cantidad de asientos nueva del tren es: "<<(tipoTren->tren->cantAsientos = numAsientos)<<endl;
		}else{
			cout<<"El codigo de tren no existe"<<endl;
		}	
	}else{
		cout<<"El codigo de tipo de tren no existe"<<endl;
	}
}

void ModificarTren(pNodoTipoTren& tipoTrenes ){
	int codTipTren; cout<<"Ingrese el codigo de tipo de tren: "; cin>>codTipTren; cout<<endl;
	int codTren; cout<<"Ingrese el codigo de tren: "; cin>>codTren; cout<<endl;
	string nomTren; cout<<"Ingrese el nuevo nombre del tren: "; cin>>nomTren; cout<<endl;
	int numAsientos; cout<<"Ingrese la nueva cantidad de asientos disponibles: "; cin>>numAsientos; cout<<endl;
	if(ExisteTipoTren(tipoTrenes,codTipTren)){
    	pNodoTipoTren tipoTren = DevolverTipoTren(tipoTrenes,codTipTren);
    	if(ExisteTren(tipoTren->tren,codTren)){
    		tipoTren->tren->cantAsientos = numAsientos;
    		tipoTren->tren->nombre = nomTren;
    		cout<<"Tren modificado con exito"<<endl;
		}else{
			cout<<"El codigo de tren no existe"<<endl;
		}	
	}else{
		cout<<"El codigo de tipo de tren no existe"<<endl;
	}
}


void VentaTiquetes(listaBoleteria &Pasajeros, ArbolUsuario &usuarios, pNodoBinario &paises, pNodoTipoTren &tipoTrenes){
	bool eleccion = true;
	int eleccion2;
	while(eleccion){
		if (Pasajeros.ListaVacia()) {
        	cout << "La cola de usuarios con reservaciones pendientes esta vacia" << endl;
        	break;
    	}
    	else{
    		pnodoBoleteria aux = Pasajeros.primero;
    		if(!usuarios.ExisteUsuario(aux->identificacion)){
				cout<<"No se ha encontrado su identificacion, se procedera a registrarlo"<<endl;
				RegistrarUsuario(usuarios,paises);
				int iDPasajeros; cout<<"Ingrese su identificacion: "; cin>>iDPasajeros; cout<<endl;
				int tipoTren; cout<<"Ingrese el tipo de tren al que desea abordar: "; cin>>tipoTren; cout<<endl;
				Pasajeros.InsertarFinal(iDPasajeros, tipoTren);
				Pasajeros.BorrarInicio();
				cout<<"Si desea seguir administrando la venta de tiquetes digite 1 de lo contrario digite 2: "; cin>>eleccion2; cout<< endl;
				if(eleccion2==2){
					break;
				}
			}else if(!usuarios.DevolverMigra(aux->identificacion)){
				cout<<"Tiene un problema de migracion se procedera a solucionarlo"<<endl;
				usuarios.ModEstMigratorio(aux->identificacion, 1);
				int iDPasajeros; cout<<"Ingrese su identificacion: "; cin>>iDPasajeros; cout<<endl;
				int tipoTren; cout<<"Ingrese el tipo de tren al que desea abordar: "; cin>>tipoTren; cout<<endl;
				Pasajeros.InsertarFinal(iDPasajeros, tipoTren);
				Pasajeros.BorrarInicio();
				cout<<"Si desea seguir administrando la venta de tiquetes digite 1 de lo contrario digite 2: "; cin>>eleccion2; cout<< endl;
				if(eleccion2==2){
					break;
				}
			}else{
				if(ExisteTipoTren(tipoTrenes,aux->codTren)){
					pNodoTipoTren agregar = DevolverTipoTren(tipoTrenes, aux->codTren);
					agregar->ventanilla.InsertarFinal(aux->identificacion,aux->codTren);
					Pasajeros.BorrarInicio();
					cout<<"Se ha ingresado a la cola de reservacion el usuario de ID "<<aux->identificacion<< " al tipo de tren "<<aux->codTren<<endl;
					cout<<"Si desea seguir administrando la venta de tiquetes digite 1 de lo contrario digite 2: "; cin>>eleccion2; cout<< endl;
					if(eleccion2==2){
						break;
					}
				}else{
					cout<<"El tren que usted ingreso no existe."<<endl;
					bool bandera = true;
					while(bandera){
						int escoger;
						cout<<"Si desea ingresar otro tipo de tren digite 1 de lo contrario digite 2: "; cin>>escoger; cout<< endl;
						if(escoger==1){
							int tipoTren; cout<<"Ingrese el tipo de tren al que desea abordar: "; cin>>tipoTren; cout<<endl;
							if(ExisteTipoTren(tipoTrenes,tipoTren)){
								aux->codTren = tipoTren;
								pNodoTipoTren agregar = DevolverTipoTren(tipoTrenes, aux->codTren);
								agregar->ventanilla.InsertarFinal(aux->identificacion,aux->codTren);
								Pasajeros.BorrarInicio();
								bandera = false;
								cout<<"El codigo ha sido modificado"<<endl;
								cout<<"Si desea seguir administrando la venta de tiquetes digite 1 de lo contrario digite 2: "; cin>>eleccion2; cout<< endl;
								if(eleccion2==2){
									break;
								}
							}else{
								cout<<"El codigo ingresado no existe"<<endl;
							}	
						}else{
							break;
						}
					}
				}			
			}	
		}	
	}
}

string DevolverTren2(NodoAVLTren* &R,int codTren){
	 if(R->codTren==codTren){
	 	return R->nombre;
	 }
	 else if(codTren<=R->codTren){
	 	return DevolverTren2(R->izquierda,codTren);
	 }
	 else{
	 	return DevolverTren2(R->derecha,codTren);
	 }
}


string TrenMayor(listaBoleteria &ciudad, pNodoTipoTren &tipoTrenes){
	pnodoBoleteria aux = ciudad.primero;
	pnodoBoleteria mayor = ciudad.primero;
	while(aux!=NULL){
		if(aux->reservacion>mayor->reservacion){
			mayor = aux; 
		}
		aux= aux->siguiente;
	}
	return DevolverTren2(DevolverTipoTren(tipoTrenes, mayor->identificacion)->tren,mayor->codTren);
}

pnodoBoleteria TrenMenor(listaBoleteria &Tren, pNodoTipoTren &tipoTrenes){
	pnodoBoleteria aux = Tren.primero;
	pnodoBoleteria tren = Tren.primero;
	int menor = aux->reservacion;
	while(aux!=NULL){
		if(menor>aux->reservacion){
			menor = aux->reservacion;
			tren = aux;
		}
		aux = aux->siguiente;
	}
	return tren;
}


 NodoAVLTren* unirTren(NodoAVLTren* izq, NodoAVLTren* der){
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    NodoAVLTren* centro = unirTren(izq->izquierda, der->derecha);
    izq->derecha = centro;
    der->izquierda = izq;
    return der;
}

void EliminarTren(NodoAVLTren* &tren, int x){
     if(tren==NULL) return;

     if(x<tren->codTren)
         EliminarTren(tren->izquierda, x);
     else if(x>tren->codTren)
         EliminarTren(tren->derecha, x);

     else{
         NodoAVLTren* p = tren;
         tren = unirTren(tren->izquierda, tren->derecha);
         delete p;
     }
}


 pnodoAA unirCR(pnodoAA izq, pnodoAA der){
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    pnodoAA centro = unirCR(izq->Hder, der->Hizq);
    izq->Hder = centro;
    der->Hizq = izq;
    return der;
}

void EliminarCR(pnodoAA &codR, int x){
     if(codR==NULL) return;

     if(x<codR->valor)
         EliminarCR(codR->Hizq, x);
     else if(x>codR->valor)
         EliminarCR(codR->Hder, x);

     else{
         pnodoAA p = codR;
         codR = unirCR(codR->Hizq, codR->Hder);
         delete p;
     }
}

NodoAVLTren* DevolverTrenX(NodoAVLTren* &R,int codTren){
	 if(R->codTren==codTren){
	 	return R;
	 }
	 else if(codTren<=R->codTren){
	 	return DevolverTrenX(R->izquierda,codTren);
	 }
	 else{
	 	return DevolverTrenX(R->derecha,codTren);
	 }
}

void EliminarTren(pNodoTipoTren &tipoTrenes){
	int codTipTren; cout<<"Ingrese el codigo de tipo de tren: "; cin>>codTipTren; cout<<endl;
	int codTren; cout<<"Ingrese el codigo de tren: "; cin>>codTren; cout<<endl;
	if(ExisteTipoTren(tipoTrenes,codTipTren)){
    	pNodoTipoTren tipoTren = DevolverTipoTren(tipoTrenes,codTipTren);
    	if(ExisteTren(tipoTrenes->tren,codTren)){
    		NodoAVLTren* aux = DevolverTrenX(tipoTrenes->tren,codTren);
    		cout<<"Rutas del tren: "<<endl;
    		aux->codRutas.PreordenAA(aux->codRutas.raiz);
    		while(aux->codRutas.raiz!=NULL){
    			EliminarCR(aux->codRutas.raiz,aux->codRutas.raiz->valor); //ARREGLAR BORRADO DE AA
			}
			cout<<"Rutas del tren despues de eliminar: "<<endl;
    		aux->codRutas.PreordenAA(aux->codRutas.raiz);
    		
    		EliminarTren(tipoTrenes->tren,codTren);
    		cout<<"Tren eliminado con exito."<<endl;
		}else{
			cout<<"El codigo de tren no existe"<<endl;
		}	
	}else{
		cout<<"El codigo de tipo de tren no existe"<<endl;
	}
}





#endif	

