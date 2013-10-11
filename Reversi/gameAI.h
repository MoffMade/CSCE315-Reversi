/* 
 * File:   gameAI.h
 * Author: Cory
 *
 * Created on October 8, 2013, 2:34 PM
 */
#include "stdhf.h"
#include "gameMechanics.h"
using namespace std;
#ifndef GAMEAI_H
#define	GAMEAI_H
class reversiAI{
    int AI_DIFFICULTY;
    char AI_COLOR;
public:
    reversiAI();
    reversiAI(int difficulty);
    reversiAI(int difficulty, char color);
    string getAIMove(Engine* board);
};
//Start off with random choice from valid moves


#endif	/* GAMEAI_H */

