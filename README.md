CSCE315-Reversi
===============

Repo for the source code used for the CSCE315 Project 2 - Online Reversi

Product Backlog 
Sprint 1:
	Game Engine/Mechanics
		Represent the board and current state of tiles
			showBoard();
		Operator Legality
			bool isValidMove(int c, int r);
		Moves
			makeMove(Player p);
				Checks validity of move and pdates board state 
				Check termination state
			bool isFull();
				True when no more valid moves
		Determine valid moves
			getMoves(Player p);
		Determine game results
			getWinner();
		Operators	
			undo();
			EXIT();
			toggleDisplay();
			AI_difficulty():
			players();
	Game Server
		initServer();
			set up server and start a game for the client
		requestMove();
			get next move from the client
Sprint 2:
	Game AI
		random move from available for first sprint
		minmax();
			Implement alpha-beta pruning
		difficulty levels
			Easy - Random move from available, no minmax
			Medium - Weighted random choice between optimal and suboptimal choices from minmax
			Hard - Optimal choice from minmax
Sprint 3:
	GUI
		mainMenu
			Give options for Human-AI or AI-AI
			set up server options; IP, Port, etc
			chooseDifficulty
			Set AI to EASY, MEDIUM, HARD
		showGame
			display game board in current state
			display undo, redo, and exit buttons
		take input for move options from player
