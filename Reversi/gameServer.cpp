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
bool serverEngine::isTerminalState(){
    vector<string> whiteMoves=gameBoard.getValidMoves(WHITE);
    vector<string> blackMoves=gameBoard.getValidMoves(BLACK);
    if(whiteMoves.empty()&&blackMoves.empty())
        return true;
    else
        return false;
};
string serverEngine::outputScores(){
    int whiteScore=gameBoard.getScore(WHITE);
    int blackScore=gameBoard.getScore(BLACK);
	stringstream stream;
    stream<<"White: "<<whiteScore<<"\nBlack: "<<blackScore<<"\n";
    if (isTerminalState()) {
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
string serverEngine::AImove() {
	string move;
	stringstream stream;
	if(!((gameBoard.getValidMoves(BLACK)).empty())){
		move=AI_Player.getAIMove(&gameBoard);
		if(makeMove(BLACK, move)) {
			stream<<"AI plays at "<<move<<"\n";	
		}
	}
	else {
			stream<<"AI has no valid moves.\n";
	}
	return stream.str();
}
void serverEngine::runGame(){
	
	/*
	This code will be separated into serverSocket and clientSocket
	
    string move;
    bool whiteTurn=true;
    showBoard();
	int turnCount=0;
    while(!isTerminalState()){
        if(whiteTurn){
			if(!((gameBoard.getValidMoves(WHITE)).empty())){
				cout<<"Turn "<<turnCount<<"- Please enter move for WHITE player:: ";
				cin>>move;
				if(move=="help"){
					cout<<"You can place a tile in spaces ";
					printValidMoves(WHITE);
					}
				else if(move=="exit")
					break;
				else if(move=="undo"){
					--turnCount;
					gameBoard.setBoardState(boardHistory[turnCount%10]);
					cout<<"Reset to turn "<<turnCount<<endl;
					}
				else if(makeMove(WHITE, move)){
					whiteTurn=false;
					turnCount++;
					}
				}
			
			else{
				cout<<"WHITE has no valid moves."<<endl;
				whiteTurn=false;
			}
		}
        else{
			if(!((gameBoard.getValidMoves(BLACK)).empty())){
				move=AI_Player.getAIMove(&gameBoard);
				cout<<"BLACK plays at "<<move<<endl;
				if(makeMove(BLACK, move))
					whiteTurn=true;
			}
			else{
				cout<<"BLACK has no valid moves."<<endl;
				whiteTurn=true;
			}
			}
		boardHistory[turnCount%10]=gameBoard.getBoardState();
        showBoard();
    }
    outputScores();
	*/
}