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
void Engine::setBoardState(char** newState){
	for(int r=0; r<8; r++){
        for(int c=0; c<8; c++)
            boardState[r][c]=newState[r][c];
    }
};
int Engine::makeMove(char p, coordPair loc){
    if(!isValidMove(p, loc)){
        cout<<"INVALID MOVE"<<endl;
        return 0;
        }
    if(p==WHITE){
        boardState[loc.row][loc.col]=WHITE;
        flipTiles(WHITE, loc);
        return 1;
    }
    else if(p==BLACK){
        boardState[loc.row][loc.col]=BLACK;
        flipTiles(BLACK, loc);
        return 1;
    }
    else
        return 0;
}

bool Engine::isValidMove(char p, coordPair loc){
    //return false if loc is non-empty
    if(boardState[loc.row][loc.col]!=EMPTY){
        return false;
    }
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
        if(end_loc.row>=0&&end_loc.col>=0&&end_loc.row<8&&end_loc.col<8)
            if(boardState[end_loc.row][end_loc.col]==opp)
                while(end_loc.row>=0&&end_loc.col>=0&&end_loc.row<8&&end_loc.col<8){
                    //check next space, if player piece return true, if empty space found break to next direction
                    //continue to next space if opponent piece
                    end_loc+=directions[i];
					if(end_loc.row>=0&&end_loc.col>=0&&end_loc.row<8&&end_loc.col<8){
						if(boardState[end_loc.row][end_loc.col]==player){
							return true;
						}
						else if(boardState[end_loc.row][end_loc.col]==EMPTY)
							break;
					}
					else 
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
        if(end_loc.row>=0&&end_loc.col>=0&&end_loc.row<8&&end_loc.col<8)
            if(boardState[end_loc.row][end_loc.col]==opp)
                while(end_loc.row<8&&end_loc.col<8){
                    //check next space, 
                    end_loc+=directions[i];
                    ++spacesChecked;
                    //if space is player, then in p|opp|...|p state
					if(end_loc.row>=0&&end_loc.col>=0&&end_loc.row<8&&end_loc.col<8){
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
					else
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
        for(int c=0; c<8; c++){
            coordPair testLocation = {r,c};
            if(isValidMove(p,testLocation)){
                move=(char)(c+97);
                move+=(char)(r+49);
                validMoves.push_back(move);
            }
        }
    return validMoves;
};

vector<coordPair> Engine::getValidMovesLocForm(char p)
{
	vector<string> valid_moves = getValidMoves(p);
	vector<coordPair> loc_moves;
	for (int i = 0; i < valid_moves.size(); i++)
	{
		cout << "valid_moves: " << valid_moves[i][0] << valid_moves[i][1] << endl;
		int r = (int)(valid_moves[i][1])-49;
		int c = (int)(valid_moves[i][0])-97;
		cout << "r: " << r << " c: " << c << endl;
		coordPair location = {r,c};
		loc_moves.push_back(location);
	}
	return loc_moves;
};

int Engine::getScore(char p){
    int score=0;
    for(int r=0; r<8; r++)
        for(int c=0; c<8; c++)
            if(boardState[r][c]==p)
                score++;
    return score;
}

bool Engine::isTerminalState()
{
    vector<string> whiteMoves=getValidMoves(WHITE);
    vector<string> blackMoves=getValidMoves(BLACK);
    if(whiteMoves.empty()&&blackMoves.empty())
        return true;
    else
        return false;
}

string Engine::showBoardState(){

    char** currBoard=this->getBoardState();
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
	//string score = outputScores();
	//result += "\n" + score;
	return result;
}