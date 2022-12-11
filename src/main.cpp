#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#include <iostream>

using namespace std;

int main()
{
    int socket_desc , client_sock ,c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
	
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) {
	cout << "Could not create socket\n";
    }
    cout << "Socket created\n";
	
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
	
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
	cerr << "bind failed. Error\n";
	return 1;
    }
	
    listen(socket_desc , 3);
	
    cout << "Waiting for incoming connections...\n";
    c = sizeof(struct sockaddr_in);
	
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0) {
	cerr << "accept failed\n";
	return 1;
    }
    cout << "Connection accepted";
	
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 ) {
	write(client_sock , client_message , strlen(client_message));
    }
	
    if(read_size == 0) {
	cout << "Client disconnected\n";
    } else if(read_size == -1) {
	cerr << "recv failed\n";
    }
	
    return 0;
}
