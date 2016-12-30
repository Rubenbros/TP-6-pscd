//*****************************************************************
// File:   Cliente.cpp
// Author: PSCD-Unizar
// Date:   noviembre 2015
// Coms:   Ejemplo de cliente con comunicación síncrona mediante sockets
//         Compilar el fichero "Makefile" asociado, mediante
//         "make".
//*****************************************************************

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Objeto.h"
#include "middleware.h"
#include "Socket.h"

using namespace std;

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres

int main(int argc, char** argv) {
	const string MENS_FIN("FIN");
    // Dirección y número donde escucha el proceso servidor
    string SERVER_ADDRESS = argv[2];
    int SERVER_PORT = atoi(argv[1]);

	// Creación del socket con el que se llevará a cabo
	// la comunicación con el servidor.
	Socket socket(SERVER_ADDRESS, SERVER_PORT);

    // Conectamos con el servidor. Probamos varias conexiones
	const int MAX_ATTEMPS = 10;
	int count = 0;
	int socket_fd;
	do {
		// Conexión con el servidor
    	socket_fd = socket.Connect();
    	count++;

    	// Si error --> esperamos 1 segundo para reconectar
    	if(socket_fd == -1){
    	    this_thread::sleep_for(chrono::seconds(1));
    	}
    } while(socket_fd == -1 && count < MAX_ATTEMPS);

    // Chequeamos si se ha realizado la conexión
    if(socket_fd == -1){
    	return socket_fd;
    }

    
    string mensaje;
    int i = 0;
	do{
		// Leer mensaje de la entrada estandar
		cout << "Termino referente a un monumento (FIN para acabar): ";
		getline(cin, mensaje);
		// Enviamos el mensaje
	    int send_bytes = socket.Send(socket_fd, mensaje);

	    if(send_bytes == -1){
			cerr << "Error al enviar datos: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
			exit(1);
		}

		if(mensaje == MENS_FIN){
			i = 4;
		}
		i++;
	} while(i < 5);

	    // Buffer para almacenar la respuesta
		string buffer[5];

		// Recibimos la respuesta del servidor  
		int read_bytes = socket.Recv(socket_fd, buffer[0], MESSAGE_SIZE);
		if(read_bytes == -1) {
			cerr << "Error al recibir datos: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
		}
		if(buffer[0] == "No puedo atenderte"){
			cout << buffer[0] << endl;
		}
		else if (buffer[0] == "Nada encontrado"){
			cout << buffer[0] << endl;
		}
		else{
			middleware monumentos;
  			crearJson("out/monumentos.json", monumentos);
  			parsearJson(monumentos);
  			//cout << generarString(monumentos) << endl;
  			vector<Objeto> monumento;
  			buscarObjetos(buffer[0], monumentos, monumento);
  			for(Objeto m: monumento){
    			cout << "**********" << endl;
    			cout << generateString(m) << endl;
  			}
    		i = 1;
    		bool final = false;
    		do{
    			int read_bytes = socket.Recv(socket_fd, buffer[i], MESSAGE_SIZE);
				if(read_bytes == -1) {
					cerr << "Error al recibir datos: " << strerror(errno) << endl;
					// Cerramos el socket
					socket.Close(socket_fd);
				}
				if(buffer[i] == MENS_FIN){
					final = true;
				}
				else{
					buscarObjetos(buffer[0], monumentos, monumento);
	  				for(Objeto m: monumento){
    					cout << "**********" << endl;
    					cout << generateString(m) << endl;
					}
	    			i++;
	    		}
    		} while(i < 5);
    		string solicitud;
    		int num = i;
    		while(num > i-1){
	    		cout << "Elija un monumento entre 0 y " << i-1 << endl;
	    		getline(cin, solicitud);
	    		num = atoi(solicitud.c_str());
	    	}
	    	int read_bytes = socket.Recv(socket_fd, buffer[num], MESSAGE_SIZE);
			if(read_bytes == -1) {
				cerr << "Error al recibir datos: " << strerror(errno) << endl;
				// Cerramos el socket
				socket.Close(socket_fd);
			}
			string respuesta;
			read_bytes = socket.Recv(socket_fd, respuesta, MESSAGE_SIZE);
			if(read_bytes == -1) {
				cerr << "Error al recibir datos: " << strerror(errno) << endl;
				// Cerramos el socket
				socket.Close(socket_fd);
			}
		}


    // Cerramos el socket
    int error_code = socket.Close(socket_fd);
    if(error_code == -1){
		cerr << "Error cerrando el socket: " << strerror(errno) << endl;
    }

    return error_code;
}
