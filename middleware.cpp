/*
 * =====================================================================================
 *
 *       Filename:  json.cpp
 *
 *        Version:  1.0
 *        Created:  12/29/2016 03:47:39 PM
 *       Compiler:  g++ -std=c++11 -pthread json.cpp -o main
 *
 *         Author:  JORGE CHATO
 *            NIP:  651348
 *
 * =====================================================================================
 */


#include <string>
#include <iostream>
#include <fstream>
#include "src/json.hpp"
#include "diccionario.h"
#include "middleware.h"
#include "Objeto.h"

using namespace std;
using json = nlohmann::json;


void crearJson(const string path, middleware &m){
  m.path = path;
  crear(m.d);
}

bool anyadirNuevoObjeto(middleware &m, const string &clave, Objeto &valor){
  Objeto aux;
  bool anyadido = false;

  if(!obtenerValor(m.d, clave, aux)){
    anyadido = anyadir(m.d, clave, valor);
  }
  return anyadido;
}

bool parsearJson(middleware &m){
  ifstream i(m.path);
  json j;
  i >> j;

  for(int pos = 0; pos < j["features"].size(); pos++){
    Coordinates coordinates;
    Objeto o;

    coordinates.lon = j["features"][pos]["geometry"]["coordinates"][0].get<double>();
    coordinates.lat = j["features"][pos]["geometry"]["coordinates"][1].get<double>();
    string title = j["features"][pos]["properties"]["title"];
    string link = j["features"][pos]["properties"]["link"];
    string description = j["features"][pos]["properties"]["description"];
    string category = j["features"][pos]["properties"]["category"];
    string date = j["features"][pos]["properties"]["date"];
    string icon = j["features"][pos]["properties"]["icon"];

    crear(title, coordinates, link, description, category, date, icon, o);
    string value =  to_string(coordinates.lon) + "," +  to_string(coordinates.lat);
    bool anyadido = anyadirNuevoObjeto(m, value, o);
  }
}

string generarString(middleware &m){
  string lista;

  if(!esVacio(m.d)){
    iniciarIterador(m.d);
    while(existeSiguiente(m.d)){
      string cod;
      Objeto o;
      bool error;
      siguiente(m.d, cod, o, error);
      if(!error){
        lista += "\n**********\n";
        lista += generateString(o);
      }
    }
  }

  return lista;
}

void buscarObjetos(const string querys[5], middleware &m, Objeto (&res)[5], int &error){
  if(!esVacio(m.d)){
    iniciarIterador(m.d);
    int pos = 0;
    bool err;

    while(existeSiguiente(m.d)){
      string cod;
      Objeto o;
      siguiente(m.d, cod, o, err);
      string cadena = allToString(o);
      bool introducido = false;

      for(int i = 0; i < 5 && querys[i] != ""; i++){
        if(pos < 5 && !err && !introducido && cadena.find(querys[i]) != std::string::npos){
          o.index++;
          res[pos] = o;
          pos++;
          introducido = true;
        }else if(introducido){
          res[pos].index++;
        }
      }
    }

    ordenarPorIndex(res);

    error = pos > 0 ? -1 : 0;
    error = err ? 1 : error;
  }
}

void ordenarPorIndex(Objeto (&res)[5]){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 4; j++){
      Objeto aux = res[j];
      if(res[j].index < res[j+1].index){
        res[j] = res[j+1];
        res[j+1] = aux;
      }
    }
  }
}

void buscarCoordenadas(const Coordinates &c, middleware &m, Objeto (&res)[5], int &error){
  if(!esVacio(m.d)){
    iniciarIterador(m.d);
    int pos = 0;
    bool err;

    while(existeSiguiente(m.d)){
      string cod;
      Objeto o;
      siguiente(m.d, cod, o, err);

      if(pos < 5 && !err && floor(c.lon/1000) == floor(getCoordinates(o).lon/1000)
          && floor(c.lat/1000) == floor(getCoordinates(o).lat/1000)){
        res[pos] = o;
        pos++;
      }
    }
    error = pos > 0 ? -1 : 0;
    error = err ? 1 : error;
  }
}
