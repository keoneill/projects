#include "player.h"
#include "board.h"


class Game
{
private:
	Board myBoard;
	int turns; // keeps track of total # of turns played
	int choice; // user input for position on board
	int nextRow, nextCol;

public:
	void play();
	void playComp();
	void computerMove(int lastMove);
	void alternateMove();
};