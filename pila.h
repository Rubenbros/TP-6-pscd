/*
 * =====================================================================================
 *
 *       Filename:  pila.h
 *
 *        Version:  1.0
 *        Created:  12/5/2016 04:11:30 PM
 *       Compiler:  g++
 *
 *         Author:  Jorge Chato Astrain (651348)
 *
 * =====================================================================================
 */


#ifndef PILA_H
#define PILA_H
using namespace std;
template <typename elemento> struct pila;
/* Los valores del TAD representan secuencias de elementos con acceso LIFO, esto es, el ultimo
 * elemento añadido sera el primero en ser borrado
 */

/* Devuelve una pila vacia
 */
template <typename elemento> void crearPila(pila<elemento>& p);
/* Devuelve la pila resultante de añadir dato a p
 */
template <typename elemento> void apilar(pila<elemento>& p, const elemento& dato);
/* Si p es no vacia devuelve la pila resultante de quitar dato de p sino devuelve p
 */
template <typename elemento> void desapilar(pila<elemento>& p);
/* Si p no es vacia devuelve su ultimo elemento apilado y error=false, sino devuelve error=true
 */
template <typename elemento> void cima(const pila<elemento>& p, elemento& dato, bool& error);
/* Devuelve verdad si y solo si p no tiene elementos
 */
template <typename elemento> bool esVacia(const pila<elemento>& p);
/* Devuelve el nº de elementos de p
 */
template <typename elemento> int altura(const pila<elemento>& p);
/* Devuelve en p la pila vacia y libera la memoria utilizada previamente por p
 */
template <typename elemento> void liberar(pila<elemento>& p);


template <typename elemento> struct pila{
    friend void crearPila<elemento>(pila<elemento>& p);
    friend void apilar<elemento>(pila<elemento>& p, const elemento& dato);
    friend void desapilar<elemento>(pila<elemento>& p);
    friend void cima<elemento>(const pila<elemento>& p, elemento& dato, bool& error);
    friend bool esVacia<elemento>(const pila<elemento>& p);
    friend int altura<elemento>(const pila<elemento>& p);
    friend void liberar<elemento>(pila<elemento>& p);
    
private:
    struct nodo{
        elemento valor;
        nodo* siguiente;
    };
    nodo* laCima;
    int numDatos;
};
template <typename elemento> void crearPila(pila<elemento>& p){
    p.numDatos=0;
    p.laCima=nullptr;
}

template <typename elemento> void apilar(pila<elemento>& p, const elemento& dato){
    typename pila<elemento>::nodo* aux=new typename pila<elemento>::nodo;
    aux->valor=dato;
    aux->siguiente=p.laCima;
    p.laCima=aux;
    p.numDatos++;
}

template <typename elemento> void desapilar(pila<elemento>& p){
    if(!esVacia(p)){
        typename pila<elemento>::nodo* aux=p.laCima;
        p.laCima=p.laCima->siguiente;
        delete(aux);
        p.numDatos--;
    }
}

template <typename elemento> void cima(const pila<elemento>& p, elemento& dato, bool& error){
    if(esVacia(p)){
        error=true;
    }
    else{
        error=false;
        dato=p.laCima->valor;
    }
}

template <typename elemento> bool esVacia(const pila<elemento>& p){
    return p.laCima==nullptr;
}

template <typename elemento> int altura(const pila<elemento>& p){
    return p.numDatos;
}

template <typename elemento> void liberar(pila<elemento>& p){
    typename pila<elemento>::nodo* aux=p.laCima;
    while(aux!=nullptr){
        p.laCima=p.laCima->siguiente;
        delete(aux);
        aux=p.laCima;
    }
    p.numDatos=0;
}

#endif
