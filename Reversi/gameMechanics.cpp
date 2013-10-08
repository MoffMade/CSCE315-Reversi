#include "gameMechanics.h"
using namespace std;
Board::Board(){
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            boardState[i][j]='_';
    
    boardState[3][3] = WHITE;
    boardState[4][4] = WHITE;
    boardState[3][4] = BLACK;
    boardState[4][3] = BLACK;
}
char** Board::getBoardState(){
    char** state = new char*[8];
    for(int r=0; r<8; r++){
        state[r]=new char[8];
        for(int c=0; c<8; c++)
            state[r][c]=boardState[r][c];
    }
    return state;
}
int Board::makeMove(){
        
    }
