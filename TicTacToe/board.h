#include <iostream>
using namespace std;

const int Size = 5;

class Board
{

private:
	char board[Size][Size];
	int boardSize;


public:
	void resetBoard();
	void printBoard();
	void setBoardSize(int newSize);
	int getBoardSize();
	char getElement(int row, int col);
	void placeX(int row, int col);
	void placeO(int row, int col);
	void moveSymbol(int row, int col, int newRow, int newCol);
	bool checkMove(int row, int col);
	bool checkForWin(int row, int col);
	bool isEmpty(int row, int col);


	

};