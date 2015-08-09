/*
Kevin O'Neill
keoneill
H343 Homework 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct card
{
	int value;
	char* name;
	struct card *next;
};

// initializing structs for player decks
struct card *p1_top = NULL;
struct card *p2_top = NULL;

struct card *p1_current = NULL;
struct card *p2_current = NULL;	

struct card * p1_last = NULL;
struct card * p2_last = NULL;

struct card *temp2top = NULL;  // used for temp structs during game-play
struct card *temp1top = NULL;

struct card *start_of_war1 = NULL;
struct card *start_of_war2 = NULL;

int p1_numCards = 26;
int p2_numCards = 26;
int num_of_turns = 0;
int numWars = 0; // keeps track of how many consecutive tied hands

int charToInt(char c);
void printHand(struct card *hand);
int winner();
void p1_winsHand();
void p1_winsWar();
void p2_winsHand();
void p2_winsWar();
void playWar();

int main()
{
	int i;

	srand(0);
	char *deckArray[52] = {"2-C","2-D","2-H","2-S",
								"3-C","3-D","3-H","3-S",
								"4-C","4-D","4-H","4-S",
								"5-C","5-D","5-H","5-S",
								"6-C","6-D","6-H","6-S",
								"7-C","7-D","7-H","7-S",
								"8-C","8-D","8-H","8-S",
								"9-C","9-D","9-H","9-S",
								"T-C","T-D","T-H","T-S",
								"J-C","J-D","J-H","J-S",
								"Q-C","Q-D","Q-H","Q-S",
								"K-C","K-D","K-H","K-S",
								"A-C","A-D","A-H","A-S"};
// Print original array	
	printf("deckArray = { ");
	for (i = 0; i < 52; i++)
	{
		printf("%s, ", deckArray[i]);
	}
	printf(" }\n");
								
//Shuffle Deck -- shuffling the array
	for (i = 51; i > 1; i--)
	{
		char* temp = deckArray[i];
		int randTemp = rand() % i;
		deckArray[i] = deckArray[randTemp];
		deckArray[randTemp] = temp;
	}

// Print shuffled array	
	printf("deckArray = { ");
	for (i = 0; i < 52; i++)
	{
		printf("%s, ", deckArray[i]);
	}
	printf(" }\n");


// creating structs for each element in the deckArray	and linking them
	for (i = 51; i > 0; i -= 2)
	{
		p1_current = (struct card *) malloc(sizeof(struct card));
		p1_current->value = charToInt(deckArray[i-1][0]);
		p1_current->name = deckArray[i-1];
		p1_current->next = p1_top;
		p1_top = p1_current;
       
		p2_current = (struct card *) malloc(sizeof(struct card));
		p2_current->value = charToInt(deckArray[i][0]);
		p2_current->name = deckArray[i];
		p2_current->next = p2_top;
		p2_top = p2_current;

		if (i == 51) // when i is 51 initialize pointer to point at last item
		{
			p1_last = p1_current;
			p2_last = p2_current;
		}
	}
  // Printing player's hands and first & last cards 
	printf("Player 1's Hand: \n");
   	printHand(p1_top);

	printf("\nPlayer 2's Hand: \n");
    printHand(p2_top);
	
	printf("p1_top: %s \n", p1_top->name);
	printf("p2_top: %s \n", p2_top->name);
	printf("p1_last: %s \n", p1_last->name);
	printf("p2_last: %s \n", p2_last->name); 


////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

// playing the game
		int p1_temp;
		int p2_temp;

	for (i = 0; i < 10000; i++)
	{
		num_of_turns += 1;
		p1_temp = p1_top->value;
		p2_temp = p2_top->value;
		
		if (p1_temp > p2_temp)  // player one wins hand
		{
			p1_winsHand();
		// check for winner
			if (winner())
			{
				printf("Player 1's Hand: \n");
				printHand(p1_top);
				printf("\nPlayer 2's Hand: \n");
				printHand(p2_top);
				break;
			}
		}	
		else if (p1_temp < p2_temp) //player 2 wins
		{
			
			p2_winsHand();
		
		// check for winner
			if (winner())
			{
				printf("Player 1's Hand: \n");
				printHand(p1_top);
				printf("\nPlayer 2's Hand: \n");
				printHand(p2_top);
				break;
			}
		}
		else // if there is a tie
		{
			numWars += 1;
			start_of_war1 = p1_top;
			start_of_war2 = p2_top;
			playWar();
		}
				
		if (i < 3)  
		{
			printf("Player 1's Hand after playing %d turn(s): \n", i+1);
			printHand(p1_top);
	
			printf("\nPlayer 2's Hand after playing %d turn(s): \n", i+1);
			printHand(p2_top);
		
			printf("p1_top: %s \n", p1_top->name);
			printf("p2_top: %s \n", p2_top->name);
			printf("p1_last: %s \n", p1_last->name);
			printf("p2_last: %s \n", p2_last->name); 
			printf("p1_numCards = %d \n", p1_numCards);
			printf("p2_numCards = %d \n", p2_numCards);
		}
	}
	/*
	if (p1_numCards > p2_numCards)
	{
		while (p1_top->next) 
		{
			p1_top = p1_top->next;
			free(p1_top);
		}
	}
	else 
	{
		while (p2_top->next) 
		{
			p2_top = p2_top->next;
			free(p2_top);
		}
	}*/
	return 0;
}


