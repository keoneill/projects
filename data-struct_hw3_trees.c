/*
Kevin O'Neill
keoneill
Homework 3 -- Trees
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 128;

// Using AVL Tree 
struct treeNode 
{
	char * word;
	int count;
	int balance; // should be -1, 0, or 1
	struct treeNode * leftChild;
	struct treeNode * rightChild;
	struct treeNode * parent;

};

struct treeNode * root = NULL;
struct treeNode	* new_node = NULL;

void countWords(char * filename);
void printTree(struct treeNode * root);
int stringsMatch(char * str1, char * str2);
void countChars(char * filename, int * charCountArray);
void printCharArray(int * charCountArray);
void insertNode(struct treeNode * root, char * word);
int left_or_right(char * str1, char * str2); 	// determines whether a word should 
																//be placed in left or right child

int main()
{
	char filename[80];
	int charCountArray[SIZE];
	int i;
	char c;
		
//Get filename from user and save as char string
	printf("Enter the filename: \n");
	scanf("%s", filename);
	printf("%s", filename);
	
// Initialize array for character count with zeroes
	for (i = 0; i < SIZE; i++)
	{
		charCountArray[i] = 0;
	}
	
// count and printing occurrences of characters in file	
	printf("\nReading file ... \n");
	countChars(filename, charCountArray);
	
	printf("Printing character counts: \n\n");
	printCharArray(charCountArray);

// counting occurrences of words in file
	printf("Counting words...\n");
	countWords(filename);
		
// Printing the words and word counts from tree.
	printf("\nPrinting words: \n\n");
	printf("Word            |  # of occurrences \n");
	printf("-----------------------------------\n\n");
	
	printTree(root);
	
	return 0;
}

void countWords(char * filename)
{
	char word[40];
	int isWord = 0; // Boolean used for knowing the end of a word
	int i = 0;
	char c;	
	FILE *myfile;

	myfile = fopen(filename, "r");
	if (!myfile)
	{
		puts("file not found!");
		exit(1);
	}
	
	do
	{
		do
		{
			c = fgetc(myfile);
			if (c >= 65 && c <= 90) // make upper-case lower-case
			{									// so that words will not count twice if differing only by case
				c += 32;					
			}	
			if (c >= 97 && c <= 122)
			{
				word[i] = c;
				i++;
				isWord = 1;
			}

			else
			{
				if (isWord) // if the previous character was last character of word
				{
					word[i] = '\0';
					if ( root == NULL ) 
					{
						root = (struct treeNode *) malloc( sizeof( struct treeNode ) );
						
						root->word = strdup(word);
						root->balance = 0;
						root->count = 1; // Keeps track of occurrences of that word
						root->leftChild = NULL;
						root->rightChild = NULL;
						root->parent = NULL;
					}
					else 
					{
						insertNode(root, word); 
					}
					isWord = 0;
					i = 0;
				}
				else // if there are still characters not part of words
					isWord = 0;
			}
		}
		while (isWord);
	}	
	while (c != EOF);
	
	fclose(myfile);
}

void printTree(struct treeNode * current_node)
{
	
	if (current_node != NULL)
	{
		printTree(current_node->leftChild);
		printf("%-20s %d\n", current_node->word, current_node->count);
		printTree(current_node->rightChild);
	}
}

void insertNode(struct treeNode * node, char * word)
{
	if (stringsMatch(word, node->word) )
	{
		node->count += 1;
	}
	else if (left_or_right(word, node->word) == -1) // Left Child
	{
		if (node->leftChild == NULL)
		{
			printf("%s becomes left-child of %s\n", word, node->word);//becomes left child
			
			new_node = (struct treeNode *) malloc( sizeof( struct treeNode ) );
			
			new_node->word = strdup(word);
			new_node->balance = 0;
			new_node->count = 1; // Keeps track of occurrences of that word
			new_node->leftChild = NULL;
			new_node->rightChild = NULL;
			new_node->parent = node;
			
			node->leftChild = new_node;
			node->balance -= 1;
			printf("  balance of %s is %d\n", node->word, node->balance);
		}
		else
		{
			//node->leftChild->balance = node->balance - 1; // ADDED IN UPDATE
			insertNode(node->leftChild, word);
		}

	}
	else if (left_or_right(word, node->word) == 1) // Right Child
	{
		if (node->rightChild == NULL)
		{
			printf("%s becomes right-child of %s\n", word, node->word);//becomes right child

			new_node = (struct treeNode *) malloc( sizeof( struct treeNode ) );
			
			new_node->word = strdup(word);
			new_node->balance = 0;
			new_node->count = 1;
			new_node->leftChild = NULL;
			new_node->rightChild = NULL;
			new_node->parent = node;
			
			node->rightChild = new_node;
			node->balance += 1;
			printf("  balance of %s is %d\n", node->word, node->balance);
		}
		else
		{
			//node->rightChild->balance = node->balance + 1; // ADDED IN UPDATE
			insertNode(node->rightChild, word);
		}
	}
	
	if (node != root && node->parent->balance > 1)
		printf("    Node needs to be rotated to the left, parent = %s; balance = %d \n", node->parent->word, node->parent->balance);
	else if (node != root && node->parent->balance < -1)
		printf("    Node needs to be rotated to the right, parent = %s; balance = %d \n", node->parent->word, node->parent->balance);
}

int left_or_right(char * str1, char * str2) 
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int i;
	int maxIter;
	if (len1 >= len2)
		maxIter = len2;
	else
		maxIter = len1;
	
	for (i = 0; i < maxIter + 1 ; i++)
	{
		if (str1[i] < str2[i] || str1[i] == '\0')
			return -1;
		else if (str1[i] > str2[i] || str2[i] == '\0')
			return 1;
	}
}

int stringsMatch(char  * str1, char * str2)
{
	int result;
	result = strcmp(str1, str2);
	if (result == 0)
		return 1;
	else	
		return 0;
}

void countChars(char * filename, int * charCountArray)
{
	FILE *myfile;
	char c;
	
	myfile = fopen(filename, "r");
	if (!myfile)
	{
		puts("file not found!");
		exit(1);
	}

// count characters	
	do
	{
		c = fgetc(myfile);
		//printf("%c",c);
		if (c >= 0 && c < 128)
			charCountArray[c] += 1;
	}
	while (c != EOF);

	fclose(myfile);
	printf("\nFile closed. \n");
}

void printCharArray(int * charCountArray)
{
	int i;
	char c;
	
	printf("ASCII # | Char | # occurences | Name\n");
	for (i = 0; i < SIZE; i++)
	{
		switch(i)
		{
			case 0:
				printf("%3d %9c %12d      'Null' \n", i, 32, charCountArray[i]); break;
			case 1:
				printf("%3d %9c %12d      'Start of heading' \n", i, 32, charCountArray[i]); break;
			case 2:
				printf("%3d %9c %12d      'Start of text' \n", i, 32, charCountArray[i]); break;
			case 3:
				printf("%3d %9c %12d      'End of text' \n", i, 32, charCountArray[i]); break;
			case 4:
				printf("%3d %9c %12d      'End of transmission' \n", i, 32, charCountArray[i]); break;
			case 5:
				printf("%3d %9c %12d      'Enquiry' \n", i, 32, charCountArray[i]); break;
			case 6:
				printf("%3d %9c %12d      'Acknowledge' \n", i, 32, charCountArray[i]); break;
			case 7:
				printf("%3d %9c %12d      'Bell' \n", i, 32, charCountArray[i]); break;
			case 8:
				printf("%3d %9c %12d      'Backspace' \n", i, 32, charCountArray[i]); break;
			case 9:
				printf("%3d %9c %12d      'Horizontal tab' \n", i, 32, charCountArray[i]); break;
			case 10:
				printf("%3d %9c %12d      'NL line feed, new line' \n", i, 32, charCountArray[i]); break;
			case 11:
				printf("%3d %9c %12d      'Vertical tab' \n", i, 32, charCountArray[i]); break;
			case 12:
				printf("%3d %9c %12d      'NP form feed, new page' \n", i, 32, charCountArray[i]); break;
			case 13:
				printf("%3d %9c %12d      'Carriage return' \n", i, 32, charCountArray[i]); break;
			case 14:
				printf("%3d %9c %12d      'Shift out' \n", i, 32, charCountArray[i]); break;
			case 15:
				printf("%3d %9c %12d      'Shift in' \n", i, 32, charCountArray[i]); break;
			case 16:
				printf("%3d %9c %12d      'Data link escape' \n", i, 32, charCountArray[i]); break;				
			case 17:
				printf("%3d %9c %12d      'Device control 1' \n", i, 32, charCountArray[i]); break;				
			case 18:
				printf("%3d %9c %12d      'Device control 2' \n", i, 32, charCountArray[i]); break;
			case 19:
				printf("%3d %9c %12d      'Device control 3' \n", i, 32, charCountArray[i]); break;
			case 20:
				printf("%3d %9c %12d      'Device control 4' \n", i, 32, charCountArray[i]); break;				
			case 21:
				printf("%3d %9c %12d      'Negative acknowledge' \n", i, 32, charCountArray[i]); break;
			case 22:
				printf("%3d %9c %12d      'Synchronous idle' \n", i, 32, charCountArray[i]); break;
			case 23:
				printf("%3d %9c %12d      'End of trans. block' \n", i, 32, charCountArray[i]); break;			
			case 24:
				printf("%3d %9c %12d      'Cancel' \n", i, 32, charCountArray[i]); break;
			case 25:
				printf("%3d %9c %12d      'End of medium' \n", i, 32, charCountArray[i]); break;				
			case 26:
				printf("%3d %9c %12d      'Substitute' \n", i, 32, charCountArray[i]); break;
			case 27:
				printf("%3d %9c %12d      'Escape' \n", i, 32, charCountArray[i]); break;
			case 28:
				printf("%3d %9c %12d      'File separator' \n", i, 32, charCountArray[i]); break;
			case 29:
				printf("%3d %9c %12d      'Group separator' \n", i, 32, charCountArray[i]); break;
			case 30:
				printf("%3d %9c %12d      'Record separator' \n", i, 32, charCountArray[i]); break;	
			case 31:
				printf("%3d %9c %12d      'Unit separator' \n", i, 32, charCountArray[i]); break;
			case 32:
				printf("%3d %9c %12d      'Space' \n", i, i, charCountArray[i]); break;
			case 127:
				printf("%3d %9c %12d      'Delete' \n", i, 32, charCountArray[i]); break;
			default:                                                                       
				c = i;
				printf("%3d %9c %12d %7c \n", i, c, charCountArray[i], c); break;
		}

	}
}

