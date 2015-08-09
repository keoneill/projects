// All the work herein is mine <04/24/2014>
// Kevin O'Neill keoneill@indiana.edu
// I have read http://studentaffairs.iub.edu/ethics/

#include "game.h"


int main()
{
	int ans = 0;
	Game newGame;
	
	cout << "Play against Computer (1) or a Two Player(2) game? : " ;
	cin >> ans;
	if (ans == 1)
		newGame.playComp();
	else
		newGame.play();

	cout << "Would you like to: start a new game (1) or Quit (0)" << endl;
	cin >> ans;

	if (ans == 1)
		main();
	else
		return 0;

	return 0;
}
