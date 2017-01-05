#*****************************************************************
# File:   Makefile
# Author: 
# Date:   diciembre 2016
# Coms:   Compilar mediante "make"
#*****************************************************************

CC = g++
RM=/bin/rm

FLAGS=-std=c++11 -fmax-errors=1 -Werror -I. -O2 -Isrc
LDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -lm -pthread -lcurl -lX11 

# Create the executable
all: Cliente Servidor

Servidor: Servidor.o middleware.o Objeto.o Socket.o
	${CC} $(FLAGS) Servidor.o middleware.o Objeto.o Socket.o -o Servidor ${LDFLAGS}

Servidor.o: Servidor.cpp
	${CC} $(FLAGS) -c Servidor.cpp  

Cliente.o: Cliente.cpp
	${CC} $(FLAGS) -c Cliente.cpp

Cliente: Socket.o Cliente.o  
	${CC} $(FLAGS) Socket.o Cliente.o -o Cliente

#LatLong-UTMconversion.o: LatLong-UTMconversion.cpp LatLong-UTMconversion.h
#	${CC} $(FLAGS) -c LatLong-UTMconversion.cpp 

middleware.o: middleware.cpp middleware.h
	${CC} $(FLAGS) -c middleware.cpp 

Objeto.o: Objeto.cpp Objeto.h
	${CC} $(FLAGS) -c Objeto.cpp 

Socket.o: Socket.h Socket.cpp
	${CC} $(FLAGS) -c Socket.cpp

clean:
	$(RM) -f Cliente Servidor *.o
