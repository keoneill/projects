#include "game.h"

void Game::play()
{
	
	Player player1;
	Player player2;
	string temp_name; // used to get names from user, will reuse for both players
	int userBoardSize;
	char turnOption; // 'p' or 'm' (place or move)
	int movePos; // used to get new position for moving a symbol
	
	cout << "Enter a name for player 1: " << endl;
	cin >> temp_name;
	player1.setName(temp_name);
	cout << "Enter a name for player 2: " << endl;
	cin >> temp_name;
	player2.setName(temp_name);
	cout << "Enter a board size: 3, 4, or 5: " << endl;
	cin >> userBoardSize;
	myBoard.setBoardSize(userBoardSize);
	cout << "You will be playing on a " << myBoard.getBoardSize() << " X ";
	cout << myBoard.getBoardSize() << " board." << endl;
	
	myBoard.resetBoard(); // sets each space in board to null
	myBoard.printBoard();

	turns = 1; // initializing to 1 for first players turn.
	while (turns < userBoardSize*userBoardSize) // if all possible turns are played, game is tied
	{
	// player 1's turn			
		cout << player1.getName();
			//give player option of moving or placing
		cout << ", would you like to (p)lace or (m)ove a symbol?: " ;
		cin >> turnOption;
		
		if (turnOption == 'p' || turnOption == 'P')
		{
			cout << "To place an 'x' enter a board position as row and col (00, 01,...44): " << endl;
			cin >> choice;
			//check if move is valid
			if (! myBoard.checkMove(choice / 10, choice % 10)) 
			{
				cout << "Invalid move, enter a new position: " << endl;
				cin >> choice;
			}
			//will use choice to determine position on board
				 // dividing choice by 10 gives the row
				// remainder after dividing by 10 gives column
			myBoard.placeX(choice / 10, choice % 10);
		}
		else // moving a symbol
		{
			cout << "Enter position of symbol to move: " ;
			cin >> choice;
			cout << "Enter position to move symbol: " ;
			cin >> movePos;
			myBoard.moveSymbol(choice / 10, choice % 10, movePos / 10, movePos % 10);
		}
				
		myBoard.printBoard();					 

		// Only need to check for winner after a certain number of turns
		if (turns > (userBoardSize - 1) * 2) 
		{
			if (myBoard.checkForWin(choice / 10, choice % 10))	
			{
				cout << player1.getName() << " wins!" << endl;
				return;
			}
		}
		turns++;

	// Player 2's turn
		cout << player2.getName();
		cout << ", would you like to (p)lace or (m)ove a symbol?: " ;
		cin >> turnOption;
		
		if (turnOption == 'p' || turnOption == 'P')
		{
			cout << "To place an 'o' enter a board position as row and col (00, 01,...44): " << endl;
			cin >> choice;
			//check if move is valid
			if (! myBoard.checkMove(choice / 10, choice % 10)) 
			{
				cout << "Invalid move, enter a new position: " << endl;
				cin >> choice;
			}
			//will use choice to determine position on board
				 // dividing choice by 10 gives the row
				// remainder after dividing by 10 gives column
			myBoard.placeO(choice / 10, choice % 10);
		}
		else // moving a symbol
		{
			cout << "Enter position of symbol to move: " ;
			cin >> choice;
			cout << "Enter position to move symbol: " ;
			cin >> movePos;
			myBoard.moveSymbol(choice / 10, choice % 10, movePos / 10, movePos % 10);
		}
			
		myBoard.printBoard();
		
		if (turns > (userBoardSize - 1) * 2)
		{
			if (myBoard.checkForWin(choice / 10, choice % 10))
			{
				cout << player2.getName() << " wins!" << endl;
				return;
			}
		}
		turns++;
	}

// If board has an even number of spaces, game is tied at this point	
	if (userBoardSize % 2 == 0)
	{
		cout << "It's a tie." << endl;
		cout << "Game Over" << endl;
	}
	else
	{
// player 1 gets last move since board has odd # of spaces
		cout << player1.getName();
			//give player option of moving or placing
		cout << ", would you like to (p)lace or (m)ove a symbol?: " ;
		cin >> turnOption;
		
		if (turnOption == 'p' || turnOption == 'P')
		{
			cout << "To place an 'x' enter a board position as row and col (00, 01,...44): " << endl;
			cin >> choice;
			//check if move is valid
			if (! myBoard.checkMove(choice / 10, choice % 10)) 
			{
				cout << "Invalid move, enter a new position: " << endl;
				cin >> choice;
			}
			myBoard.placeX(choice / 10, choice % 10);
		}
		else // moving a symbol
		{
			cout << "Enter position of symbol to move: " ;
			cin >> choice;
			cout << "Enter position to move symbol: " ;
			cin >> movePos;
			myBoard.moveSymbol(choice / 10, choice % 10, movePos / 10, movePos % 10);
		}
	
		myBoard.printBoard();
		
	
	
		if (myBoard.checkForWin(choice / 10, choice % 10))
		{
			cout << player1.getName() << "wins!" << endl;
		}
		else
		{
			cout << "It's a tie." << endl;
		}
	
		cout << "Game Over" << endl;
	}

}

