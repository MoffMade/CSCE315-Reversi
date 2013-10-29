/* 
 * File:   main.cpp
 * Author: Cory
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
 * 
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
		cout<<"Port num: ";
		cin>>port;
		e.CreateAnotherAI("127.0.0.1",port);
		cout<<"set level of difficulty for AI: ";
		cin>>level;
		e.setAILevel(level);
		
		bool cond = true;
		while (cond) {
			cond = e.seeAIMove();
		}
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

