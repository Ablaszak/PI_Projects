#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256
#define MAX_NUMBER 64
#define MAX_TEXTS 64

int read_from_line(char* c_buf, double *values, char** texts, int* text_counter) 
{
	// Init:
	*text_counter = 0;
	int devider = 1;
	char c;
	int instring = 0, got_int = 0, past_coma = 0; // bool
	int val_it = 0; // iterator
	
	for(int i=0; i<MAX_NUMBER; i++)
		values[i] = 0;
	for(int i=0; i<MAX_TEXTS; i++)
		texts[i] = "";

	// Main loop:
	for(int j=0; j<MAX_LINE; j++)
	{
        c = c_buf[j];

		if(c == ' ')
		{
			if(instring == 0 && got_int == 1) // edited just int, not a string
			{
				values[val_it] *= devider;
				devider = 1;
				val_it ++;
			}
			else 			  // edited string (int edition was ended elsewhere)
				*text_counter ++;

			instring = 0;
			got_int = 0;
			continue;
		}

		if(isalnum(c) && instring == 0)
		{
			values[val_it] *= 10;
			values[val_it] += (c - '0');
			
			if(past_coma == 1)
				devider /= 10;

			got_int = 1;
			continue;
		}

		if(c == '.' && instring == 0) // going past coma in a number
		{
			devider = 1;
			continue;
		}

		// Now we enter the string teritory
		instring = 1;

		if(got_int == 1) // We've just ended an int
		{
			values[val_it] *= devider;
			devider = 1;
			val_it ++;
		}

		strncat(texts[*text_counter], &c, 1);
	}
	// In case we ended on an int:
	if(instring == 0 && got_int == 1) // edited just int, not a string
	{
		values[val_it] *= devider;
		val_it ++;
	}
    return val_it;
	

}
int read_int(void) {
	char c_buf[MAX_LINE];
	fgets(c_buf, MAX_LINE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main()
{
	char c_buf[MAX_LINE];
	double values[MAX_NUMBER];
	char* texts[MAX_TEXTS];
	int text_counter;
    

			fgets(c_buf, MAX_LINE, stdin);
			int number = read_from_line(c_buf, values, texts, &text_counter);

			for (int k = 0; k < text_counter; k++) {
				printf("%s\n", texts[k]);
        }
    }