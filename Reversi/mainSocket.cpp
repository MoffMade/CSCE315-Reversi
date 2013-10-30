/* 
 * File:   main.cpp
 * Author: Chuong trinh
 *
 * Created on October 8, 2013, 2:33 PM
 */

#include "stdhf.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <strings.h>
#include "clientGUISocket.h"

using namespace std; 
/*

		The calling command from terminal
		reversiServer <port_num_1>
		reversiClient <port_num_1>
		
		if user pick AI-AI
		
		reversiServer <port_num_2> (from the third terminal)
		program will ask user for only port_num_2
		
		Level for Difficulty: HARD, EASY, MEDIUM
		
 
		Instruction for AI-AI
		After type AI-AI in the command
		Specify level difficult for Server 1
		Type port num for Server 2
		Specify level difficult for Server 2
		
		Start -> Initialize Server 1 
			  -> Choose HUMAN or AI-AI:
			  setPlayerMode() -> setPlayerLevel() -> makePlayerMove()
			 *HUMAN -> level -> Move
			 
			 setPlayerLevel() -> e.CreateAnotherAI() -> setAILevel() -> seeAIMove()
			 *AI-AI -> level for 1 -> port num for Server 2 -> level for 2 -> seeAIMove()
					Server 1 will play first, server 2 play second.
			
			*sendingQuit() only for AI-AI since for HUMAN makePlayerMove will handle it
			
			the return string for seeAIMove will be exactly like the output if tested in this main
			
			
			seeAIMove() return string value:
				"Server 1 play at:**"
				"Server 2 play at:**"
				"..(board) .."
			
			*NOTE: ALL THE MOVE values WILL BE AT POSITION 12 and 13 for HUMAN
		needed to follow this order
		
 
 */
int main(int argc, char** argv) {
	ClientGUISocket e; 
	e = ClientGUISocket("127.0.0.1",atoi(argv[1]));
	string move,level,mode;
	bool invalid = true;
	do {
	cout<<"Pick the mode HUMAN-AI or AI-AI: ";
	cin>>mode;
	if (mode.compare("HUMAN-AI") ==0 || mode.compare("AI-AI") == 0)
		invalid = false;
	} while (invalid);
	
	string k;
	k = e.setPlayerMode(mode);

	cout<<"set level of difficulty: ";
	cin>>level;
	e.setPlayerLevel(level);
	
	if (mode.compare("AI-AI") ==0 ) {
		int port;
		cout<<"Input the port number for second AI: ";
		cin>>port;
		e.CreateAnotherAI("127.0.0.1",port);
		cout<<"set level of difficulty for second AI: ";
		cin>>level;
		e.setAILevel(level);
		while (1) {
		cout<<"\nEnter to see a move or quit to quit:";
			if (cin.get() == 'q'){
				cout<<"\n*******Server is about to close. Thank you for playing*******\n";
				break;
			} else {
				k = e.seeAIMove();
			}
		}
		e.sendingQuit();
		
		
	} else {
	
		while (1) {
		cout<<"\nMake the move:";
		cin>>move;

		k = e.makePlayerMove(move);
		if (move.compare("quit") == 0) {
			break;
		}
		}
	}
    return 0;
}

