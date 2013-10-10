#include "gameServer.h"
using namespace std;

serverEngine::serverEngine(){
    initBoard();
    //will have other initialization
}
void serverEngine::initBoard(){
    gameBoard;
}
void serverEngine::showBoard(){
    char** currBoard=gameBoard.getBoardState();
    cout<<"  _ _ _ _ _ _ _ _"<<endl;
    for(int i=0; i<8; i++){
        cout<<i+1<<"|"<<currBoard[i][0]<<"|"<<currBoard[i][1]<<"|"<<currBoard[i][2]<<"|"<<currBoard[i][3]<<
                "|"<<currBoard[i][4]<<"|"<<currBoard[i][5]<<"|"<<currBoard[i][6]<<"|"<<currBoard[i][7]<<"|"<<endl;
    }
    cout<<"  a b c d e f g h "<<endl;
}
void serverEngine::makeMove(char p, string m){
    if(m.length()==2){
        cout<<m[0]<<" "<<m[1]<<endl;
        char col=m[0];
        int c=-1;
        int r=atoi((m.substr(1,1)).c_str())-1;
        switch(col){
            case 'a':
                c=0;
                break;
            case 'b':
                c=1;
                break;
            case 'c':
                c=2;
                break;
            case 'd':
                c=3;
                break;
            case 'e':
                c=4;
                break;
            case 'f':
                c=5;
                break;
            case 'g':
                c=6;
                break;
            case 'h':
                c=7;
                break;
            default:
                c=-1;
                break;
        }
        cout<<r<<" "<<c<<endl;
        gameBoard.makeMove(p,coordPair {r,c});
    }
    else
        cout<<"INVALID MOVE"<<endl;
}
void serverEngine::printValidMoves(char p){
    vector<string> moves=gameBoard.getValidMoves(p);
    for(int i=0; i<moves.size(); i++)
        cout<<moves[i]<<", ";
    cout<<endl;
}
bool serverEngine::isTerminalState(){
    vector<string> whiteMoves=gameBoard.getValidMoves(WHITE);
    vector<string> blackMoves=gameBoard.getValidMoves(BLACK);
    if(whiteMoves.empty()&&blackMoves.empty())
        return true;
    else
        return false;
};
void serverEngine::outputScores(){
    int whiteScore=gameBoard.getScore(WHITE);
    int blackScore=gameBoard.getScore(BLACK);
    cout<<"White: "<<whiteScore<<endl<<"Black: "<<blackScore<<endl;
    if(whiteScore>blackScore)
        cout<<"White wins!"<<endl;
    else if(whiteScore<blackScore)
        cout<<"Black wins!"<<endl;
    else
        cout<<"It is a tie!"<<endl;
}
void serverEngine::runGame(){
    string move=" ";
    bool whiteTurn=true;
    showBoard();
    while(move!="exit"){
        move=" ";
        if(whiteTurn){
            printValidMoves(WHITE);
            cout<<"Please enter move for WHITE player:: ";
            cin>>move;
            makeMove(WHITE, move);
            whiteTurn=false;
            }
        else{
            printValidMoves(BLACK);
            cout<<"Please enter move for BLACK player:: ";
            cin>>move;
            makeMove(BLACK, move);
            whiteTurn=true;
            }
        showBoard();
        
        if(isTerminalState())
            break;
    }
    outputScores();
}