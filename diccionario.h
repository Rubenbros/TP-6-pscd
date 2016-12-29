/*
 * =====================================================================================
 *
 *       Filename:  diccionario.h
 *
 *        Version:  1.0
 *        Created:  12/4/2016 04:11:30 PM
 *       Compiler:  g++
 *
 *         Author:  Jorge Chato Astrain (651348)
 *
 * =====================================================================================
 */


#ifndef DICCIONARIO_H
#define DICCIONARIO_H
#include "pila.h"
using namespace std;
template <typename clave,typename valor> struct diccionario;
/* Los valores del TAD representan conjuntos de pares (clave,valor), en los que no se permiten claves 
 * repetidas, y que cuentan con las operaciones de un iterador que permite recorrer los datos
 * del diccionario segun el orden por clave, de menor a mayor.
 */
/* El parametro formal clave tiene definida la operacion de comparacion "<" :
 * clave c1 < clave c2   -> devuelve true si y solo si c1 es menor estricto que c2
 */
template <typename clave,typename valor> void crear(diccionario<clave,valor> &d);
/* Devuelve un diccionario vacio, sin elementos (pares)
 */
template <typename clave,typename valor> bool anyadir(diccionario<clave,valor> &d, const clave& c, const valor& v);
/* Si en d no hay ningún par con clave c, devuelve un diccionario igual al resultante de añadir
 * el par (c,v) a d; si en d hay un par (c,v’), entonces devuelve un diccionario igual al
 * resultante de sustituir (c,v’) por el par (c,v)
 */
template <typename clave,typename valor> bool obtenerValor(const diccionario<clave,valor> &d, const clave& c, valor& v);
/* Si en d existe un par (c,v) devuelve en v el valor de v y devuelve true, en caso contrario devuelve false.
 */
template <typename clave,typename valor> bool quitar(diccionario<clave,valor> &d, const clave& c);
/* Si c está en d, devuelve un diccionario igual al resultante de borrar en d el par con clave c y devuelve true;
 * si c no está en d, devuelve un diccionario igual a d y devuelve false
 */
template <typename clave,typename valor> int cardinal(const diccionario<clave,valor> &d);
/* Devuelve el numero de elementos (de pares) en el diccionario d
 */
template <typename clave,typename valor> bool esVacio(const diccionario<clave,valor> &d);
/* Devuelve verdad si y solo si d no tiene elementos
 */
 
/*Operaciones de iterador interno, para recorrer los datos del diccionario en orden por clave de
 * menor a mayor
 */
template <typename clave,typename valor> void iniciarIterador(diccionario<clave,valor> &d);
/* Prepara el iterador y su cursor para que el siguiente elemento (par) a visitar sea el primero
 * del diccionario d (situación de no haber visitado ningún elemento)
 */
template <typename clave,typename valor> bool existeSiguiente(const diccionario<clave,valor> &d);
/* Devuelve falso si ya se ha visitado el último elemento, devuelve verdad en caso contrario}
 */
template <typename clave,typename valor> void siguiente(diccionario<clave,valor> &d, clave& c, valor& v, bool &error);
/* Devuelve la clave y el valor del siguiente par a visitar de d y avanza el iterador, si no quedan claves por visitar devuelve error=true
 */

template <typename clave,typename valor> struct diccionario{
private:
        struct nodo{
            clave c;
            valor v;
            nodo* izq;
            nodo* der;
        };
        nodo* raiz;
        int tam;
        pila<diccionario::nodo*> iter;
        
    template <typename p1,typename p2> friend void insertar(typename diccionario<p1,p2>::nodo* &abb, const p1& c, const p2& v,bool& insertado);
    template <typename p1,typename p2> friend void buscar(const typename diccionario<p1,p2>::nodo* abb,const p1& c, p2& v,bool& encontrado);
    template <typename p1,typename p2> friend void remover(typename diccionario<p1,p2>::nodo* &abb,const p1& c, bool& quitado);
    template <typename p1,typename p2> friend void max(const typename diccionario<p1,p2>::nodo* abb, p1& c, p2& v);
public:
    friend void crear<clave,valor>(diccionario<clave,valor> &d);
    friend bool anyadir<clave,valor>(diccionario<clave,valor> &d, const clave& c, const valor& v);
    friend bool obtenerValor<clave,valor>(const diccionario<clave,valor> &d, const clave& c, valor& v);
    friend bool quitar<clave,valor>(diccionario<clave,valor> &d, const clave& c);
    friend int cardinal<clave,valor>(const diccionario<clave,valor> &d);
    friend bool esVacio<clave,valor>(const diccionario<clave,valor> &d);
    friend void iniciarIterador<clave,valor>(diccionario<clave,valor> &d);
    friend bool existeSiguiente<clave,valor>(const diccionario<clave,valor> &d);
    friend void siguiente<clave,valor>(diccionario<clave,valor> &d, clave& c, valor& v, bool &error);
};

