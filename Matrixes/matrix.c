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

int read_int_lines_cont(int* ptr_array[], int* row_len) 
{
	// Init:
	int line = 0;
	int len = 0;
	char c;
	int sign = 1;

	// Prepere first line:
	ptr_array[0] = malloc(TAB_SIZE * sizeof(int));

	// Main loop:
	while((c = getchar()) != EOF)
	{
		if(c == '\n') // End of line
		{
			ptr_array[line] = (int*)realloc(ptr_array[line], (len+1)*sizeof(int));
			row_len[line] = len+1;

			sign = 1;
			line ++;
			printf("Długość: %d\n", len);
			len=0;
			row_len[line] = 0;

			// Prepere next row:
			if(line < TAB_SIZE)
			{
				ptr_array[line] = malloc(TAB_SIZE * sizeof(int));
				ptr_array[line][0] = 0; 
			}

			continue;
		}

		if(c == ' ') // Go to next array space
		{
			ptr_array[line][len] *= sign;
			sign = 1;

			len++;
			ptr_array[line][len] = 0;
		}

		if(c == '-')
		{
			sign = -1;
			continue;
		}

		if(c != ' ') // Append number to array:
		{
			ptr_array[line][len] *= 10; 
			ptr_array[line][len] += c - 48;
		}
	}
	// We know that every line is ended with \n, so we have to clean up last line, which was prepered (malloc()) but never used
	free(ptr_array[line]);

	return line;
}

void write_int_line_cont(int *ptr_array[], int* n, int* row_len) 
{
	for(int i=0; i<	row_len[*n]; i++)
		printf("%d ", ptr_array[*n][i]);
	printf("\n");
}

void cleanup(int *ptr_array[], int n)
{
	for(int i=0; i<n; i++)
	{
		//printf("%d\n", i);
		free(ptr_array[i]);
	}
}

// 3
///////////////////////////////////////////////////////////

/*
int read_char_lines(char *array[]) {
}

void write_char_line(char *array[], int n) {
}

void delete_lines(char *array[]) {
}
*/

// auxiliary
////////////////////////////////////////////////////////////

int read_int(void) {
	char c_buf[BUF_SIZE];
	fgets(c_buf, BUF_SIZE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) 
{
	// DEBUG:
	//const int to_do = read_int();
	//int A[TAB_SIZE];
	/*
	read_mat(2, 3, A);
	read_mat(3, 2, B);
	prod_mat(2, 3, 3, A, B, AB);
	*/
	//printf("%d\n", get(3, 1, 0, A));

	// PROPER CODE:
	
	const int to_do = read_int();

	int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
	int n, rowsA, colsA, rowsB, colsB;
	char* char_lines_array[TAB_SIZE] = { NULL };
	int continuous_array[TAB_SIZE];
	int* ptr_array[TAB_SIZE];
	int row_len[TAB_SIZE];

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
			//ptr_array[0] = continuous_array; Why is it even here? It was in original template so I won't delete it
			int arr_size = read_int_lines_cont(ptr_array, row_len);
			write_int_line_cont(ptr_array, &n, row_len);
			cleanup(ptr_array, arr_size);
			break;
			/*
		case 3:
			n = read_int() - 1;
			read_char_lines(char_lines_array);
			write_char_line(char_lines_array, n);
			delete_lines(char_lines_array);
			break;
			*/
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}