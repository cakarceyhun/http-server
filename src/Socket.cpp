#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Socket.h"

struct SocketPrivateValues
{
    int socket_desc;
    int client_sock;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char client_message[2000];   
};

using namespace std;

Socket::Socket()
{
    self = shared_ptr<SocketPrivateValues>();
    
    self->socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (self->socket_desc == -1) {
	cerr << "Could not create socket\n";
	throw 1;
    }

    self->server.sin_family = AF_INET;
    self->server.sin_addr.s_addr = INADDR_ANY;
    self->server.sin_port = htons( 8888 );
	
    if( bind(self->socket_desc,(struct sockaddr *)&self->server , sizeof(self->server)) < 0) {
	cerr << "bind failed. Error\n";
	throw 1;
    }
	
    listen(self->socket_desc , 3);
}

std::string Socket::read()
{
    int c;
    int read_size;
    string buffer = "";
    
    cout << "Waiting for incoming connections...\n";
    c = sizeof(struct sockaddr_in);
	
    self->client_sock = accept(self->socket_desc, (struct sockaddr *)&self->client, (socklen_t*)&c);
    if (self->client_sock < 0) {
	cerr << "accept failed\n";
	throw 1;
    }
    cout << "Connection accepted";
	
    while( (read_size = recv(self->client_sock , self->client_message , 2000 , 0)) > 0 ) {
	string message(self->client_message, self->client_message + read_size);

	cout << message;

	buffer = buffer + message;
    }
	
    if(read_size == 0) {
	cout << "Client disconnected\n";
    } else if(read_size == -1) {
	cerr << "recv failed\n";
    }

    return buffer;
}