template <typename clave,typename valor> void crear(diccionario<clave,valor> &d){
    d.raiz=nullptr;
    d.tam=0;
}
/* Si en abb no hay ningún par con clave c, devuelve un diccionario igual al resultante de añadir
 * el par (c,v) a d; si en d hay un par (c,v’), entonces devuelve un diccionario igual al
 * resultante de sustituir (c,v’) por el par (c,v), si lo ha insertado insertado=true
 */
template <typename clave,typename valor> void insertar(typename diccionario<clave,valor>::nodo* &abb, const clave& c, const valor& v,bool& insertado){
    if(abb==nullptr){
        typename diccionario<clave,valor>::nodo* aux= new typename diccionario<clave,valor>::nodo;
        aux->c=c;
        aux->v=v;
        aux->izq=nullptr;
        aux->der=nullptr;
        abb=aux;
        insertado=true;
    }
    else if(c<(abb->c)){
        insertar(abb->izq,c,v,insertado);
    }
    else if(c>(abb->c)){
        insertar(abb->der,c,v,insertado);
    }
    else{//c==abb->c
        abb->v=v;
        insertado=false;
    }
}

template <typename clave,typename valor> bool anyadir(diccionario<clave,valor> &d, const clave& c, const valor& v){
    bool insertado=false;
    insertar<clave,valor>(d.raiz,c,v,insertado);
    if(insertado){
        d.tam++;
    }
    return insertado;
}
/* Si en abb existe un par (c,v) devuelve en v el valor de v y devuelve true, en caso contrario devuelve false.
 */
template <typename clave,typename valor> void buscar(const typename diccionario<clave,valor>::nodo* abb,const clave& c, valor& v,bool& encontrado){
    if(abb==nullptr){
    }
    else if(abb->c==c){
        v=abb->v;
        encontrado=true;
    }
    else if(c<(abb->c)){
        buscar<clave,valor>(abb->izq,c,v,encontrado);
    }
    else{//c>(abb->c)
        buscar<clave,valor>(abb->der,c,v,encontrado);
    }
}

template <typename clave,typename valor> bool obtenerValor(const diccionario<clave,valor> &d, const clave& c, valor& v){
    bool encontrado=false;
    buscar<clave,valor>(d.raiz,c,v,encontrado);
    return encontrado;
}
/* Pre: abb es no vacio
 * Devuelve el maximo elemento de abb y su valor
 */
template <typename clave,typename valor> void max(const typename diccionario<clave,valor>::nodo* abb, clave& c, valor& v){
    if(abb->der==nullptr){
        c=abb->c;
        v=abb->v;
    }
    else{
        max<clave,valor>(abb->der,c,v);
    }
}

/* Si c está en abb, devuelve un diccionario igual al resultante de borrar en abb el par con clave c y devuelve true;
 * si c no está en abb, devuelve un diccionario igual a abb y devuelve false
 */
template <typename clave,typename valor> void remover(typename diccionario<clave,valor>::nodo* &abb,const clave& c, bool& quitado){
    if(abb==nullptr){
    }
    else if(c<(abb->c)){
        remover<clave,valor>(abb->izq,c,quitado);
    }
    else if(c>(abb->c)){
        remover<clave,valor>(abb->der,c,quitado);
    }
    else{//abb->c==c
        if(abb->izq==nullptr){
            typename diccionario<clave,valor>::nodo* aux;
            quitado=true;
            aux=abb;
            abb=abb->der;
            delete(aux);
        }
        else{
            max<clave,valor>(abb->izq,abb->c,abb->v);
            remover<clave,valor>(abb->izq,abb->c,quitado);
        }
    }
}

template <typename clave,typename valor> bool quitar(diccionario<clave,valor> &d, const clave& c){
    bool quitado=false;
    remover<clave,valor>(d.raiz,c,quitado);
    if(quitado){
        d.tam--;
    }
    return quitado;
}

template <typename clave,typename valor> int cardinal(const diccionario<clave,valor> &d){
    return d.tam;
}

template <typename clave,typename valor> bool esVacio(const diccionario<clave,valor> &d){
    return d.tam==0;
}

template <typename clave,typename valor> void iniciarIterador(diccionario<clave,valor> &d){
    typename diccionario<clave,valor>::nodo* aux; 
    crearPila(d.iter);
    aux=d.raiz;
    while(aux!=nullptr){
        apilar(d.iter,aux);
        aux=aux->izq;
    }
}

template <typename clave,typename valor> bool existeSiguiente(const diccionario<clave,valor> &d){
    return !esVacia(d.iter);
}

template <typename clave,typename valor> void siguiente(diccionario<clave,valor> &d, clave& c, valor& v, bool &error){
    typename diccionario<clave,valor>::nodo* aux; 
    if(existeSiguiente(d)){
        error=false;
        bool errorAux;
        cima(d.iter,aux,errorAux);
        desapilar(d.iter);
        c=aux->c;
        v=aux->v;
        aux=aux->der;
        while(aux!=nullptr){
            apilar(d.iter,aux);
            aux=aux->izq;
        }
    }
    else{
        error=true;
    }
}
#endif
