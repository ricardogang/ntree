#include <iostream>

using namespace std;
//NODOLISTA.H//////////////////////////////////////////////////////////////////
template <class T>
class NodoLista {
    T dato ;
    NodoLista<T>* siguiente ;
public:
    NodoLista(T d){
        dato= d ;
        siguiente= nullptr;
    }

    T getDato() {
        return dato ;
    }
    void setSiguiente(NodoLista<T> *s) {
        siguiente= s ;
    }
    NodoLista<T>* getSiguiente() {return siguiente;}
};
//LISTA.H//////////////////////////////////////////////////////////////////
template <class T>
class Lista {
    NodoLista<T> *cabeza ;
public:
    Lista<T>(){ cabeza= nullptr ;}

    void Insertar(T dato) {
        NodoLista<T>* n = new NodoLista<T>(dato) ;
        NodoLista<T>* t= cabeza ;
        cabeza = n ;
        cabeza->setSiguiente(t);
    }

    int Longitud() {
        NodoLista<T> *n= cabeza ;
        int c=0 ;
        while (n!=nullptr){
            c++;
            n= n->getSiguiente();
        }
        return c;
    }

    T getI(int i) {
        NodoLista<T> *n= cabeza ;
        int c=0 ;
        while (n!=nullptr&& c<i){
            c++;
            n= n->getSiguiente();
        }
        return n!=nullptr?n->getDato():nullptr;
    }

};

//NODOARBOL.H//////////////////////////////////////////////////////////////////
template <class T>
class NodoArbol {
    T dato ; //dato del usuario
    Lista<NodoArbol*> *hijos ;
public:
    NodoArbol(){hijos= nullptr;}
    NodoArbol(T d) {
        dato= d;
        hijos= nullptr ;
    }

    T getDato() { return dato ; }

    void agregarHijo(T dato){
        NodoArbol<T> *n= new NodoArbol<T>(dato);
        if (hijos==nullptr) {
            hijos= new Lista<NodoArbol*>();
        }
        hijos->Insertar(n);
    }

    int getCantidadDeHijos() {

        return hijos!= nullptr ? hijos->Longitud():0 ;
    }

    NodoArbol* getHijo(int i) {
        return hijos!=nullptr?hijos->getI(i):nullptr;
    }

    bool DatoEsHijo(T dato) ;
    void EliminarHijo(T d) { hijos->Eliminar(d);}
};


//ARBOL.H//////////////////////////////////////////////////////////////////
template <class T>
class Arbol {
    NodoArbol<T> *raiz= new NodoArbol<T>();
public:
    void InsertarRaiz(T dato){ raiz= new NodoArbol<T>(dato);}
    bool Insertar(T padre, T dato) ;
    bool InsertarEnMonticulo(T dato) ;
    int AlturaRecursivo(NodoArbol<T> *n);
    int Altura();
    NodoArbol<T>* Buscar(NodoArbol<T> *n, T dato);
    NodoArbol<T>* BuscarEspacio(NodoArbol<T> *n);
    NodoArbol<T>* HojaMasIzquierda(NodoArbol<T>* n);
    void Eliminar(T d) ;
    NodoArbol<T>* BuscarPadre(NodoArbol<T> *n,T d) ;
    NodoArbol<T>* BuscarPadre(T d) { return BuscarPadre(raiz, d);}

};
//ARBOL.CPP//////////////////////////////////////////////////////////////////
template <class T>
bool Arbol<T>::Insertar(T padre, T dato) {
    bool exito = false ;
    NodoArbol<T> *n= Buscar(raiz, padre) ;
    if (n!=nullptr) {
        n->agregarHijo(dato);
        exito= true ;
    }
    return exito ;
}
template <class T>
bool Arbol<T>::InsertarEnMonticulo(T dato) {
    bool exito = false ;
    NodoArbol<T> *n= BuscarEspacio(raiz) ;
    if (n==nullptr){
        n= HojaMasIzquierda(raiz);
    }
    if (n!=nullptr) {
        n->agregarHijo(dato);
        exito= true ;
    }
    if (true)    {
        ;
    }

    //FALTA REUBICAR ESE NODO INSERTADO COMPARANDO CON SUS PADRES
    return exito ;
}


