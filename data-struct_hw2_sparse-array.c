// Kevin O'Neill
// keoneill
// Homework #2 Sparse Arrays


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cell
{
	int row;
	int col;
	double data;
	struct cell * next_row_cell;
	struct cell * next_col_cell;
};

struct headPointer
{
	struct rowStart *next_row_ptr;
	struct colStart *next_col_ptr;
};

struct rowStart
{
	struct cell * next_col;
	struct rowStart * next_row;
};

struct colStart
{
	struct colStart * next_col;
	struct cell * next_row;
};

struct InputMatrix
{
	int row;
	int col;
	int data;
};

static int LEN; // used for making input array in read_data()
static struct InputMatrix *input = NULL;
int num_lines; // number of lines in file, used in main(), read_data(), and MaxRowCols() functions

void read_data();
void MaxRowCols(int *maxRows, int *maxCols);
void printArray(struct headPointer *head_ptr);
void rowMath(struct headPointer *head_ptr, int maxRows);
double findMultiple(struct headPointer *head_ptr, int row);

////////////////// MAIN //////////////////////////////////////////////////////////

int main()
{
	int i;
	int row;
	int col;
	int maxRows = 0;
	int maxCols = 0;
	int nextRow = 0;
	
// Initializing Structs and making links to first cells
	struct headPointer *head_ptr = NULL;
	head_ptr = (struct headPointer *) malloc(sizeof(struct headPointer));
	
	// row pointers
	struct rowStart *row_pointer = NULL;
	row_pointer = (struct rowStart *) malloc(sizeof(struct rowStart));
	struct rowStart *current_row_ptr = row_pointer;
	struct rowStart *next_row_ptr = NULL;
	
	// column pointers
	struct colStart *col_pointer = NULL; // will be first col
	col_pointer = (struct colStart *) malloc(sizeof(struct colStart));
	struct colStart *current_col_ptr = col_pointer;
	struct colStart *next_col_ptr = NULL;
	
	// cell pointers
	struct cell * current_cell =NULL;
	current_cell = (struct cell *) malloc(sizeof(struct cell));
	struct cell * current_row_cell = NULL; // used to link columns to current cell
	struct cell * current_col_cell = NULL; // used to link row pointer to current cell
	struct cell * new_col_cell = NULL; // used making new cells while filling sparse array with data
		
// head pointer will always point to first row pointer and first column pointer	
	head_ptr->next_row_ptr = row_pointer; 
	head_ptr->next_col_ptr = col_pointer;
	
//Reading Data
	printf("Reading Data ... \n");
	
	read_data(); // reads in sparse_data and creates array of the input
	
	for (i = 0; i <= num_lines; i++)
	{
		printf("line %d: ", i+1);
		printf("row: %d ,", input[i].row);
		printf("col: %d , ",  input[i].col);
		printf("data: %d \n", input[i].data); 
	} // */
	printf(" \n");

// finding the number of rows and columns	
	MaxRowCols(&maxRows, &maxCols);
	
	printf("maxRows = %d \n", maxRows);
	printf("maxCols = %d \n", maxCols);
	
// link column pointers
	current_col_ptr = col_pointer; // establishing first column pointer
	for (i = 0; i <= maxCols; i++)
	{
		next_col_ptr = (struct colStart *)malloc(sizeof(struct colStart));
		current_col_ptr->next_col = next_col_ptr;
		current_col_ptr->next_row = NULL;
		current_col_ptr = next_col_ptr;
		if (i == 0)
			col_pointer->next_col = current_col_ptr;
	}
	current_col_ptr->next_col = NULL;
	current_col_ptr->next_row = NULL;
	
// link row pointers	
	current_row_ptr = row_pointer; // establishing first row pointer
	for (i = 0; i <= maxRows; i++)
	{
		//printf("adding row %d pointer \n", i+1);
		next_row_ptr = (struct rowStart *)malloc(sizeof(struct rowStart));
		current_row_ptr->next_row = next_row_ptr;
		current_row_ptr->next_col = NULL;
		current_row_ptr = next_row_ptr;
		if (i == 0)
			row_pointer->next_row = current_row_ptr;
	}
	current_row_ptr->next_row = NULL;
	current_row_ptr->next_col = NULL;

// reset pointers to beginning of row and columns	
	current_col_ptr = col_pointer;
	current_row_ptr = row_pointer;
	
	printf("Inserting Data from input array into sparse array... \n");
// Insert Data from input array into sparse array
	for (i = 0; i <= num_lines; i++)
	{
		row = input[i].row+1;
		col = input[i].col+1;
		nextRow = input[i+1].row+1;
		
		if (i == 0)
		{
			col_pointer->next_row = current_cell;
			row_pointer->next_col = current_cell;
		} 
				
		//Assigning data to current cell ////////////////////////////
		new_col_cell = (struct cell *)malloc(sizeof(struct cell));	
		current_cell->row = input[i].row;
		current_cell->col = input[i].col;
		current_cell->data = input[i].data;
		if (nextRow > row)
		{
			current_cell->next_col_cell = NULL;
			current_cell->next_row_cell = NULL;
		}
		else
		{
			current_cell->next_col_cell = new_col_cell;
			current_cell->next_row_cell = NULL;
			current_cell->next_col_cell = NULL;
		} 
		
//// Linking column pointers to current cell
		int j;
		for (j = 0; j < col; j++)
		{
			current_col_ptr = current_col_ptr->next_col;
		}
		if (current_col_ptr->next_row == NULL)
		{
			current_col_ptr->next_row = current_cell;
		}
		else 
		{
			current_row_cell = current_col_ptr->next_row;
			while (current_row_cell->next_row_cell != NULL)
			{
				current_row_cell = current_row_cell->next_row_cell;
			}
			current_row_cell->next_row_cell = current_cell;
		}

//// Linking row pointers to current cell
		int k;
		for (k = 0; k < row; k++)
		{
			current_row_ptr = current_row_ptr->next_row; //goes to row in which next data cell will be inserted
		}
		if (current_row_ptr->next_col == NULL)
		{
			current_row_ptr->next_col = current_cell;
		}
		else
		{
			current_col_cell = current_row_ptr->next_col;
			while (current_col_cell->next_col_cell != NULL)
			{
				current_col_cell = current_col_cell->next_col_cell;
			}
			current_col_cell->next_col_cell = current_cell;
		}
		
		current_cell = new_col_cell;
		current_col_ptr = col_pointer; // resetting col pointer to beginning
		current_row_ptr = row_pointer; // resetting row pointer to beginning

	}
	
//////  Printing Sparse Array
	printArray(head_ptr); 
	free(input);
	rowMath(head_ptr, maxRows);
	printArray(head_ptr);

	return 0;
}

