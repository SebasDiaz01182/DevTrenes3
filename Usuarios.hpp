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
	//Prototipos
  	void insertNonFull(int k,string pnombre,int ppais,int pciudad,int pestado);
  	void splitChild(int i, NodoUsuario *y);
  	void traverse();
	bool ModEstMigratorio(int k, int estMigratorio);
	bool DevolverMigra(int k);

    int findKey(int k); //listo

    void remove(int k); 

    void removeFromLeaf(int idx); 

    void removeFromNonLeaf(int idx); 

    int getPred(int idx); 

    int getSucc(int idx); 

    void fill(int idx); 

    void borrowFromPrev(int idx); 
  
    void borrowFromNext(int idx); 

    void merge(int idx);
  

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
	
	void insert(int k); 
    void remove(int k);
	void EliminarB(int k); 
	
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

int NodoUsuario::findKey(int k) { 
    int idx=0; 
    while (idx<n && keys[idx] < k) 
        ++idx; 
    return idx; 
}

void NodoUsuario::remove(int k) { 
    int idx = findKey(k); 
  
    // The key to be removed is present in this node 
    if (idx < n && keys[idx] == k) 
    { 
  
        // If the node is a leaf node - removeFromLeaf is called 
        // Otherwise, removeFromNonLeaf function is called 
        if (leaf) 
            removeFromLeaf(idx); 
        else
            removeFromNonLeaf(idx); 
    } 
    else
    { 
  
        // If this node is a leaf node, then the key is not present in tree 
        if (leaf) 
        { 
            cout << "The key "<< k <<" is does not exist in the tree\n"; 
            return; 
        } 
  
        // The key to be removed is present in the sub-tree rooted with this node 
        // The flag indicates whether the key is present in the sub-tree rooted 
        // with the last child of this node 
        bool flag = ( (idx==n)? true : false ); 
  
        // If the child where the key is supposed to exist has less that t keys, 
        // we fill that child 
        if (C[idx]->n < t) 
            fill(idx); 
  
        // If the last child has been merged, it must have merged with the previous 
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the 
        // (idx)th child which now has atleast t keys 
        if (flag && idx > n) 
            C[idx-1]->remove(k); 
        else
            C[idx]->remove(k); 
    } 
    return; 
}

void NodoUsuario::removeFromLeaf (int idx) { 
  
    // Move all the keys after the idx-th pos one place backward 
    for (int i=idx+1; i<n; ++i){
    	keys[i-1] = keys[i];
    	nombres[i-1] = nombres[i];
    	pais[i-1] = pais[i];
    	ciudad[i-1] = ciudad[i];
    	estado[i-1] = estado[i];
	}        
  
    // Reduce the count of keys 
    n--; 
  
    return; 
}

void NodoUsuario::removeFromNonLeaf(int idx) { 
  
    int k = keys[idx]; 
  
    // If the child that precedes k (C[idx]) has atleast t keys, 
    // find the predecessor 'pred' of k in the subtree rooted at 
    // C[idx]. Replace k by pred. Recursively delete pred 
    // in C[idx] 
    if (C[idx]->n >= t) 
    { 
        int pred = getPred(idx); 
        keys[idx] = pred;
		//nombres[idx] = pred;
		//pais[idx] = pred;
		//ciudad[idx] = pred;
		//estado[idx] = pred;     
        C[idx]->remove(pred); 
    } 
  
    // If the child C[idx] has less that t keys, examine C[idx+1]. 
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in 
    // the subtree rooted at C[idx+1] 
    // Replace k by succ 
    // Recursively delete succ in C[idx+1] 
    else if  (C[idx+1]->n >= t) 
    { 
        int succ = getSucc(idx); 
        keys[idx] = succ;
		//nombres[idx] = succ;
		//pais[idx] = succ;
		//ciudad[idx] = succ;
		//estado[idx] = succ;     
        C[idx+1]->remove(succ); 
    } 
  
    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1] 
    // into C[idx] 
    // Now C[idx] contains 2t-1 keys 
    // Free C[idx+1] and recursively delete k from C[idx] 
    else
    { 
        merge(idx); 
        C[idx]->remove(k); 
    } 
    return; 
} 


