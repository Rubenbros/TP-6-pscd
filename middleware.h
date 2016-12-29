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
#include <vector>
#include "Objeto.h"
#include "diccionario.h"

using namespace std;


struct middleware;

void crearJson(const string path, middleware &m);

bool parsearJson(middleware &m);

void buscarObjetos(const string query, middleware &m, vector<Objeto> &res);

bool anyadirNuevoObjeto(middleware &m, const string &clave, Objeto &valor);

string generarString(middleware &m);

struct middleware{
  friend void crearJson(string nombre, middleware &m);
  friend bool parsearJson(middleware &m);
  friend void buscarObjetos(const string query, middleware &m, vector<Objeto> &res);
  friend string generarString(middleware &m);

  private:
  string path;
  diccionario <string, Objeto> d;
  friend bool anyadirNuevoObjeto(middleware &m, const string &clave, Objeto &valor);
};
#endif