int charToInt(char c)
{
	if (c - '0' < 10)
		return c - '0';
	else 
	{
		switch(c)
		{
			case 'T': return 10;
			case 'J': return 11;
			case 'Q': return 12;
			case 'K': return 13;
			case 'A': return 14;
		}
	}
}

void printHand(struct card *hand)
{
	 while (hand)
	{
        puts(hand->name);
        hand = hand->next;
    }
}

int winner() 
{
	if (p2_numCards <= 0)
	{
		printf(" \n");
		printf("Player 1 Wins in %d turns!! \n", num_of_turns);
		return 1;
	}
	else if (p1_numCards <= 0)
	{
		printf(" \n");
		printf("Player 2 Wins in %d turns!! \n", num_of_turns);
		return 1;
	}
	else
		return 0;
}

void p1_winsHand()
{
	temp2top = p2_top;
	temp1top = p1_top;
	
	p1_top = temp1top->next;
	p2_top = temp2top->next;
	
	p1_last->next = temp1top;
	temp1top->next = temp2top;
	temp2top->next =  NULL;
	
	p1_last = temp2top;
	
	p1_numCards += 1;
	p2_numCards -= 1;
}

void p1_winsWar()
{
	int i;
	int loopMax;
	if (numWars ==1)
		loopMax = 5;
	else
		loopMax = (4*numWars +1);
	//printf("War: numWars = %d \n", numWars);
	//printf(" \n");
	//printf("player 2 wins war \n");
	//printf("p1_top = %s \n", p1_top->name);
	//printf("p2_top = %s \n", p2_top->name);
	
	// adding p2 cards to bottom of p2 deck
	for (i = 0; i < loopMax; i++) 
	{
		temp1top = p1_top;
		p1_top = temp1top->next;
		p1_last->next = temp1top;
		p1_last = temp1top;
		p1_numCards += 1;
	}
	// adding p1 cards to bottom of p2 deck
	for (i = 0; i < loopMax; i++) 
	{
		temp2top = p2_top;
		p2_top = temp2top->next;
		p1_last->next = temp2top;
		p1_last = temp2top;
		p2_numCards -= 1;
	}
	p1_last->next = NULL;
	//printf("p1_top = %s \n ", p1_top->name);
	//printf("p2_top = %s \n ", p2_top->name);
}

void p2_winsHand()
{
	temp2top = p2_top;
	temp1top = p1_top;
	// change the top card	to the next card
	p1_top =  temp1top->next; // replaced p1_current with temp*top
	p2_top = temp2top->next;
				
	p2_last->next = temp2top;
	temp2top->next = temp1top;
	temp1top->next = NULL;
	//re-assign pointers	
	p2_last = temp1top;
	
	p2_numCards += 1;
	p1_numCards -= 1;
}

void p2_winsWar()
{
	int i;
	int loopMax;
	if (numWars ==1)
			loopMax = 5;
	else
	{
		loopMax = (4*numWars +1);
		p1_top = start_of_war1;
		p2_top = start_of_war2;
	}
	//printf("War: numWars = %d \n", numWars);
	//printf(" \n");
	//printf("player 2 wins war \n");
	//printf("p1_top = %s \n", p1_top->name);
	//printf("p2_top = %s \n", p2_top->name);
	
	// adding p2 cards to bottom of p2 deck
	for (i = 0; i < loopMax; i++) 
	{
		temp2top = p2_top;
		p2_top = temp2top->next;
		p2_last->next = temp2top;
		p2_last = temp2top;
		p2_numCards += 1;
	}
	// adding p1 cards to bottom of p2 deck
	for (i = 0; i < loopMax; i++) 
	{
		temp1top = p1_top;
		p1_top = temp1top->next;
		p2_last->next = temp1top;
		p2_last = temp1top;
		p1_numCards -= 1;
	}
	p2_last->next = NULL;
	//printf("p1_top = %s \n ", p1_top->name);
	//printf("p2_top = %s \n ", p2_top->name);
}

void playWar()
{
	
	int tempVal1 = 0;
	int tempVal2 = 0;
	int i;
	
	temp2top = p2_top;
	temp1top = p1_top;
	
	if (p1_numCards < 5) // check for a winner
	{
		printf("Player 2 wins in %d turns!", num_of_turns);
	}
	if (p2_numCards < 5)
	{
		printf("Player 1 wins in %d turns", num_of_turns);
	}
	
	for (i = 0; i < 4; i++)
	{
		//printf("temp2top->name = %s \n", temp2top->name);
		//printf("temp1top->name = %s \n", temp1top->name);
		temp2top = temp2top->next;
		tempVal2 = temp2top->value;
		temp1top = temp1top->next;
		tempVal1 = temp1top->value;			
	}
	//printf("temp2top->name: %s \n", temp2top->name);
	//printf("tempVal2: %d \n", tempVal2);
	//printf("temp1top->name: %s \n", temp1top->name);
	//printf("tempVal1: %d \n", tempVal1);
	
	if (tempVal1 > tempVal2)
	{
		numWars = 0;
		p1_winsWar();
	}
	else if (tempVal2 > tempVal1)
	{
		numWars = 0;
		p2_winsWar();
	}
	else
	{
		// there is a problem with multiple ties
		
		printf("There's a second tie \n");
		printf("p1_top = %s \n", p1_top->name);
		printf("temp1top = %s \n", temp1top->name);
		numWars += 1;
		p1_numCards -= 4;
		p2_numCards -= 4;
		p1_top = temp1top;
		p2_top = temp2top;
		printf("p1_top = %s \n", p1_top->name);
		printf("temp1top = %s \n", temp1top->name);
		playWar();
	}
	
}
















