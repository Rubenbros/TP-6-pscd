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
#include <vector>
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

void buscarObjetos(const string query, middleware &m, vector<Objeto> &res){
  if(!esVacio(m.d)){
    iniciarIterador(m.d);
    while(existeSiguiente(m.d)){
      string cod;
      Objeto o;
      bool error;
      siguiente(m.d, cod, o, error);
      //cout << generateString(o);
      if(!error && allToString(o).find(query) != std::string::npos){
        res.push_back(o);
      }
    }
  }
}
