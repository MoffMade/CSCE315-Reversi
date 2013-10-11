/* 
 * File:   server.h
 * Author: Cory
 *
 * Created on October 8, 2013, 2:33 PM
 */
#include "stdhf.h"
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
    void showBoard();
    int makeMove(char p, string m);
    void printValidMoves(char p);
    bool isTerminalState();
    void outputScores();
    void runGame();
};

#endif	/* SERVER_H */

