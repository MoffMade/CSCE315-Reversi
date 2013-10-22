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
		
	For AI-AI
	open 3 terminals
		Server term: reversiServer 12345
		Server term: reversiServer 23456
		Client term: reversiClient 127.0.0.1 AI-AI 12345 23456
		Client term: "enter" key or "q"

*/

#include <iostream>
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

	int sock, port_num, port_num2,sock_2;
	char send_message[1024], receive_message[1024];
	char send_message_2[1024], receive_message_2[1024];
	bool isAIvsAI = false;

	struct sockaddr_in server_address;
	struct sockaddr_in server_address_2;
	
	struct hostent *server;

	//check if command calls contain port number

	if (argc <3) {
	
		fprintf(stderr, "Missing Agrs client hostname port");
		exit(1);
	} else if (argc == 3){
		//get the port number
		port_num = atoi(argv[2]);
	} else if (argc == 5) {
	
	//check if the command call AI-AI, and if yes -> check the second port number
	//Format is reversiClient host AI-AI port1 port2
	//the first move will be server 2
		string mode = argv[2];
		if (mode.compare("AI-AI") == 0) {
			isAIvsAI = true;
			port_num = atoi(argv[3]);
			port_num2 = atoi(argv[4]);
		
		} else {
			fprintf(stderr, "Invalid Command");
			exit(1);
		}
	}
	
	
	
	//creating a socket
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0) {
		fprintf(stderr, "Error whille openning socket for server 1");
		exit(1);
	}
	
	//creating second socket for AI-Ai
	if (isAIvsAI) {
		sock_2 = socket(AF_INET,SOCK_STREAM, 0);
		if (sock_2 < 0) {
			fprintf(stderr, "Error whille openning socket for server 2");
			exit(1);
		}
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
	 
	int m;
	 //setting up second socket to second server if AI-AI command was entered
	if (isAIvsAI) {
	 
		//clear address structure
		bzero((char *) &server_address_2, sizeof(server_address_2));

		//setup the server address structure for binding call
		server_address_2.sin_family = AF_INET;	// server byte order
		bcopy((char *)server->h_addr, (char *)&server_address_2.sin_addr.s_addr,server->h_length);
		server_address_2.sin_port = htons(port_num2); // converting port num into network byte order
		
		if (connect(sock_2, (struct sockaddr *)&server_address_2, sizeof(server_address_2)) <0) {
			fprintf(stderr,"Errow while writing to socket for server 2");
			exit(1);
		}
		//sending the first signal to server 2 indicate AIvsAI mode
		//server 1 will behave line normal server-client
		
		m = write(sock_2,"AIvsAI",6);
	 }
	 	int n;
	
	bzero(receive_message,1024);
	n = read(sock, receive_message, 1024);
	if (n < 0) 
         fprintf(stderr,"ERROR reading from socket");
	
	if(isAIvsAI) {
		
		bzero(receive_message_2,1024);
		m = read(sock_2,receive_message_2,1024);
		if (m <0)
			fprintf(stderr,"ERROR reading from socket server 2");
	}
		 
	while (1) {
		 
	//When server game send quit message -> terminate by closing connection
	//sometime the server sends an empty message
	//this will ensure that no sending back from client if it receives invalid message from server
	if (receive_message[0] != '\0') {
		
		if (receive_message[0] != 'q') {
						
			if (isAIvsAI) {
				if (receive_message_2[0] != '\0') {
					//receiving move from server 2 WHITE
					bzero(receive_message_2,1024);
					m = read(sock_2,receive_message_2,1024);
					printf("This is a response from server 2: %s\n", receive_message_2 ); 

					//sending move to server 1 BLACK
					bzero(send_message,1024); 
					send_message[0] = toupper(receive_message_2[12]);
					send_message[1] = receive_message_2[13];
					n = write(sock,send_message,1024);
					
					//receiving move from server 1 BLACK
					bzero(receive_message,1024);
					n = read(sock,receive_message,1024);
					printf("This is a response from server 1: %s\n", receive_message ); 

					//sending move to server 2 WHITE
					bzero(send_message_2,1024);
					send_message_2[0] = toupper(receive_message[12]);
					send_message_2[1] = receive_message[13];
					m = write(sock_2,send_message_2,1024);
					
					bzero(send_message,1024);
					
					cout<<"Enter to see AIs moves or 'q' to stop connection: \n";
					if (cin.get() == 'q'){
						printf("\n*******Server is about to close. Thank you for playing*******\n");
						close(sock);
						break;
					}
				}
			}
			else {
				printf("This is a response from server: %s\n", receive_message); 
				printf("Enter move or 'q' to stop connection: \n");	
				bzero(send_message,1024); 
				fgets(send_message,1024,stdin);
				n = write(sock, send_message, strlen(send_message));
				
				bzero(receive_message,1024);
				n = read(sock, receive_message, 1024);

			}
			
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