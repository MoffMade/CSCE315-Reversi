#include "gameMechanics.h"
using namespace std;

Engine::Engine(){
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            boardState[i][j]=EMPTY;
    
    boardState[3][3] = WHITE;
    boardState[4][4] = WHITE;
    boardState[3][4] = BLACK;
    boardState[4][3] = BLACK;
}
char** Engine::getBoardState(){
    char** state = new char*[8];
    for(int r=0; r<8; r++){
        state[r]=new char[8];
        for(int c=0; c<8; c++)
            state[r][c]=boardState[r][c];
    }
    return state;
}
int Engine::makeMove(char p, coordPair loc){
    if(!isValidMove(p, loc))
        cout<<"INVALID MOVE"<<endl;
        return -1;
    if(p==WHITE){
        if(boardState[loc.row][loc.col]!=WHITE){
            boardState[loc.row][loc.col]=WHITE;
            flipTiles(WHITE, loc);
        }
        else
            return 0;
        return 1;
    }
    else if(p==BLACK){
        if(boardState[loc.row][loc.col]!=BLACK){
            boardState[loc.row][loc.col]=BLACK;
            flipTiles(BLACK, loc);
        }
        else
            return 0;
        return 1;
    }
    else
        return -1;
    }
const coordPair directions[8]={coordPair {0,-1}, coordPair {0,1}, coordPair {-1, 0}, coordPair {1,0}, coordPair {-1,-1}, coordPair {1,-1}, coordPair {-1,1}, coordPair {1,1}};
bool Engine::isValidMove(char p, coordPair loc){
    //return false if loc is non-empty
    if(boardState[loc.row][loc.col]!=EMPTY)
        return false;
    char player=p;
    char opp;
    if(player==WHITE)
        opp=BLACK;
    else
        opp=WHITE;
    //directions = {N, S, E, W, NE, NW, SE, SW}
    coordPair end_loc=loc;
    //loop for each direction
    for(int i=0; i<8; i++){
        //move one space in direction[i] and check for opponent piece
        end_loc+=directions[i];
        if(boardState[end_loc.row][end_loc.col]==opp)
            while(end_loc.row<8&&end_loc.col<8){
                //check next space, if player piece return true, if empty space found break to next direction
                //continue to next space if opponent piece
                end_loc+=directions[i];
                if(boardState[end_loc.row][end_loc.col]==player)
                    return true;
                else if(boardState[end_loc.row][end_loc.col]==EMPTY)
                    break;
            }
         //reset end_loc for next direction search
         end_loc=loc;
      }
      //return false if all 8 directions do not return true
      return false;    
}
void Engine::flipTiles(char p, coordPair loc){
    //flip all tiles between two tiles of player p in all valid directions
    char player=p;
    char opp;
    if(player==WHITE)
        opp=BLACK;
    else
        opp=WHITE;
    //directions = {N, S, E, W, NE, NW, SE, SW}
    //directions = {(0,-1),(0,1),(-1,0),(1,0),(-1,-1),(1,-1),(-1,1),(1,1)}
    coordPair end_loc=loc;
    //loop for each direction
    for(int i=0; i<8; i++){
        //move one space in direction[i] and check for opponent piece
        end_loc+=directions[i];
        //spacesChecked is a counter for how many tiles will be flipped in directions[i]
        int spacesChecked=1;
        if(boardState[end_loc.row][end_loc.col]==opp)
            while(end_loc.row<8&&end_loc.col<8){
                //check next space, 
                end_loc+=directions[i];
                ++spacesChecked;
                //if space is player, then in p|opp|...|p state
                if(boardState[end_loc.row][end_loc.col]==player){
                    for(int k=0; k<spacesChecked; k++){
                        end_loc-=directions[i];
                        boardState[end_loc.row][end_loc.col]=player;
                    }
                    break;
                }
                else if(boardState[end_loc.row][end_loc.col]==EMPTY)
                    break;
            }
         //reset end_loc for next direction search
         end_loc=loc;
      }  
}
vector<string> Engine::getValidMoves(char p){
    vector<string> validMoves;
    string move=" ";
    for(int r=0; r<8; r++)
        for(int c=0; c<8; c++)
            if(isValidMove(p,coordPair {r,c})){
                move=(char)(c+97);
                move+=(char)(r+49);
                validMoves.push_back(move);
            }
    return validMoves;
};
int Engine::getScore(char p){
    int score=0;
    for(int r=0; r<8; r++)
        for(int c=0; c<8; c++)
            if(boardState[r][c]==p)
                score++;
    return score;
}