int NodoUsuario::getPred(int idx) { 
    // Keep moving to the right most node until we reach a leaf 
    NodoUsuario *cur=C[idx]; 
    while (!cur->leaf) 
        cur = cur->C[cur->n]; 
  
    // Return the last key of the leaf 
    return cur->keys[cur->n-1]; 
}

int NodoUsuario::getSucc(int idx) { 
  
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf 
    NodoUsuario *cur = C[idx+1]; 
    while (!cur->leaf) 
        cur = cur->C[0]; 
  
    // Return the first key of the leaf 
    return cur->keys[0]; 
} 

void NodoUsuario::fill(int idx) { 
  
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key 
    // from that child 
    if (idx!=0 && C[idx-1]->n>=t) 
        borrowFromPrev(idx); 
  
    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key 
    // from that child 
    else if (idx!=n && C[idx+1]->n>=t) 
        borrowFromNext(idx); 
  
    // Merge C[idx] with its sibling 
    // If C[idx] is the last child, merge it with with its previous sibling 
    // Otherwise merge it with its next sibling 
    else
    { 
        if (idx != n) 
            merge(idx); 
        else
            merge(idx-1); 
    } 
    return; 
}

void NodoUsuario::borrowFromPrev(int idx) { 
  
    NodoUsuario *child=C[idx]; 
    NodoUsuario *sibling=C[idx-1]; 
  
    // The last key from C[idx-1] goes up to the parent and key[idx-1] 
    // from parent is inserted as the first key in C[idx]. Thus, the  loses 
    // sibling one key and child gains one key 
  
    // Moving all key in C[idx] one step ahead 
    for (int i=child->n-1; i>=0; --i){
    	child->keys[i+1] = child->keys[i];
		child->nombres[i+1] = child->nombres[i];
		child->pais[i+1] = child->pais[i];
		child->ciudad[i+1] = child->ciudad[i];
		child->estado[i+1] = child->estado[i];     
	} 
    // If C[idx] is not a leaf, move all its child pointers one step ahead 
    if (!child->leaf) 
    { 
        for(int i=child->n; i>=0; --i) 
            child->C[i+1] = child->C[i]; 
    } 
  
    // Setting child's first key equal to keys[idx-1] from the current node 
    child->keys[0] = keys[idx-1];
	child->nombres[0] = nombres[idx-1]; 
	child->pais[0] = pais[idx-1]; 
	child->ciudad[0] = ciudad[idx-1];
	child->estado[0] = estado[idx-1];   
  
    // Moving sibling's last child as C[idx]'s first child 
    if(!child->leaf) 
        child->C[0] = sibling->C[sibling->n]; 
  
    // Moving the key from the sibling to the parent 
    // This reduces the number of keys in the sibling 
    keys[idx-1] = sibling->keys[sibling->n-1];
	nombres[idx-1] = sibling->nombres[sibling->n-1];
	pais[idx-1] = sibling->pais[sibling->n-1];
	ciudad[idx-1] = sibling->ciudad[sibling->n-1];
	estado[idx-1] = sibling->estado[sibling->n-1]; 
  
    child->n += 1; 
    sibling->n -= 1; 
  
    return; 
} 

