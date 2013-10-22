/* 
 * File:   server.h
 * Author: Cory
 *
 * Created on October 8, 2013, 2:33 PM
 */
#include "stdhf.h"
#include <stdio.h>
#include <stdlib.h>
#include "gameMechanics.h"
#include "gameAI.h"
using namespace std;

#ifndef GAMESERVER_H
#define	GAMESERVER_H

class serverEngine{
    Engine gameBoard;
    reversiAI AI_Player;
	char** boardHistory[10];
public:
    serverEngine();
	serverEngine(int difficulty,char Ai_color);
	void changeColor(char Ai_color);
	string AImove();
    string showBoard();
	char getColor();
	void updateBoard(int turnCount);
	void undo(int turnCount);
    int makeMove(char p, string m);
    string printValidMoves(char p);
    bool isTerminalState();
    string outputScores();
    void runGame();
};

#endif	/* SERVER_H */