template <class T>
NodoArbol<T>* Arbol<T>::HojaMasIzquierda(NodoArbol<T>* n){
    NodoArbol<T> *nr= nullptr ;
    if (n!=nullptr && n->getCantidadDeHijos()==0){
        nr= n ;
    } else if (n!=nullptr){
        nr= HojaMasIzquierda(n->getHijo(0));
    }
    return nr ;
}

template <class T>
void Arbol<T>::Eliminar(T dato) {
    NodoArbol<T> *p = BuscarPadre(dato);
    p->EliminarHijo(dato) ;
}

template <class T>
NodoArbol<T>* Arbol<T>::BuscarPadre(NodoArbol<T> *n, T dato) {
    NodoArbol<T>* nr= nullptr ;
    /*
    * buscar entre los hijos inmediatos
    * cuando el dato esta entre los hijos yupi
    * buscar entre los nietos y sub nietos y tataratata...
    * */
    if (n!= nullptr && n->DatoEsHijo(dato)){
        nr= n ; //dato está entre los hijos de n
    } else {
        int i=0 ;
        NodoArbol<T> *h= nullptr ;
        while (n!=nullptr && i<n->getCantidadDeHijos() && nr==nullptr) {
            h= n->getHijo(i);
            nr= BuscarPadre(h, dato);
            i++;
        }
    }
    return nr ;
}

//
template <class T>
bool NodoArbol<T>::DatoEsHijo(T dato){
    int i = 0;
    bool loEncontre= false ;
    while(!loEncontre && i < hijos->Longitud()) {
        if (hijos->getI(i)->getDato()== dato) {
            loEncontre= true ;
        }
        i++;
    }
    return loEncontre;
}


template <class T>
NodoArbol<T>* Arbol<T>::Buscar(NodoArbol<T> *n, T dato){
    NodoArbol<T>* nr= nullptr;
    if (n!=nullptr && n->getDato()==dato) {
        nr= n ;
    } else {
        int i=0 ;
        NodoArbol<T> *h= nullptr ;
        while (n!=nullptr && i<n->getCantidadDeHijos() && nr==nullptr) {
            h= n->getHijo(i);
            nr= Buscar(h, dato);
            i++;
        }
    }
    return nr ;
}

template <class T>
NodoArbol<T>* Arbol<T>::BuscarEspacio(NodoArbol<T> *n){
    NodoArbol<T>* nr= nullptr;
    if (n!=nullptr && n->getCantidadDeHijos()<3 && n->getCantidadDeHijos()>0) {
        nr= n ;
    } else {
        int i=0 ; int a=0 ; int b=1 ;
        NodoArbol<T> *h= nullptr ;
        while (n!=nullptr && i<n->getCantidadDeHijos() && nr==nullptr && a<=b) {
            a= AlturaRecursivo(h);
            h= n->getHijo(i);
            b= AlturaRecursivo(h);
            nr= BuscarEspacio(h);
            i++;
        }
    }
    return nr ;
}

//contribuido por: Fabian y Alvaro
template<class T>
int Arbol<T>::AlturaRecursivo(NodoArbol<T> *n){
    int mayor = 0;
    int contador = 0;
    if(n == nullptr){
        return 0;
    }else{
        for(int i = 0 ; i < n->getCantidadDeHijos(); i++){
            contador = AlturaRecursivo(n->getHijo(i));
            if(contador > mayor){
                mayor = contador;
            }
        }
        return mayor+1;
    }
}
template <class T>
int Arbol<T>::Altura(){
    return AlturaRecursivo(raiz);
}

int main() {
    Arbol<int> *a= new Arbol<int>() ;

    a->InsertarRaiz(23);
    a->Insertar(23,7);
    a->Insertar(23,5);
    a->Insertar(5,11);
    a->Insertar(11,1);
    cout << a->Altura();

    //cout << a->BuscarPadre(7)->getDato();

//    a->Eliminar(7);
//    a->Eliminar(23);

    // a->Insertar(8,4);

    Arbol<string> *ab= new Arbol<string> ;
    ab->InsertarRaiz("hey");
    ab->Insertar("hey","yo");
    cout << ab->Altura();

    Arbol<int> *m= new Arbol<int>() ;
    m->InsertarRaiz(7);
    m->InsertarEnMonticulo(5);
    m->InsertarEnMonticulo(11);
    m->InsertarEnMonticulo(13);
    m->InsertarEnMonticulo(3);
    m->InsertarEnMonticulo(2);
    m->InsertarEnMonticulo(17);
    m->InsertarEnMonticulo(23);

    return 0;
}
