/*
Kevin O'Neill
keoneill
Homework 4 -- Hash Tables
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void keyMaxMin(char * filename, int * min, int * max)
{
	char c;
	char line[60];
	int Aid, size, Rid;
	int newMin = 0;
	int newMax = 0;

	FILE *myfile;
	
	myfile = fopen(filename, "r");
	if (!myfile)
	{
		puts("file not found!");
		exit(1);
	}
	
	fgets(line, 60, myfile);
	sscanf(line, "%c, %d, %d", &c, &newMin, &size);
	
	while ( fgets(line, 60, myfile) != NULL )
	{
		if (line[0] == 'A')
		{
			sscanf(line, "%c, %d, %d", &c, &Aid, &size);
			if (Aid < newMin)
				newMin = Aid;
			if (Aid > newMax)
				newMax = Aid;
		}
	}
	fclose(myfile);
	
	*min = newMin;
	*max = newMax;

}

int main()
{
	char filename[80] = "data.txt";
	char line[60];
	int min = 0;
	int max = 0;
	int i;
	char c;
	int Aid, size, Rid;

	keyMaxMin(filename, &min, &max);
	
	int tableSize = (max - min) +1;
	int hashTable	[tableSize];
	
	FILE *myfile;
	
	myfile = fopen(filename, "r");
	if (!myfile)
	{
		puts("file not found!");
		exit(1);
	}

	while ( fgets(line, 60, myfile) != NULL )
	{

		if (line[0] == 'A')
		{
			sscanf(line, "%c, %d, %d", &c, &Aid, &size);
			hashTable[Aid % tableSize] = size;
		}
		else if (line[0] == 'R')
		{
			sscanf(line, "%c, %d", &c, &Rid);
			printf("id %d:\n  size = %d\n", Rid, hashTable[Rid % tableSize]);
		}
		else
		{
			printf("Error reading data");
		}
	}

	fclose(myfile);
	
	return 0;
}





