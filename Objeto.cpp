/*
 * =====================================================================================
 *
 *       Filename:  Objeto.cpp
 *
 *        Version:  1.0
 *        Created:  12/29/2016 01:56:54 PM
 *       Compiler:  g++ -std=c++11 -pthread Monumento.cpp -o main
 *
 *         Author:  JORGE CHATO
 *            NIP:  651348
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include "Objeto.h"


void crear(const string title,const Coordinates coordinates, const string link,
      const string description, const string category, const string date, const string icon, Objeto &o){
  o.title = title;
  o.coordinates = coordinates;
  o.link = link;
  o.description = description;
  o.category = category;
  o.date = date;
  o.icon = icon;
}

string getTitle(const Objeto &o){
  return o.title;
}

Coordinates getCoordinates(const Objeto &o){
  return o.coordinates;
}

string getLink(const Objeto &o){
  return o.link;
}

string getDescription(const Objeto &o){
  return o.description;
}

string getCategory(const Objeto &o){
  return o.category;
}

string getDate(const Objeto &o){
  return o.date;
}

string getIcon(const Objeto &o){
  return o.icon;
}

string allToString(const Objeto &o){
  return o.title + ", " + o.description + ", " + o.category + ", " + o.date + ", " + o.icon;
}

string generateString(const Objeto &o){
  return "TITLE: " + o.title + "\nCOORDINATES: "+ to_string(o.coordinates.lon) +
    "," + to_string(o.coordinates.lat) + "\nLINK: " + o.link + "\nDESCRIPTION: " +
    o.description + "\nCATEGORY: " + o.category + "\nDATE: " + o.date +
    "\nICON: " + o.icon;
}