////////////// Function Definitions //////////////////////////////////////////////

void read_data()
{
	FILE *myfile;
	char c;
	int commas = 0;
	int line_position = 0; // distance from last comma
	int temp_num = 1; // used to hold temp value of row, col, and data
	int current_line = 0;
	num_lines = 0;
	
	myfile = fopen("sparse_data.txt","r");
	if (!myfile)
	{
		puts("sparse_data.txt not found!");
		exit(1);
	}
	
// count lines in file	
	do
	{
		c = fgetc(myfile);
		if (c == '\n' || c == !EOF)
		{
			num_lines += 1;
		}
	}
	while (c != EOF);
	rewind(myfile);
	
//	Make matrix for storing array from file
    LEN = num_lines+1;
    input = calloc(LEN, sizeof(struct InputMatrix));
    if (input == NULL)
    {
       printf("Memory error!\n");
       exit(-1);
    }
	
//reading from file and storing data in input array
	do
	{
		c = fgetc(myfile);
		
		if (c == '\n' || c == EOF)
		{
			input[current_line].data = temp_num;
			commas = 0;
			line_position = 0;
			temp_num = 1;
			current_line += 1;
		}
		else if (c == ',')
		{
			if (commas == 0)
			{
				input[current_line].row = temp_num;
				commas += 1;
				temp_num = 1;
				line_position = 0;
			}
			else if (commas == 1)
			{
				input[current_line].col = temp_num;
				commas += 1;
				temp_num = 1;
				line_position = 0;
			}
			else
			{
				commas += 1;
				temp_num = 1;
			}
		}
		else 
		{
			if (line_position <= 0)
			{
				temp_num *= atoi(&c);
				line_position += 1;
			}
			else if (line_position > 0)
			{
				temp_num = (temp_num * 10) + atoi(&c);
				line_position += 1;
			}
		} 
	}
	while (c != EOF);
	fclose(myfile);
}

