/* 
 * File:   clientGUISocket.cpp
 * Author: Chuong Trinh
 *
 * Created on October 26, 2013, 1:19 PM
 */
 
 #include "clientGUISocket.h"
 using namespace std;
 
 
 ClientGUISocket::ClientGUISocket() {
 }
 //For Human-AI
 ClientGUISocket::ClientGUISocket(string address, int _port_num) {
	
	port_num1 = _port_num;
 	sock = socket(AF_INET, SOCK_STREAM, 0);
	server = gethostbyname(address.c_str());
	if (server == NULL){
		fprintf(stderr, "Invalid Host");
		exit(1);
	}
	
	//clear address structure
	bzero((char *) &server_address, sizeof(server_address));

	//setup the server address structure for binding call
	server_address.sin_family = AF_INET;	// server byte order
	bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr,server->h_length);
	server_address.sin_port = htons(port_num1); // converting port num into network byte order
	
	if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) <0) {
		fprintf(stderr,"Errow while writing to socket");
		exit(1);
	 }

 }
//this is for AI-AI
void ClientGUISocket::CreateAnotherAI(string address,int _port_num2) {

	port_num2 = _port_num2;
	 
	sock_2 = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char *) &server_address_2, sizeof(server_address_2));

	//setup the server address structure for binding call
	server_address_2.sin_family = AF_INET;	// server byte order
	bcopy((char *)server->h_addr, (char *)&server_address_2.sin_addr.s_addr,server->h_length);
	server_address_2.sin_port = htons(port_num2); // converting port num into network byte order

	if (connect(sock_2, (struct sockaddr *)&server_address_2, sizeof(server_address_2)) <0) {
		fprintf(stderr,"Errow while writing to socket for server 2");
		exit(1);
	}

}
 
void ClientGUISocket::showBoard(string message) {
	cout<<receive_message<<endl;
 }
 
 void ClientGUISocket::setPlayerLevel(string level) {
	bzero(send_message,1024);
	memcpy(send_message,level.c_str(),level.size());
	n = write(sock, send_message, strlen(send_message));
	//receiving the init board state after setting level
	bzero(receive_message,1024);
	n = read(sock, receive_message, 1024);
	showBoard(receive_message);
 }
 
  void ClientGUISocket::setAILevel(string level) {

	bzero(send_message_2,1024);
	memcpy(send_message_2,level.c_str(),level.size());
	n = write(sock_2, send_message_2, strlen(send_message_2));
	//receiving the init board state after setting level
	bzero(receive_message_2,1024);
	n = read(sock_2, receive_message_2, 1024);
	showBoard(receive_message_2);
 }
 
 string ClientGUISocket::setPlayerMode(string mode) {
	bzero(send_message,1024);
	memcpy(send_message,mode.c_str(),mode.size());
	n = write(sock, send_message, strlen(send_message));
	
	//receiving the init board state after setting level
	bzero(receive_message,1024);
	n = read(sock, receive_message, 1024);
	
	//note the message here is 'OK'
	showBoard(receive_message);
	return receive_message;
 }
 bool ClientGUISocket::seeAIMove() {
	//receiving move from server 2 WHITE
	bzero(receive_message_2,1024);
	m = read(sock_2,receive_message_2,1024);
	printf("This is a response from server 2: %s\n", receive_message_2 ); 
	showBoard(receive_message_2);
	
	//sending move to server 1 BLACK
	bzero(send_message,1024); 
	send_message[0] = toupper(receive_message_2[12]);
	send_message[1] = receive_message_2[13];
	n = write(sock,send_message,1024);
	
	//receiving move from server 1 BLACK
	bzero(receive_message,1024);
	n = read(sock,receive_message,1024);
	printf("This is a response from server 1: %s\n", receive_message ); 
	showBoard(receive_message);
	
	
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
		close(sock_2);
		return false;
	}
	return true;
 }
 string ClientGUISocket::makePlayerMove(string move) {
  	bzero(send_message,1024);
	memcpy(send_message,move.c_str(),move.size());
	n = write(sock, send_message, strlen(send_message));
	bool cond = false;
		bzero(receive_message,1024);
		n = read(sock, receive_message, 1024);
		if (receive_message[0] == 'q' || send_message[0] == 'q') {
			cout<<"\n*******Server is about to close. Thank you for playing*******"<<endl;
			close(sock);
		}
		showBoard(receive_message);
		return receive_message;

}
