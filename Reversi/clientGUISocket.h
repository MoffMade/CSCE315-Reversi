/* 
 * File:   clientGUISocket.h
 * Author: Chuong Trinh
 *
 * Created on October 26, 2013, 1:19 PM
 */
 
#include "stdhf.h"
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
#ifndef CLIENTGUISOCKET_H
#define	CLIENTGUISOCKET_H

class ClientGUISocket {

private:
	struct hostent *server;
	int sock, port_num1, port_num2, m, n,sock_2;
	char send_message[1024], receive_message[1024];
	char send_message_2[1024], receive_message_2[1024];
	struct sockaddr_in server_address;
	struct sockaddr_in server_address_2;
public:
	ClientGUISocket();
	ClientGUISocket(string address,int _port_num);
	void CreateAnotherAI(string address,int _port_num2);
	void setAILevel(string leve);
	bool seeAIMove();
	void setPlayerLevel(string level);
	
	string setPlayerMode(string mode); //return 'OK' message
	string makePlayerMove(string move); //return whole board + info
	void showBoard(string message);

};
#endif	