void NodoUsuario::borrowFromNext(int idx) { 
  
    NodoUsuario *child=C[idx]; 
    NodoUsuario *sibling=C[idx+1]; 
  
    // keys[idx] is inserted as the last key in C[idx] 
    child->keys[(child->n)] = keys[idx];
    child->nombres[(child->n)] = nombres[idx];
    child->pais[(child->n)] = pais[idx];
    child->ciudad[(child->n)] = ciudad[idx];
    child->estado[(child->n)] = estado[idx];
	 
  
    // Sibling's first child is inserted as the last child 
    // into C[idx] 
    if (!(child->leaf)) 
        child->C[(child->n)+1] = sibling->C[0]; 
  
    //The first key from sibling is inserted into keys[idx] 
    keys[idx] = sibling->keys[0];
	nombres[idx] = sibling->nombres[0];
	pais[idx] = sibling->pais[0];
	ciudad[idx] = sibling->ciudad[0];
	estado[idx] = sibling->estado[0];     
  
    // Moving all keys in sibling one step behind 
    for (int i=1; i<sibling->n; ++i){
		sibling->keys[i-1] = sibling->keys[i];
		sibling->nombres[i-1] = sibling->nombres[i];
		sibling->pais[i-1] = sibling->pais[i];
		sibling->ciudad[i-1] = sibling->ciudad[i];
		sibling->estado[i-1] = sibling->estado[i];
	}  
  
    // Moving the child pointers one step behind 
    if (!sibling->leaf) 
    { 
        for(int i=1; i<=sibling->n; ++i) 
            sibling->C[i-1] = sibling->C[i]; 
    } 
  
    // Increasing and decreasing the key count of C[idx] and C[idx+1] 
    // respectively 
    child->n += 1; 
    sibling->n -= 1; 
  
    return; 
}


void NodoUsuario::merge(int idx){ 
    NodoUsuario *child = C[idx]; 
    NodoUsuario *sibling = C[idx+1]; 
  
    // Pulling a key from the current node and inserting it into (t-1)th 
    // position of C[idx] 
    child->keys[t-1] = keys[idx]; 
  	child->nombres[t-1] = nombres[idx];
	child->pais[t-1] = pais[idx];
	child->ciudad[t-1] = ciudad[idx];
	child->estado[t-1] = estado[idx];    
    // Copying the keys from C[idx+1] to C[idx] at the end 
    for (int i=0; i<sibling->n; ++i){
		child->keys[i+t] = sibling->keys[i];
		child->nombres[i+t] = sibling->nombres[i];
		child->pais[i+t] = sibling->pais[i];
		child->ciudad[i+t] = sibling->ciudad[i];
		child->estado[i+t] = sibling->estado[i];     
	} 
    // Copying the child pointers from C[idx+1] to C[idx] 
    if (!child->leaf) 
    { 
        for(int i=0; i<=sibling->n; ++i) 
            child->C[i+t] = sibling->C[i]; 
    } 
  
    // Moving all keys after idx in the current node one step before - 
    // to fill the gap created by moving keys[idx] to C[idx] 
    for (int i=idx+1; i<n; ++i){
		keys[i-1] = keys[i];
		nombres[i-1] = nombres[i];
		pais[i-1] = pais[i];
		ciudad[i-1] = ciudad[i];
		estado[i-1] = estado[i];
	}  
  
    // Moving the child pointers after (idx+1) in the current node one 
    // step before 
    for (int i=idx+2; i<=n; ++i) 
        C[i-1] = C[i]; 
  
    // Updating the key count of child and the current node 
    child->n += sibling->n+1; 
    n--; 
  
    // Freeing the memory occupied by sibling 
    delete(sibling); 
    return; 
} 

void ArbolUsuario::EliminarB(int k) 
{ 
    if (!root) { 
        cout <<"No hay administradores registrados"<<endl; 
        return; 
    } 
  
    // Call the remove function for root 
    root->remove(k); 
  
    // If the root node has 0 keys, make its first child as the new root 
    //  if it has a child, otherwise set root as NULL 
    if (root->n==0) 
    { 
        NodoUsuario *tmp = root; 
        if (root->leaf) 
            root = NULL; 
        else
            root = root->C[0]; 
  
        // Free the old root 
        delete tmp; 
    } 
    return; 
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
  	estado[i] = 1;
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
