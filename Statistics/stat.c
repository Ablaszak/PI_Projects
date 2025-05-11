#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

double sum_var (int number, ...) 
{
	va_list args;
	va_start(args, number);
	double sum = 0;
	for(int i=0; i<number; i++)
		sum += va_arg(args, double);
	va_end(args);
	return sum;
}

double average_var (int number, ...) 
{
	va_list args;
	va_start(args, number);
	double sum = 0;
	for(int i=0; i<number; i++)
		sum += va_arg(args, double);
	va_end(args);
    sum /= number;
	return sum;
}
void swap(double* i, double* j)
{
    double temp = * j;
    *j = *i;
    *i = temp;
}

// Quick select block:
int partition(double arr[], int start, int end)
{
    double pivot = arr[end];
    int i = start-1;
    int j = start;
    while(j < end)
    {
        if(arr[j] > pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
        j++;
    }
    swap(&arr[i+1], &arr[end]);
    return i+1; // New pivot index
}

double qselect(double arr[], int start, int end, int k)
{
    int pid = partition(arr, start, end);

    if(pid == k)
        return arr[pid];
    if(k < pid)
        return qselect(arr, start, pid-1, k);
    else
        return qselect(arr, pid+1, end, k);
}
double median_var (int number, ...) 
{
	double med;
	double* t = malloc(sizeof(double) * number);
	va_list args;
	va_start(args, number);
	for(int i=0; i<number; i++)
		t[i] = va_arg(args, double); // Create a seperate array to use in quick select
	if(number % 2 == 1) // Simpler case
		med = qselect(t, 0, number-1, number/2);
	else // Gotta take the avarage num (will use function hehe)
	{
		med = average_var(2,
			qselect(t, 0, number-1, (number/2)-1),
			qselect(t, 0, number-1, (number/2)));
	}
	free(t);
	return med;
}

double min_var (int number, ...) 
{
	va_list args;
	va_start(args, number);
	double min = va_arg(args, double);
	double temp;
	for(int i=0; i<number-1; i++)
	{
		temp = va_arg(args, double);
		if(temp < min)
			min = temp;
	}
	va_end(args);
	return min;
}

double max_var (int number, ...) 
{
	va_list args;
	va_start(args, number);
	double max = va_arg(args, double);
	double temp;
	for(int i=0; i<number-1; i++)
	{
		temp = va_arg(args, double);
		if(temp > max)
			max = temp;
	}
	va_end(args);
	return max;
}

#define MAX_LINE 256
#define MAX_NUMBER 64
#define MAX_TEXTS 64

double sum (const int number, const double* values) 
{
	if(number == 0)
		return 0;
	
	double summ=0;
	for(int i=0; i<number; i++)
		summ += values[i];
	return summ;
}

double average (const int number, const double* values) 
{
	if(number == 0)
		return 0;
	
	double summ = sum(number, values);
	return (summ/number);
}

double median (const int number, double* values) 
{
	if(number == 0)
		return 0;
	
	// Same as median_var():
	if(number % 2 == 1) // Simpler case
		return(qselect(values, 0, number-1, number/2));

	else // Gotta take the avarage num (will use function hehe)
	{
		double med[2] = {
			qselect(values, 0, number-1, (number/2)-1),
			qselect(values, 0, number-1, (number/2)),
			};
		return (sum(2, med)/2);
	}
}

double min (const int number, const double* values) 
{
	if(number == 0)
		return 0;
	
	double min = values[0];
	for(int i=1; i<number; i++)
		if(values[i] < min)
			min = values[i];
	return min;
}

double max (const int number, const double* values) 
{
	if(number == 0)
		return 0;

	double max = values[0];
	for(int i=1; i<number; i++)
		if(values[i] > max)
			max = values[i];
	return max;
}

int read_from_line(char* c_buf, double *values, char** texts, int* text_counter) 
{
	// Init:
	*text_counter = 0;
	double devider = 1;
	char c;
	int instring = 0, got_int = 0, past_coma = 0; // bool
	int val_it = 0; // iterator
	size_t n = strlen(c_buf);
	
	for(int i=0; i<MAX_NUMBER; i++)
		values[i] = 0;
	for(int i=0; i<MAX_TEXTS; i++)
	{
		texts[i] = malloc(MAX_LINE);
		texts[i][0] = '\0';
	}

	// Main loop:
	for(size_t j=0; j<n; j++)
	{
        c = c_buf[j];

		if(c == ' ')
		{
			if(instring == 0 && got_int == 1) // edited just int, not a string
			{
				values[val_it] *= devider;
				devider = 1;
				past_coma = 0;
				val_it ++;
			}
			else 			  // edited string (int edition was ended elsewhere)
				(*text_counter) ++;

			instring = 0;
			got_int = 0;
			continue;
		}

		if(isdigit(c) && instring == 0)
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
			// afaik devider should be = 1 or -1 at this point
			past_coma = 1;
			continue;
		}
		
		if(c == '-' && instring == 0 && got_int == 0) // got a '-' as firts char
		{
			devider = -1;
			continue;
		}

		// Now we enter the string teritory
		instring = 1;

		if(got_int == 1) // We've just ended an int
		{
			values[val_it] *= devider;
			devider = 1;
			val_it ++;
			past_coma = 0;
			got_int = 0;
		}

		strncat(texts[*text_counter], &c, 1);
	}
	// In case we ended on an int:
	if(instring == 0 && got_int == 1) // edited just int, not a string
	{
		values[val_it] *= devider;
		val_it ++;
	}

	// Or if we ended with string:
	else if(instring == 1)
		(*text_counter) ++ ;

	// Debug:
	/*
	for(int i=0; i<4; i++)
		printf("%.2f ", values[i]);
	printf("\n");

	printf("val_it = %d\n", val_it);
	*/
    return val_it;

}

int read_int(void) {
	char c_buf[MAX_LINE];
	fgets(c_buf, MAX_LINE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
	int number;
	double v1, v2, v3, v4, v5;

	char c_buf[MAX_LINE];
	double values[MAX_NUMBER];
	char* texts[MAX_TEXTS];
	int text_counter;

	const int to_do = read_int();

	switch (to_do) {
		case 1:
			number = 3;
			scanf("%lf%lf%lf", &v1, &v2, &v3);
			printf("%.2f %.2f %.2f %.2f %.2f\n",
					sum_var(number, v1, v2, v3),
					average_var(number, v1, v2, v3),
					median_var(number, v1, v2, v3),
					min_var(number, v1, v2, v3),
					max_var(number, v1, v2, v3));

			number = 5;
			scanf("%lf%lf%lf%lf%lf", &v1, &v2, &v3, &v4, &v5);
			printf("%.2f %.2f %.2f %.2f %.2f\n",
					sum_var(number, v1, v2, v3, v4, v5),
					average_var(number, v1, v2, v3, v4, v5),
					median_var(number, v1, v2, v3, v4, v5),
					min_var(number, v1, v2, v3, v4, v5),
					max_var(number, v1, v2, v3, v4, v5));
			break;
		case 2:
			fgets(c_buf, MAX_LINE, stdin);
			number = read_from_line(c_buf, values, texts, &text_counter);
			printf("%.2f %.2f %.2f %.2f %.2f\n",
					sum(number, values),
					average(number, values),
					median(number, values),
					min(number, values),
					max(number, values));

			for (int k = 0; k < text_counter; k++) {
				printf("%s\n", texts[k]);
			}
			for(int i=0; i<MAX_TEXTS; i++)
				free(texts[i]);
			break;
		default:
			printf("Nothing to do for n = %d\n", to_do);
			break;
	}

	return EXIT_SUCCESS;
}

