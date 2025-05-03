#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

// 1
////////////////////////////////////////////////////////////

int get(int cols, int row, int col, const int* A) 
{
		return A[(row*cols) + col];
}

void prod_mat(int rowsA, int colsA, int colsB, int* A, int* B, int* AB) 
{
	for(int r=0; r<rowsA; r++)
		for(int c=0; c<colsB; c++)
		{
			AB[(r*colsB) + c] = 0; // set base value
			for(int i=0; i<colsA; i++)
				AB[(r*colsB) + c] += A[(r*colsA) + i] * B[(i*colsB) + c];
			
		}
}


void read_mat(int rows, int cols, int* t) 
{
	for(int i=0; i<(rows*cols); i++)
	{
		scanf("%d", &t[i]);
	}
}

void print_mat(int rows, int cols, int* t) 
{
	for(int r=0; r<rows; r++)
	{
		for(int c=0; c<cols; c++)
			printf("%d ", get(cols, r, c, t));
		printf("\n");
	}
}


// 2
/////////////////////////////////////////////////////////////

int read_int_lines_cont(int *ptr_array[]) 
{
	// Init:
	int* current = ptr_array[0];
	int row = 0;
	
	for(int i=0; i<TAB_SIZE; i++)
	{
		*current = 0;
		current++;
	}
	current = ptr_array[0];

	// Input variables:
	char c;
	int sign = 1; // negative/positive numbers

	// Main loop:
	while((c = getchar()) != EOF)
	{
		//printf("Wczytuję: %c\n", c);
		if(c == '\n')
		{
			// Go to new number, as if c was ' ':
				// End processing prevoius number:
				*current *= sign;
				sign = 1;

				// Get to space for new number:
				current++;
			
			// Point at the new number to indicate a new row:
			row++;
			ptr_array[row] = current;

			continue;
		}

		if(c == ' ') // Go to new number
		{
			// End processing prevoius number:
			*current *= sign;
			sign = 1;

			// Get to space for new number:
			current++;;
		}
		else 
		{
			if(c == '-')
			{
				sign = -1;
				continue;
			}
			// Add character to number:
			*current *= 10;
			*current += (c - '0');
		}
	}

	//for(int i=0; i<5; i++)
	//	printf("\n%d\n", *ptr_array[i]);
	return row;
}

void write_int_line_cont(int *ptr_array[], int n) 
{
	//printf("zaczynam wypisywać linię\n");
	int* i = ptr_array[n];
	while(i != ptr_array[n+1])
	{
		printf("%d ", *i);
		i++;
	}
	//printf("\nkończę wypisywać linię\n");
}

// 3
///////////////////////////////////////////////////////////


int read_char_lines(char *array[]) 
{
	// Init:
	int line = 0;
	int len = 0;
	char c;

	// Prepere first line:
	array[0] = malloc(TAB_SIZE * sizeof(char));

	// Main loop:
	while((c = getchar()) != EOF)
	{
		if(c == '\n') // End of line
		{
			// Append '\0':
			array[line][len] = '\0';
			len++;

			array[line] = realloc(array[line], (len+1)*sizeof(char));
			
			// Write down the progress
			line ++;

			// Prepere next row:
			len=0;
			if(line < TAB_SIZE)
			{
				array[line] = malloc(TAB_SIZE * sizeof(char));
			}

			continue; // Don't append the '\n'
		}

		// Append number to array: 
		array[line][len] = c;
		len++;
	}
	// We know that every line is ended with \n, so we have to clean up last line, which was prepered (malloc()) but never used
	free(array[line]);

	return line;
}

void write_char_line(char *array[], int n) 
{
	int i=0;
	while(array[n][i] != '\0')
	{
		printf("%c", array[n][i]);
		i++;
	}
}

void delete_lines(char *array[], int n) 
{
	for(int i=0; i<n; i++)
		free(array[i]);
}


// auxiliary
////////////////////////////////////////////////////////////

int read_int(void) {
	char c_buf[BUF_SIZE];
	fgets(c_buf, BUF_SIZE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) 
{	
	const int to_do = read_int();

	int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
	int n, rowsA, colsA, rowsB, colsB;
	char* char_lines_array[TAB_SIZE] = { NULL };
	int* ptr_array[TAB_SIZE];
	int continuous_array[TAB_SIZE];

	switch (to_do) {

		case 1:
			scanf("%d %d", &rowsA, &colsA);
			read_mat(rowsA, colsA, A);
			scanf("%d %d", &rowsB, &colsB);
			read_mat(rowsB, colsB, B);
			prod_mat(rowsA, colsA, colsB, A, B, AB);
			print_mat(rowsA, colsB, AB);
			break;

		case 2:
			n = read_int() - 1; // we count from 1 :)
			//printf("n = %d\n", n);
			ptr_array[0] = continuous_array;
			read_int_lines_cont(ptr_array);
			write_int_line_cont(ptr_array, n);
			break;

		case 3:
			n = read_int() - 1;
			int rows = read_char_lines(char_lines_array);
			write_char_line(char_lines_array, n);
			delete_lines(char_lines_array, rows);
			break;

		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}