void MaxRowCols(int *maxRows, int *maxCols)
{
	int row;
	int col;
	int i;

	for (i = 0; i <= num_lines; i++)
	{
		row = input[i].row;
		col = input[i].col;
		if (row > *maxRows)
			*maxRows = row;
		if (col > *maxCols)
			*maxCols = col;
	} 
}

void printArray(struct headPointer *head_ptr)
{                                                                                                       
	struct rowStart *current_row_ptr = head_ptr->next_row_ptr;
	struct cell * current_col_cell = head_ptr->next_row_ptr->next_col;
	
	
	printf(" \n");
	printf("Printing sparse array: \n");
	
	while (current_row_ptr->next_row != NULL)
	{
		current_row_ptr = current_row_ptr->next_row;	
		current_col_cell = current_row_ptr->next_col;
		
		while (current_col_cell->next_col_cell != NULL)
		{
			printf("row: %d, ", current_col_cell->row);
			printf("col: %d, ", current_col_cell->col);
			printf("data: %.3lf \n", current_col_cell->data);
			current_col_cell = current_col_cell->next_col_cell;
		}
		printf("row: %d, ", current_col_cell->row);
		printf("col: %d, ", current_col_cell->col);
		printf("data: %.3lf \n", current_col_cell->data);
	}
}

void rowMath(struct headPointer *head_ptr, int maxRows)
{
	struct rowStart *current_row_ptr = head_ptr->next_row_ptr;
	struct cell * current_col_cell = head_ptr->next_row_ptr->next_col;
	current_row_ptr = current_row_ptr->next_row;

	printf(" \n");
	printf("Calculating row operations... \n");
	
	int i = 0;
	while (i < maxRows)//(current_row_ptr->next_row != NULL) // 
	{
		double multiple = findMultiple(head_ptr, i);
		printf("multiple = %.3lf \n", multiple);
		i++;
	}
	printf("end of rowMath. found multiples but did not finish Matrix operations :( \n");
	
	
}
double findMultiple(struct headPointer *head_ptr, int row)
{
		struct rowStart *current_row_ptr = head_ptr->next_row_ptr;
		current_row_ptr = current_row_ptr->next_row;
		int next_non_zero_row;
		double multiple;
		double data_K_J;
		double data_I_J = current_row_ptr->next_col->data;
		int i;
		for (i = 0; i < row; i++)
		{
			current_row_ptr = current_row_ptr->next_row;
		}
		
		if (current_row_ptr->next_col->next_row_cell != NULL)
		{
			next_non_zero_row = current_row_ptr->next_col->next_row_cell->row;
			printf("row (I) = %d; next_non_zero_row(K) = %d \n", i, next_non_zero_row);
			
			int k;
			for (k = i; k < next_non_zero_row; k++)
			{
				current_row_ptr = current_row_ptr->next_row;
			}	
			data_K_J = current_row_ptr->next_col->data;
			multiple = data_K_J / data_I_J;
		}
		else
		{
			printf("row (I) = %d; next_non_zero_row(K) = %d \n", i, next_non_zero_row);
			multiple = 0;
		}
		return multiple;
}


					
