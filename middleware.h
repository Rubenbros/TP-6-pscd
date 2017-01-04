/*
 * =====================================================================================
 *
 *       Filename:  middleware.h
 *
 *        Version:  1.0
 *        Created:  12/29/2016 01:43:32 PM
 *       Compiler:  g++ -std=c++11 -pthread middleware.h -o main
 *
 *         Author:  JORGE CHATO
 *            NIP:  651348
 *
 * =====================================================================================
 */


#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H
#include <string>
#include "Objeto.h"
#include "diccionario.h"

using namespace std;


struct middleware;

void crearJson(const string path, middleware &m);
//inicializa el TAD middleware con un diccionario (árbol abb) vacío y un path.

bool parsearJson(middleware &m);
//parsear el json con el path m.path. Lo almacena en memoria con un abb.
//devuelve verdadero si y solo si ha sido capaz de añadir el struct Objeto al
//diccionario m.d

void buscarObjetos(const string query[5], middleware &m, Objeto (&res)[5], int &error);
//Valores: querys de búsqueda (max 5), middleware, lista de lugares de salida (max 5), error
//ERROR: NadaEncontrado CODIGO:0, DenegaciónServicio CODIGO:1, Ningún error CODIGO: -1
//Si en el middleware m existe un par que satisfaga alguno de los elementos de
//query,  devolverá un array de Objetos no mayor en dimensión a 5 igual al resultante
//de la comparación con los valores en query.
//Si en el middleware m no existe un par (que satisfaga ninguna de las condiciones) (NadaEncontrado)
//Si existe un error al recorrer el iterador (DenegaciónServicio)

void buscarCoordenadas(const Coordinates &c, middleware &m, Objeto (&res)[5], int &error);
//Valores: struct Coordinates, middleware, lista de lugares de salida (max 5), error
//ERROR: NadaEncontrado CODIGO:0, DenegaciónServicio CODIGO:1, Ningún error CODIGO: -1
//Si en el middleware m existe un par que satisfaga c = getCoordinates(Objeto),
//devolverá un array de Objetos no mayor en dimensión a 5 igual al resultante
//de la comparación.
//Si en el middleware m no existe un par (que satisfaga ninguna de las condiciones) (NadaEncontrado)
//Si existe un error al recorrer el iterador (DenegaciónServicio)

bool anyadirNuevoObjeto(middleware &m, const string &clave, Objeto &valor);
//Almacena en memoria con un abb el Objeto valor con su correspondiente clave
//("lat,lon"). Devuelve verdadero si y solo si ha sido capaz de añadir el
//struct Objeto al diccionario m.d

string generarString(middleware &m);
//Devuelve un string resultante de recorrer m.d.
//"**********"
//TITLE:
//COORDINATES: 0.000000,0.000000
//LINK:
//DESCRIPTION:
//CATEGORY:
//DATE:
//ICON:

void ordenarPorIndex(Objeto (&res)[5]);

struct middleware{
  friend void crearJson(string nombre, middleware &m);
  friend bool parsearJson(middleware &m);
  friend void buscarObjetos(const string query[5], middleware &m, Objeto (&res)[5], int &error);
  friend string generarString(middleware &m);
  friend void buscarCoordenadas(const Coordinates &c, middleware &m, Objeto (&res)[5], int &error);

  private:
  string path;
  diccionario <string, Objeto> d;
  friend bool anyadirNuevoObjeto(middleware &m, const string &clave, Objeto &valor);
  friend void ordenarPorIndex(Objeto (&res)[5]);
};
#endif
