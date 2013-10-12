/*

	Project 2: Reversi
	CSEC 315
	Team 502-e 
	

	This is used for establishing socket connection on server side
	compile command must be: g++ serverSocket.cpp -o server -lsocket -lnsl
	wont be compiled if missing lsocket and lnsl
	This was only tested and compiled on CS tamu UNIX server
	from now:
	open 2 terminals
		Server term: server 12345
		Client term: client 127.0.0.1 12345
		Client term: input message
		... both will get responses

*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {

	int sock, newsock, port_num;
	char send_message[1024], receive_message[1024];
	socklen_t clientlen;
	struct sockaddr_in server_address, client_address;

	//check if command calls contain port number

	if (argc <2) {
	
		fprintf(stderr, "Missing Port Number");
		exit(1);
	} else {
		
		//get the port number
		port_num = atoi(argv[1]);
	}
	//creating a socket 
	//1st para = domain
	//2nd = type
	//3rd = protocol

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0) {
		fprintf(stderr, "Error whille openning socket");
		exit(1);
	}

	//clear address structure
	bzero((char *) &server_address, sizeof(server_address));

	//setup the server address structure for binding call
	
	server_address.sin_family = AF_INET;	// server byte order
	server_address.sin_addr.s_addr = INADDR_ANY; //filled with current host's IP usually 127.0.0.1
	server_address.sin_port = htons(port_num); // converting port num into network byte order

    	// This bind() call will bind  the socket to the current IP address on port, port_num
     	if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)  {
		
		 fprintf(stderr, "Error while binding");
		 exit(1);
	 }

	 // listen() dectect the incoming connections
	 if (listen(sock,5) < 0 ) {
		
		fprintf(stderr, "Error while listening");
		exit(1);

	 }

	 clientlen = sizeof(client_address);

	 //accepting connection
	 //the accept return a new socket file descriptor
	 // in order to reuse the original socket file for accepting new connections
	 // using another socket file newsock to communicate with connected client
	 newsock = accept(sock, (struct sockaddr *) &client_address, &clientlen);

	 if (newsock < 0)
		fprintf(stderr,"Error while accepting");
	
	 printf("server: got connection from %s port %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

	 //testing sending mess
	 //this will send to the client
	 send(newsock, "Hello ,world\n", 15,0);

	 bzero(receive_message,1024);

	 int n;
	 n = read(newsock,receive_message,1024);
	 if (n <0) {
		fprintf(stderr,"Error while reading from socket");
	 }

	 //the message sent by client
	 printf("Here is the message: %s\n",receive_message);


	 close(newsock);
	 close(sock);
	 return 0;
	 



}





