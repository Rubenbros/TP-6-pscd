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
		// si ya no quiero enviar mas
		if(mensaje == MENS_FIN){
			i = 4;
		}
		i++;
	} while(i < 5);

    // Buffer para almacenar la respuesta
	string buffer;

	// Recibimos la respuesta del servidor  
	int read_bytes = socket.Recv(socket_fd, buffer, MESSAGE_SIZE);
	if(read_bytes == -1) {
		cerr << "Error al recibir datos: " << strerror(errno) << endl;
		// Cerramos el socket
		socket.Close(socket_fd);
	}
	if(buffer == "No puedo atenderte"){
		cout << buffer << endl;
	}
	else if (buffer == "Nada encontrado"){
		cout << buffer << endl;
	}
	else{
		char *cstr = new char [buffer.length()+1];
  		strcpy (cstr, buffer.c_str());
		char *url;
		url = strtok(cstr,",");
		i = 0;
		while (url != NULL){
			cout << "**********************************" << endl;
			cout << "Monumento numero " << i << endl;
    		string sUrl(url);
    		cout << sUrl << endl;
    		string cmd("firefox "+sUrl);
			int v = system(cmd.c_str());
			if(v != 0){
				cerr << "Ha habido algún problema al abrir el navegador" << endl;
			}
			url = strtok (NULL, ",");
			i++;
		}
		string solicitud;
		int num = i;
		//elije el monumento
		while(num > i-1){
    		cout << "Elija un monumento entre 0 y " << i-1 << endl;
    		getline(cin, solicitud);
    		num = atoi(solicitud.c_str());
    	}
    	
    	//envia el monumento
    	int send_bytes = socket.Send(socket_fd, solicitud);
	    if(send_bytes == -1){
			cerr << "Error al enviar datos: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
			exit(1);
		}


    	string restaurante;
    	//recibe el restaurante
    	int read_bytes = socket.Recv(socket_fd, restaurante, MESSAGE_SIZE);
		if(read_bytes == -1) {
			cerr << "Error al enviar datos: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
		}
		cout << "+++++++++++++++++++++++++++++++++" << endl;
		cout << "Restaurante mas cercano" << endl;
		cout << restaurante << endl;
		string res("firefox "+restaurante);
		int v = system(res.c_str());
		if(v != 0){
			cerr << "Ha habido algún problema al abrir el navegador" << endl;
		}

		string respuesta;
		//recibe el precio
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