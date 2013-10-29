#include "gameAI.h"
using namespace std;


reversiAI::reversiAI(){
    AI_DIFFICULTY=EASY;
    AI_COLOR=BLACK;
	enemy_color = WHITE;
}
reversiAI::reversiAI(int difficulty){
    AI_DIFFICULTY=difficulty;
    AI_COLOR=BLACK;
	enemy_color = WHITE;
	depth = 0;
	if (difficulty == 1)
		MAX_DEPTH = 1;
	else if (difficulty == 2)
		MAX_DEPTH = 3;
	for (int i = 0; i < 5; i++)
		board_history[i];
	min_completed = false;
	max_completed = false;
	//two_finished_complex = false;
	//max_hit_end_of_loop = false;
}
reversiAI::reversiAI(int difficulty, char color){
    AI_DIFFICULTY=difficulty;
    AI_COLOR=color;
	depth = 0;
	if (AI_COLOR == BLACK)
		enemy_color = WHITE;
	else
		enemy_color = BLACK;
	if (difficulty == 1)
		MAX_DEPTH = 1;
	else if (difficulty == 2)
		MAX_DEPTH = 3;
	for (int i = 0; i < 5; i++)
		board_history[i];
	min_completed = false;
	max_completed = false;
	//two_finished_complex = false; 
	//max_hit_end_of_loop = false;
}
string reversiAI::getAIMove(Engine* board){
	if (AI_DIFFICULTY == 0)
	{
		vector<string> moveList=board->getValidMoves(AI_COLOR);
		int randomMoveChoice=(int)((double)(moveList.size()*(rand()/(RAND_MAX + 1.0))));
		return moveList[randomMoveChoice];
	}
	else if (AI_DIFFICULTY == 1 || AI_DIFFICULTY == 2)
	{
		//cout << "trying to find best_move" << endl;
		game_engine.setBoardState((board->getBoardState()));
		coordPair best_move = MinMax();
		//printMovesOfMWS();
		return convertCoordPairToString(best_move);
	}
	else 
		return "error: difficulty was never selected for AI";
}

/*vector<int> reversiAI::eval(Engine *board)
{
	vector<int> modded_score; //modded from normal score because edge tiles and tiles on just inside of edge will have slightly different values than normal
	modded_score.resize(2);
	int white_score = board->getScore(WHITE);
	int black_score = board->getScore(BLACK);
	modded_score.push_back(white_score);
	modded_score.push_back(black_score);
	return modded_score; 
}*/

void reversiAI::reset_AI_thought_back_one_move()
{
	depth -= 1; //sets depth_count back to the one prior to mini's execution.
	if (branch_of_moves.empty() == false)
		branch_of_moves.pop_back();
	if (branch_of_scores.empty() == false)
	{
		branch_of_scores.pop_back();
		branch_of_scores.pop_back();
	}
	returnToPreviousBoardState(depth);
}

coordPair reversiAI::eval(char color)
{
	/*
	used in the cut-off state of the MIN-MAX algorithm below. it will take the 
	vector of coordPairs (a whole branch of moves) and then return the value of
	that branch of moves based on overall gain of original player
	*/
	
	char e_color;
	coordPair move = branch_of_moves[0]; //initial move that should lead to resulting score after X depth
	if (color == WHITE)
		e_color = BLACK;
	else
		e_color = WHITE;
	int AI_score = 0;
	int enemy_score = 0;
	int AI_score_change = 0;
	int enemy_score_change = 0;
	int result = 0;
	vector<int> enemy_score_changes;
	vector<int> AI_score_changes;
	//cout << "Branch size: " << branch_of_scores.size() << endl;
	for (int i = 0; i < branch_of_scores.size(); i++)
	{
		//calculates overall gain for AI and enemy
		if ((i % 2) == 0) //represents even indices, and thus Min scores, or enemy_scores.
		{
			if (i != 0) //if it's not the first value of enemy_scores
			{
				enemy_score_change = branch_of_scores[i] - branch_of_scores[i-2];
				enemy_score_changes.push_back(enemy_score_change);
			}
			//cout << "enemy score change: " << enemy_score_change << endl;
		}
		else //if its an odd indices, add it to AI score.
		{
			if (i != 1)
			{
				AI_score_change = branch_of_scores[i] - branch_of_scores[i-2];
				AI_score_changes.push_back(AI_score_change);
			}
			//cout << "AI score change: " << AI_score_change << endl;
		}
	}
	if (AI_score_changes.size() == 1)
	{
		AI_score = AI_score_changes[0];
		enemy_score = enemy_score_changes[0];
	}
	else
		for (int i = 0; i < AI_score_changes.size(); i++)
		{
			AI_score += AI_score_changes[i];
			enemy_score += enemy_score_changes[i];
			//cout << "AI_score net gain: " << AI_score << endl;
			//cout << "Enemy_score net gain: " << enemy_score << endl;
		}
	//calculates net gain for AI and puts it in result
	result = AI_score - enemy_score;

	moveWithScore mws = {result, move};
	move_with_score.push_back(mws);
	//cout << "Result: " << result << endl;
	reset_AI_thought_back_one_move();
	//cout << "move: " << move.row << move.col << endl;
	return move;
}

