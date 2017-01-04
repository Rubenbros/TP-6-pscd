
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Objeto.h"
#include "middleware.h"
#include "Socket.h"

using namespace std;
const int NUM_CLIENTES = 1;

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres

void Proceso(Socket socket, int client_fd,middleware& monumentos,middleware& restaurantes){
  
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
		cliente[i]=thread(&Proceso,socket,client_fd,ref(monumentos),ref(restaurantes));
		i++;
	}	
	for(i=0;i<NUM_CLIENTES;i++){
		cliente[i].join();
	}
}
