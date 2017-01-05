
#include <iostream>
#include <chrono>
#include <thread>
#include "Objeto.h"
#include "middleware.h"
#include "Socket.h"

using namespace std;
const int NUM_CLIENTES = 100;

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres

void Proceso(int id, Socket socket, int client_fd,middleware& monumentos,middleware& restaurantes){
	int error,servicios=0;
	bool end=false;
	string buffer,respuesta;
	string queries[5];
	while(!end){
		//Recibe la lista de terminos para buscar
		int rcv_bytes = socket.Recv(client_fd, buffer, MESSAGE_SIZE);
		if(rcv_bytes == -1) {
			cerr << "Error al recibir datos: " << strerror(errno) << endl;
			// Cerramos los sockets
			socket.Close(client_fd);
		}
		cout << "Mensaje recibido del cliente " << id <<": '" << buffer << "'" << endl;
		char *cstr = new char [buffer.length()+1];
		strcpy (cstr, buffer.c_str());
		char * pch = strtok (cstr,",");
		for(int i=0;pch!=NULL;i++){
			string s(pch);
			queries[i] = s;
			pch = strtok(NULL,",");
		}
		//Prepara la respuesta
		Objeto listaMonumentos[5];
		buscarObjetos(queries, monumentos, listaMonumentos, error);
		if(error == 0)respuesta="Nada encontrado";
		else if(error ==-1){
			//Prepara una lista con las urls de los monumentos para enviar
			respuesta=getLink(listaMonumentos[0]);
			for (int i=1;i < 5 && getTitle(listaMonumentos[i]) != "";i++)
				respuesta+= "," + getLink(listaMonumentos[i]); 
		}
		else respuesta="No puedo atenderte";
		int send_bytes = socket.Send(client_fd, respuesta);
		if(send_bytes == -1) {
			cerr << "Error al enviar datos: " << strerror(errno) << endl;
			// Cerramos los sockets
			socket.Close(client_fd);
			exit(1);
		}
		servicios++;
		rcv_bytes = socket.Recv(client_fd, buffer, MESSAGE_SIZE);
		if(rcv_bytes == -1) {
			cerr << "Error al recibir datos: " << strerror(errno) << endl;
			// Cerramos los sockets
			socket.Close(client_fd);
		}
		cout << "Mensaje recibido del cliente " << id <<": '" << buffer << "'" << endl;
		if(buffer=="FIN"){
			end=true;
			
		}
		else if(buffer!="OTRA BUSQUEDA"){
			int seleccion = atoi(buffer.c_str());
			Coordinates c;
			c.lon = getCoordinates(listaMonumentos[seleccion]).lon;
			c.lat = getCoordinates(listaMonumentos[seleccion]).lat;
			Objeto listaRestaurantes[5];
			buscarCoordenadas(c, restaurantes, listaRestaurantes, error);
			send_bytes = socket.Send(client_fd, getLink(listaRestaurantes[0]));
			if(send_bytes == -1) {
				cerr << "Error al enviar datos: " << strerror(errno) << endl;
				// Cerramos los sockets
				socket.Close(client_fd);
				exit(1);
			}
			servicios++;
			rcv_bytes = socket.Recv(client_fd, buffer, MESSAGE_SIZE);
			if(rcv_bytes == -1) {
				cerr << "Error al recibir datos: " << strerror(errno) << endl;
				// Cerramos los sockets
				socket.Close(client_fd);
			}
			if(buffer=="FIN"){
				end=true;
			}
		}
	}
	int send_bytes = socket.Send(client_fd, to_string(servicios*3));
	if(send_bytes == -1) {
		cerr << "Error al enviar datos: " << strerror(errno) << endl;
		// Cerramos los sockets
		socket.Close(client_fd);
		exit(1);
	}
}

int main(int argc, char *argv[]) {
	middleware monumentos;
	middleware restaurantes;

	crearJson("out/monumentos.json", monumentos);
	crearJson("out/restaurantes.json", restaurantes);
	parsearJson(monumentos);
	parsearJson(restaurantes);
	// Puerto donde escucha el proceso servidor
	int SERVER_PORT = atoi(argv[1]);
	// CreaciÃ³n del socket con el que se llevarÃ¡ a cabo
	// la comunicaciÃ³n con el servidor.
	Socket socket(SERVER_PORT);

	// Bind 
	int socket_fd =socket.Bind();
	if (socket_fd == -1) {
		cerr << "Error en el bind: " << strerror(errno) << endl;
		exit(1);
	}

	// Listen
	int max_connections = 10;
	int error_code = socket.Listen(max_connections);
	if(error_code == -1) {
		cerr << "Error en el listen: " << strerror(errno) << endl;
		// Cerramos el socket
		socket.Close(socket_fd);
		exit(1);
	}
	thread cliente[NUM_CLIENTES];
	int i=0;
	while(i<NUM_CLIENTES){
		// Accept
		int client_fd = socket.Accept();
		if(client_fd == -1) {
			cerr << "Error en el accept: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
			exit(1);
		}
		cliente[i]=thread(&Proceso,i,socket,client_fd,ref(monumentos),ref(restaurantes));
		i++;
	}	
	for(i=0;i<NUM_CLIENTES;i++){
		cliente[i].join();
	}
}