coordPair reversiAI::MinMax()
{
	depth = 0; //makes sure depth always starts at 0, after initialization of AI
	move_with_score.clear(); //makes sure the initial moves and associated scores vector is empty
	updateHistory(0);
	branch_of_scores.clear();
	branch_of_moves.clear();
	branch_of_scores.push_back(game_engine.getScore(enemy_color));
	branch_of_scores.push_back(game_engine.getScore(AI_COLOR));
	min_completed = false;
	max_completed = false;
	int alpha = -65;
	int beta = 65; //values of +- 65 are used because net gain for any move can never exceed 
	//either of those values as there are only 64 squares on the board to possibly control.
	//two_finished_complex = false;
	return Maxi(alpha, beta);
}

coordPair reversiAI::Maxi(int alpha, int beta)
{
	int value = -65;
	coordPair best_move = {0,0};
	//Engine temporary_board;
	//cout << "about to make temp board in Maxi" << endl;
	//temporary_board.setBoardState(board.getBoardState());
	//cout << "made temporary board in Maxi" << endl;
	if (game_engine.isTerminalState() || depth == MAX_DEPTH)
	{
		//cout << "returning eval: " << endl;
		return eval(AI_COLOR);
	}
	else
	{
		vector<coordPair> moves = game_engine.getValidMovesLocForm(AI_COLOR);
		coordPair move = {0,0};
		for (int i = 0; i < moves.size(); i++)
		{
			cout << min_completed << " " << max_completed << endl;
			if (min_completed == true && max_completed == true)
			{
				//resets back two moves because depth jumps back up two moves when
				//the case of both max/min or min/max are finished at the same time
				reset_AI_thought_back_one_move();
				reset_AI_thought_back_one_move();
				min_completed = false; //resets for next branch
				max_completed = false; 
			}
			if (min_completed == true)
			{
				reset_AI_thought_back_one_move();
				min_completed = false; //resets for next branch
			}
			//cout << "depth_ count: before loop: " << depth << endl;
			//cout << "# of available moves Maxi: " << moves.size() << endl;
			//cout << "Moves[i]: " << moves[i].row << moves[i].col << endl;
			game_engine.makeMove(AI_COLOR, moves[i]); 
			
			//cout << "saved board state to previous" << endl;
			//cout << "made move" << endl;
			branch_of_moves.push_back(moves[i]); //used to keep track of entire branch of one set of moves
			branch_of_scores.push_back(game_engine.getScore(enemy_color)); //keeps track of enemy scores in branch (all are even numbered)
			branch_of_scores.push_back(game_engine.getScore(AI_COLOR)); //keeps track of the AI scores in the branch (all are odd numbered)
			depth += 1;
			updateHistory(depth);
			//cout << "Maxi depth: " << depth << endl;
			//cout << "Maxi i: " << i << endl;
			move = Mini(alpha, beta); //crucial mutual recursion to get a whole branch of tree
			//cout << "Max size of move_with_score: " << move_with_score.size() << endl;
			//cout << "Max Move_with_score i score: " << move_with_score[i].score << endl;
			//cout << "Max Current Value: " << value << endl;
			for (int j = 0; j < move_with_score.size(); j++) 
				if (move_with_score[j].score >= value)
				{
					//cout << "Max Move_with_score j score: " << move_with_score[j].score << endl;
					best_move.row = move_with_score[j].move.row;
					best_move.col = move_with_score[j].move.col;
					//cout << "Max best_move RC: " << best_move.row << best_move.col << endl;
					value = move_with_score[j].score;
					alpha = value;
				}
			//cout << "Alpha: " << alpha << endl;
			//cout << "Beta: " << beta << endl;
			/*if (beta <= alpha)
			{
				max_completed = true;
				//cout << "Beta is less or equal to Alpha" << endl;
				//cout << "max is complete: TRUE" << endl; 
				return best_move;
			}*/
		}
		max_completed = true;
		//cout << "Max complete?: " << max_completed << endl;
		return best_move;
	}
}

