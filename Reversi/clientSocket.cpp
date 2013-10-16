/*

	Project 2: Reversi
	CSEC 315
	Team 502-e 
	

	This is used for establishing socket connection on client side
	compile command must be: g++ clientSocket.cpp -o client -lsocket -lnsl
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
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;



int main(int argc, char *argv[]) {

	int sock, port_num;
	char send_message[1024], receive_message[1024];

	struct sockaddr_in server_address;
	struct hostent *server;

	//check if command calls contain port number

	if (argc <3) {
	
		fprintf(stderr, "Missing Agrs client hostname port");
		exit(1);
	} else {
		//get the port number
		port_num = atoi(argv[2]);
	}
	//creating a socket
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0) {
		fprintf(stderr, "Error whille openning socket");
		exit(1);
	}
	//get server
	//127.0.0.1
	server = gethostbyname(argv[1]);
	if (server == NULL){
		fprintf(stderr, "Invalid Host");
		exit(1);
	}

	//clear address structure
	bzero((char *) &server_address, sizeof(server_address));

	//setup the server address structure for binding call
	server_address.sin_family = AF_INET;	// server byte order
	bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr,server->h_length);
	server_address.sin_port = htons(port_num); // converting port num into network byte order
	if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) <0) {
		fprintf(stderr,"Errow while writing to socket");
		exit(1);
	 }
	 
	int n;
	while (1) {
	
	//reading message from server

	bzero(receive_message,1024);
	n = read(sock, receive_message, 1023);
	if (n < 0) 
         fprintf(stderr,"ERROR reading from socket");

	//When server game send quit message -> terminate by closing connection
	//sometime the server sends an empty message
	//this will ensure that no sending back from client if it receives invalid message from server
	if (receive_message[0] != '\0') {
		
		if (receive_message[0] != 'q') {
		    printf("This is a response from server: %s\n", receive_message ); 
			printf("Enter move or 'q' to stop connection: \n");
			bzero(send_message,1024); 
			fgets(send_message,1023,stdin);
			n = write(sock, send_message, strlen(send_message));
			if (send_message[0] == 'q') {
				printf("\n*******Server is about to close. Thank you for playing*******\n");
				close(sock);
				break;
			}
		} else {
			printf("\n*******Server is about to close. Thank you for playing*******\n");
			close(sock);
			break;
		}
 
	}
	}
    
	return 0;



}