#include "gameServer.h"
#include <sstream>


using namespace std;

serverEngine::serverEngine(){
    gameBoard;
    AI_Player;
	for(int i=0; i<10; i++)
		boardHistory[i];
    //will have other initialization
}
serverEngine::serverEngine(int difficulty,char Ai_color) {
	gameBoard;
	AI_Player = reversiAI(difficulty,Ai_color);
	for(int i=0; i<10; i++)
		boardHistory[i];

}
string serverEngine::showBoard(){

    char** currBoard=gameBoard.getBoardState();
	string result;
    result = "\n  _ _ _ _ _ _ _ _\n";
    for(int i=0; i<8; i++){
		stringstream stream;
		  stream<<i+1<<"|"<<currBoard[i][0]<<"|"<<currBoard[i][1]<<"|"<<currBoard[i][2]<<"|"<<currBoard[i][3]<<
                "|"<<currBoard[i][4]<<"|"<<currBoard[i][5]<<"|"<<currBoard[i][6]<<"|"<<currBoard[i][7]<<"|";
		result += stream.str() +  "\n";
    }
    result += "  a b c d e f g h ";
	//add score below the table so the server will only send 1 message
	string score = outputScores();
	result += "\n" + score;
	return result;
}
int serverEngine::makeMove(char p, string m){
    char c=tolower(m[0]);
    char r=tolower(m[1]);
    int col_choice=c-97;
    int row_choice=r-49;
    coordPair loc = {row_choice,col_choice};
    return gameBoard.makeMove(p,loc);
}
string serverEngine::printValidMoves(char p){
	stringstream stream;
    vector<string> moves=gameBoard.getValidMoves(p);
    for(int i=0; i<moves.size(); i++) {
        stream<<moves[i]<<", ";
	}
    stream<<"\n";
	return stream.str();
}
string serverEngine::outputScores(){
    int whiteScore=gameBoard.getScore(WHITE);
    int blackScore=gameBoard.getScore(BLACK);
	stringstream stream;
    stream<<"White: "<<whiteScore<<"\nBlack: "<<blackScore<<"\n";
    if (gameBoard.isTerminalState()) {
		if(whiteScore>blackScore) {
			stream<<"White wins!\n";
		}
		else if(whiteScore<blackScore) {
			stream<<"Black wins!\n";
		}
		else
			stream<<"It is a tie!\n";
	}
	return stream.str();
}
void serverEngine::undo(int turnCount) {

	gameBoard.setBoardState(boardHistory[turnCount%10]);
	
}
void serverEngine::updateBoard(int turnCount) {

	boardHistory[turnCount%10]=gameBoard.getBoardState();
	
}
char serverEngine::getColor() {

	return AI_Player.getColor();
}
void serverEngine::changeColor(char Ai_color) {
	
	AI_Player.changeColor(Ai_color);

}
string serverEngine::AImove() {
	string move;
	stringstream stream;
	if(!((gameBoard.getValidMoves(AI_Player.getColor())).empty())){
		move=AI_Player.getAIMove(&gameBoard);
		cout<<"AI MOVE "<<move<<endl;
		if(makeMove(AI_Player.getColor(), move)) {
			stream<<"AI plays at "<<move<<"\n";	
		}
	}
	else {
			stream<<"AI has no valid moves.\n";
	}
	return stream.str();
}
void serverEngine::runGame(){

}