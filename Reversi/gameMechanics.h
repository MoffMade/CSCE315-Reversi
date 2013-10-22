/* 
 * File:   gameMechanics.h
 * Author: Cory
 *
 * Created on October 8, 2013, 2:35 PM
 * 
 * WHITE: O
 * BLACK: @
 * EMPTY: _
 * 
 * Board initial setup:
 * 0|_|_|_|_|_|_|_|_|
 * 1|_|_|_|_|_|_|_|_|
 * 2|_|_|_|_|_|_|_|_|
 * 3|_|_|_|O|@|_|_|_|
 * 4|_|_|_|@|O|_|_|_|
 * 5|_|_|_|_|_|_|_|_|
 * 6|_|_|_|_|_|_|_|_|
 * 7|_|_|_|_|_|_|_|_|
 *   0 1 2 3 4 5 6 7
 */
#include "stdhf.h"
#include <sstream>
using namespace std;
#ifndef GAMEMECHANICS_H
#define	GAMEMECHANICS_H

class Engine {
    char boardState[8][8];
    void flipTiles(char p, coordPair loc);
public:
    Engine();
    char** getBoardState();
	void setBoardState(char** newState);
    int makeMove(char p, coordPair loc);
    bool isValidMove(char p, coordPair loc);
    vector<string> getValidMoves(char p);
	vector<coordPair> getValidMovesLocForm(char p);
    int getScore(char p);
	bool isTerminalState();
	string showBoardState();
};

#endif	/* GAMEMECHANICS_H */

