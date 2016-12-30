/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *        Version:  1.0
 *        Created:  12/29/2016 05:04:03 PM
 *       Compiler:  g++ -std=c++11 -pthread main.cpp -o main
 *
 *         Author:  JORGE CHATO
 *            NIP:  651348
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Objeto.h"
#include "middleware.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Main
 *  Description:  
 * =====================================================================================
 */
int main(int argc, char *argv[]){
  middleware monumentos;
  middleware restaurantes;

  crearJson("out/monumentos.json", monumentos);
  crearJson("out/restaurantes.json", restaurantes);
  parsearJson(monumentos);
  parsearJson(restaurantes);

  //cout << generarString(monumentos) << endl;
  Objeto listaMonumentos[5];
  string querys[5] = {"fra", "Jorge", "Expo"};
  cout << querys[4] << endl;
  int error;
  buscarObjetos(querys, monumentos, listaMonumentos, error);
  Coordinates c;
  for(int i = 0; error == -1 && i < 5 && getTitle(listaMonumentos[i]) != ""; i++){
    cout << "*****Monumentos encontrados*****" << endl;
    cout << generateString(listaMonumentos[i]) << endl;
    c.lon = getCoordinates(listaMonumentos[i]).lon;
    c.lat = getCoordinates(listaMonumentos[i]).lat;
  }

  int err;
  //Coordinates c;
  //c.lon = 675125.210000;
  //c.lat = 4613725.410000;
  Objeto listaRestaurantes[5];
  buscarCoordenadas(c, restaurantes, listaRestaurantes, err);
  for(int i = 0; err == -1 && i < 5 && getTitle(listaRestaurantes[i]) != ""; i++){
    cout << "=====Restaurantes cercanos=====" << endl;
    cout << generateString(listaRestaurantes[i]) << endl;
  }
  return EXIT_SUCCESS;
}
