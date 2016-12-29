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
#include "middleware.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Main
 *  Description:  
 * =====================================================================================
 */
int main(int argc, char *argv[]){
  middleware monumentos;

  crearJson("out/monumentos.json", monumentos);
  parsearJson(monumentos);
  cout << generarString(monumentos) << endl;
  return EXIT_SUCCESS;
}