void Game::playComp() 
{
	Player player1;
	Player player2;
	string temp_name; // used to get names from user, will reuse for both players
	int userBoardSize;
	
	cout << "Enter a name for player 1: " << endl;
	cin >> temp_name;
	player1.setName(temp_name);
	player2.setName("Computer");
	cout << "Enter a board size: 3, 4, or 5: " << endl;
	cin >> userBoardSize;
	myBoard.setBoardSize(userBoardSize);
	cout << "You will be playing on a " << myBoard.getBoardSize() << " X ";
	cout << myBoard.getBoardSize() << " board." << endl;
	
	myBoard.resetBoard();
	myBoard.printBoard();
	
	turns = 1; // initializing to 1 for first players turn.
	while (turns < userBoardSize*userBoardSize) // if all possible turns are played, game is tied
	{
		cout << player1.getName() << ", to place an 'x' enter a board position as row and col (00, 01,...44): " << endl;
		cin >> choice;
		if (! myBoard.checkMove(choice / 10, choice % 10))
		{
			cout << "Invalid move, enter a new position: " << endl;
			cin >> choice;
		}
		myBoard.placeX(choice / 10, choice % 10);
		myBoard.printBoard();
		
		if (turns > (userBoardSize - 1) * 2)
		{
			if (myBoard.checkForWin(choice / 10, choice % 10))
			{
				cout << player1.getName() << " wins!" << endl;
				return;
			}
		}
		turns++;

	// computer move
		cout << "computers move..." << endl;
		computerMove(choice); // set nextRow and nextCol
		myBoard.placeO(nextRow, nextCol); // places computer move
		myBoard.printBoard();

		// check if computer wins	
		if (myBoard.checkForWin(nextRow, nextCol))
		{
			cout << "Computer wins!" << endl;
			return;
		}
		turns++;
	}

// If board has an even number of spaces, game is tied at this point	
	if (userBoardSize % 2 == 0)
	{
		cout << "It's a tie." << endl;
		cout << "Game Over" << endl;
	}
	else
	{
// player 1 gets last move since board has odd # of spaces
		cout << player1.getName();
		cout << ", to place an 'x' enter a board position as row and col (00, 01,...44): " << endl;
		cin >> choice;
		if (! myBoard.checkMove(choice / 10, choice % 10))
		{
			cout << "Invalid move, enter a new position: " << endl;
			cin >> choice;
		}
		myBoard.placeX(choice / 10, choice % 10);
		myBoard.printBoard();
		
		if (myBoard.checkForWin(choice / 10, choice % 10))
		{
			cout << player1.getName() << "wins!" << endl;
		}
		else
		{
			cout << "It's a tie." << endl;
		}

		cout << "Game Over" << endl;
	}
}


void Game::computerMove(int lastMove)
{
	int max = myBoard.getBoardSize() - 1;
	int row = lastMove / 10;
	int col = lastMove % 10;
	int numX = 0;
	int nullCells = 0;


// check diagonal for near win

	if (row == col)
	{
		for (int j = 0; j <= max; j++)
		{
			if (myBoard.getElement(j,j) == 'x')
				numX++;
			else if (myBoard.getElement(j,j) == NULL)
			{
				nullCells++;
				nextRow = j;
				nextCol = j;
			}
		}
		if (numX == max && nullCells == 1)
		{
			return;
		}
		else
		{
			numX = 0; // reset counters
			nullCells = 0;
		}
	}

//check row for near win
	for (int j = 0; j <= max; j++)
	{
		if (myBoard.getElement(row,j) == 'x')
			numX++;
		else if (myBoard.getElement(row,j) == NULL)
		{
			nullCells++;
			nextRow = row;
			nextCol = j;
		}
	}
	if (numX == max && nullCells == 1)
	{
		return;
	}
	else
	{
		numX = 0;
		nullCells = 0;
	}


// check column for near win

	for (int i = 0; i <= max; i++)
	{
		if (myBoard.getElement(i,col) == 'x')
			numX++;
		else if (myBoard.getElement(i,col) == NULL)
		{
			nullCells++;
			nextRow = i;
			nextCol = col;
		}
	}

	if (numX == max && nullCells == 1)
	{
		return;
	}
	else
	{
		numX = 0;
		nullCells = 0;
	}


// check anti-diagonal for near win

	int jtemp = 0;
	for (int i(max); i > -1; i--)
	{
		if (myBoard.getElement(i,jtemp) == 'x')
			numX++;
		else if (myBoard.getElement(i,jtemp) == NULL)
		{
			nullCells++;
			nextRow = i;
			nextCol = jtemp;
		}
		jtemp++;
	}
	if (numX == max && nullCells == 1)
	{
		return;
	}
	else
	{
		numX = 0;
		nullCells = 0;
	}

// basic moves

	if (row < max && col < max)
	{
		nextRow = row + 1;
		nextCol = col + 1;
		
		if (myBoard.isEmpty(nextRow, nextCol))
		{
			return;
		}
		else
		{
			alternateMove();
			return;
		}
	}
	else if (row > 0 && col > 0)
	{
		nextRow = row - 1;
		nextCol = col - 1;
		
		if (myBoard.isEmpty(nextRow, nextCol))
		{
			return;
		}
		else
		{
			alternateMove();
			return;
		}
	}
	else if (row > 0)
	{
		nextRow = row - 1;
		nextCol = col;

		if (myBoard.isEmpty(nextRow, nextCol))
		{
			return;
		}
		else
		{
			alternateMove();
			return;
		}
	}
}

// if spaces are filled in other conditions
// computer looks for an empty space that is adjacent to an 'x'
void Game::alternateMove() 
{
	int max = myBoard.getBoardSize();
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			if (myBoard.getElement(i,j) == NULL)
			{
				nextRow = i;
				nextCol = j;
				if (myBoard.getElement(i,j+1) == 'x' || myBoard.getElement(i+1, j) == 'x')
					return;
			}
		}
	}
}