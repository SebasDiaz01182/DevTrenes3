#ifndef AAA_H
#define	AAA_H
#include <iostream>

using namespace std;


class NodoRuta {
    public:

    NodoRuta(int num, int niv, NodoRuta *der = NULL, NodoRuta *izq = NULL):
        Hizq(izq), Hder(der), valor(num), nivel(niv){}

    int valor;
    int nivel;
    NodoRuta *Hizq, *Hder;

    friend class ArbolRutas;
};
typedef NodoRuta *pnodoAA;
typedef NodoRuta *pNodoBinarioAA;

class ArbolRutas{
    public:
    pnodoAA raiz;
    ArbolRutas():raiz(NULL){}

    pnodoAA insertar(pNodoBinarioAA &raizP, int num);
    pnodoAA Giro(pnodoAA &nodoP);
    pnodoAA Reparto(pnodoAA &nodoP);
    pnodoAA insertarBalanceado(int num);
    void PreordenAA(pnodoAA raizP);
};
pnodoAA ArbolRutas::Giro(pnodoAA &nodoP){
    if (nodoP==NULL){
        return NULL;
        }
    else if ((nodoP->Hizq) && (nodoP->Hizq->nivel == nodoP->nivel)){
        pnodoAA L = nodoP->Hizq;
        nodoP->Hizq = L->Hder;
        L->Hder = nodoP;
        return L;
    }
    else
        return nodoP;
}
pnodoAA ArbolRutas::Reparto(pnodoAA &nodoP){
    if (nodoP==NULL){
        return NULL;
    }
    else if ((nodoP->Hder->Hder) && (nodoP->nivel == nodoP->Hder->Hder->nivel)){
        pnodoAA R = nodoP->Hder;
        nodoP->Hder = R->Hizq;
        R->Hizq = nodoP;
        R->nivel++; 
        return R;
    }
    return nodoP;
}
pnodoAA ArbolRutas::insertar(pNodoBinarioAA &raizP, int num){
    if(raizP==NULL){
        return raizP=new NodoRuta(num, 1);
    }
    else{
        if (num<raizP->valor)
        {
            raizP->Hizq = insertar(raizP->Hizq, num);
        }
        else if (num>raizP->valor)
        {
            raizP->Hder = insertar(raizP->Hder, num);
        }
        else
        {
            return raizP;
        }
        
        raizP = Giro(raizP);
        raizP = Reparto(raizP);
    }
    return raizP;
}

pnodoAA ArbolRutas::insertarBalanceado(int num){
    pnodoAA nuevoArbol = insertar(raiz, num);
    return nuevoArbol;
}

void ArbolRutas::PreordenAA(pnodoAA raizP){
    if(raizP==NULL){
        return;
    }
	else{
        PreordenAA(raizP->Hizq);
        cout<<raizP->valor<<" -> "<<raizP->nivel<<endl;
        PreordenAA(raizP->Hder);
    }
}

bool ExisteCodRuta(pnodoAA &raizP, int codRuta){
    if(raizP==NULL){
        return false;
    }
	else{
		if(raizP->valor==codRuta){
			return true;
		}
        ExisteCodRuta(raizP->Hizq, codRuta);
        ExisteCodRuta(raizP->Hder, codRuta);
    }
}


#endif
