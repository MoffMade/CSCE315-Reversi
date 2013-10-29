/* 
 * File:   gameAI.h
 * Author: Cory
 *
 * Created on October 8, 2013, 2:34 PM
 */
//modded gameAI
#include "stdhf.h"
#include "gameMechanics.h"
using namespace std;
#ifndef GAMEAI_H
#define	GAMEAI_H
class reversiAI{
    int AI_DIFFICULTY;
	int MAX_DEPTH;
	int depth;
    char AI_COLOR;
	char enemy_color;
	char** board_history[5];
	Engine game_engine;
	bool min_completed, max_completed;
	//bool max_hit_end_of_loop;
	vector<coordPair> branch_of_moves;
	vector<moveWithScore> move_with_score;
	vector<int> branch_of_scores; //keeps track of each of the scores for a branch
	
public:
    reversiAI();
    reversiAI(int difficulty);
    reversiAI(int difficulty, char color);
    string getAIMove(Engine* board);
	//vector<int> eval(Engine *board);
	void reset_AI_thought_back_one_move();
	coordPair eval(char color);
	coordPair MinMax();
	coordPair Maxi(int alpha, int beta);
	coordPair Mini(int alpha, int beta);
	string convertCoordPairToString(coordPair best_move);
	void printMovesOfMWS();
	void returnToPreviousBoardState(int depth);
	void updateHistory(int depth);
};
//Start off with random choice from valid moves


#endif	/* GAMEAI_H */