coordPair reversiAI::Mini(int alpha, int beta)
{
	//cout << "got to mini" << endl;
	int value = -65;
	coordPair best_move = {0,0};
	//Engine temp_board;
	//cout << "about to make temp board in Mini" << endl;
	//temp_board.setBoardState(board.getBoardState());
	//cout << "made temporary board in Mini" << endl;
	if (game_engine.isTerminalState() || depth == MAX_DEPTH)
		return eval(enemy_color);
	else
	{
		//cout << "got to else statement Mini" << endl;
		vector<coordPair> moves = game_engine.getValidMovesLocForm(enemy_color);
		coordPair move = {0,0};
		//cout << "made it after moves list is done in Mini" << endl;
		for (int i = 0; i < moves.size(); i++)
		{
			if (min_completed == true && max_completed == true)
			{
				//resets back two moves because depth jumps back up two moves when
				//the case of both max/min or min/max are finished at the same time
				reset_AI_thought_back_one_move();
				reset_AI_thought_back_one_move();
				min_completed = false; //resets for next branch
				max_completed = false; 
			}
			if (max_completed == true)
			{
				reset_AI_thought_back_one_move();
				max_completed = false; //resets for next branch
			}
			//cout << "# of available moves Mini: " << moves.size() << endl;
			//cout << "Moves[i]: " << moves[i].row << moves[i].col << endl;
			game_engine.makeMove(enemy_color, moves[i]);
			branch_of_moves.push_back(moves[i]); //used to keep track of entire branch of one set of moves
			branch_of_scores.push_back(game_engine.getScore(enemy_color)); //keeps track of enemy scores in branch (all are even numbered)
			branch_of_scores.push_back(game_engine.getScore(AI_COLOR)); //keeps track of the AI scores in the branch (all are odd numbered)
			depth += 1;
			updateHistory(depth);
			//cout << "Mini depth: " << depth << endl;
			//cout << "Mini i: " << i << endl;
			move = Maxi(alpha, beta); //crucial mutual recursion to get a whole branch of tree
			//cout << "Min size of move_with_score: " << move_with_score.size() << endl;
			//cout << "Min Current Value: " << value << endl;
			for (int j = 0; j < move_with_score.size(); j++) 
				if (move_with_score[j].score >= value)
				{
					//cout << "Min Move_with_score j score: " << move_with_score[j].score << endl;
					best_move.row = move_with_score[j].move.row;
					best_move.col = move_with_score[j].move.col;
					//cout << "Min best_move RC: " << best_move.row << best_move.col << endl;
					value = move_with_score[j].score;
					beta = value;
				} 
			//if (beta < value)
				//beta = value;
			//cout << "Alpha: " << alpha << endl;
			//cout << "Beta: " << beta << endl;
			/*if (beta <= alpha)
			{
				min_completed = true;
				//cout << "Beta is less or equal to Alpha" << endl;
				//cout << "min is complete: TRUE" << endl; 
				return best_move;
			}*/
		}
		//cout << best_move.col << best_move.row << endl;
		min_completed = true; //means that recursion has been completed
		//cout << "Min complete?: " << min_completed << endl;
		return best_move;
	}
}

string reversiAI::convertCoordPairToString(coordPair best_move)
{
	string move = " ";
	move = (char)(best_move.col + 97);
	move += (char)(best_move.row + 49);
	return move;
}

void reversiAI::printMovesOfMWS()
{
	for (int i = 0; i < move_with_score.size(); i++)
	{
		cout << "Move RC: " << move_with_score[i].move.row << move_with_score[i].move.col << endl;
		cout << "Associated Move Score: " << move_with_score[i].score << endl;
	}
}

void reversiAI::returnToPreviousBoardState(int depth)
{
	game_engine.setBoardState(board_history[depth]);
}

void reversiAI::updateHistory(int depth)
{
	board_history[depth] = game_engine.getBoardState();
}