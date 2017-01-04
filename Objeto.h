/*
 * =====================================================================================
 *
 *       Filename:  Objeto.h
 *
 *        Version:  1.0
 *        Created:  12/29/2016 01:48:33 PM
 *       Compiler:  g++ -std=c++11 -pthread Monumento.h -o main
 *
 *         Author:  JORGE CHATO
 *            NIP:  651348
 *
 * =====================================================================================
 */

#ifndef OBJETO_H_
#define OBJETO_H_

#include <string>

using namespace std;
struct Coordinates{
  double lon;
  double lat;
};

struct Objeto;
void crear(const string title,const Coordinates coordinates, const string link,
    const string description, const string category, const string date, const string icon, Objeto &o);
string getTitle(const Objeto &o);
Coordinates getCoordinates(const Objeto &o);
string getLink(const Objeto &o);
string getDescription(const Objeto &o);
string getCategory(const Objeto &o);
string getDate(const Objeto &o);
string getIcon(const Objeto &o);
string allToString(const Objeto &o);
string generateString(const Objeto &o);

struct Objeto{
  friend void crear(const string title,const Coordinates coordinates, const string link,
      const string description, const string category, const string date, const string icon, Objeto &o);
  friend string getTitle(const Objeto &o);
  friend Coordinates getCoordinates(const Objeto &o);
  friend string getLink(const Objeto &o);
  friend string getDescription(const Objeto &o);
  friend string getCategory(const Objeto &o);
  friend string getDate(const Objeto &o);
  friend string getIcon(const Objeto &o);
  friend string allToString(const Objeto &o);
  friend string generateString(const Objeto &o);
  int index;

  private:
  string title;
  Coordinates coordinates;
  string link;
  string description;
  string category;
  string date;
  string icon;
};
#endif
