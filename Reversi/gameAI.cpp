#include "gameAI.h"
using namespace std;

reversiAI::reversiAI(){
    AI_DIFFICULTY=EASY;
    AI_COLOR=BLACK;
}
char reversiAI::getColor() {
	return AI_COLOR;
}
reversiAI::reversiAI(int difficulty){
    AI_DIFFICULTY=difficulty;
    AI_COLOR=BLACK;
}
reversiAI::reversiAI(int difficulty, char color){
    AI_DIFFICULTY=difficulty;
    AI_COLOR=color;
}
void reversiAI::changeColor(char color) {
	AI_COLOR =color;
}
string reversiAI::getAIMove(Engine* board){
    vector<string> moveList=board->getValidMoves(AI_COLOR);
    int randomMoveChoice=(int)((double)(moveList.size()*(rand()/(RAND_MAX + 1.0))));
    return moveList[randomMoveChoice];
}