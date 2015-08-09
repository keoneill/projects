#include "board.h"


void Board::resetBoard()
{
	
	//int temp = 48; // ascii int# for zero
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			board[i][j] = NULL;
			//board[i][j] = char(temp); //only needed for 3x3 hard coded win conditions
			//temp++;
		}
	}
	
}

void Board::printBoard()
{
	
//printing column index numbers
	cout << "  " ;
	for (int i = 0; i < boardSize; i++)
		cout << "  " << i << " " ;
	cout << endl;
//	print top line
	if (boardSize == 3)
		cout << "  -------------";
	else if (boardSize == 4)
		cout << "  -----------------";
	else if (boardSize == 5)
		cout << "  ---------------------";
	cout << endl;
	
	for (int i = 0; i < boardSize; i++)
	{
		cout << i << " | ";
		for (int j = 0; j < boardSize; j++) 
		{
			if (board[i][j] == 'x' || board[i][j] == 'o')
					cout << board[i][j] << " | ";
				else
					cout << " " << " | ";
				
		}
		cout << endl;
		//cout << line << endl;
		if (boardSize == 3)
			cout << "  -------------";
		else if (boardSize == 4)
			cout << "  -----------------";
		else if (boardSize == 5)
			cout << "  ---------------------";
		cout << endl;
	}
}

void Board::setBoardSize(int newSize) 
{
	boardSize = newSize;
}

int Board::getBoardSize() 
{
	return this->boardSize;
}

char Board::getElement(int i, int j)
{
	return board[i][j];
};

void Board::placeX(int row, int col)
{
	board[row][col] = 'x';
}

void Board::placeO(int row, int col)
{
	board[row][col] = 'o';
}

void Board::moveSymbol(int row, int col, int newRow, int newCol)
{
	char temp = board[row][col];
	board[row][col] = NULL;
	board[newRow][newCol] = temp;
}

bool Board::checkMove(int row, int col)
{
	if (board[row][col] == 'x' || board[row][col] == 'o')
		return 0;
	else
		return 1;
}

bool Board::checkForWin(int row, int col)
{
	int winner = 0;
	char temp = board[row][col];
	
// check diagonal
	if (row == col)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (board[j][j] == temp)
				winner++;
		}
		if (winner == boardSize)
		{
			cout << "diagonal" << endl;
			return 1;
		}
		else
			winner = 0;
	}
//check row for win
	for (int j = 0; j < boardSize; j++)
	{
		if (board[row][j] == temp)
			winner++;
	}
	if (winner == boardSize)
	{
		cout << "row" << endl;
		return 1;
	}
	else
		winner = 0;

// check column for win
	for (int i = 0; i < boardSize; i++)
	{
		if (board[i][col] == temp)
			winner++;
	}

	if (winner == boardSize)
	{
		cout << "column" << endl;
		return 1;
	}
	else
		winner = 0;

// check anti-diagonal
	int jtemp = 0;
	for (int i = boardSize-1; i > -1; i--)
	{
		if (board[i][jtemp] == temp)
		{
			winner++;
			jtemp++;
		}
	}
	if (winner == boardSize)
	{
		cout << "anti-diagonal" << endl;
		return 1;
	}
	else
		winner = 0;

// final determination
	if (winner == boardSize)
		return 1;
	else 
		return 0;
}

bool Board::isEmpty(int row, int col)
{
	return (board[row][col] == NULL);
}
				
						