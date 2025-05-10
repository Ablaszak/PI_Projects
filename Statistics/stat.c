#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

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
    while(j <= end)
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
			qselect(t, 0, number-1, number/2),
			qselect(t, 0, number-1, (number/2) + 1 ));
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

double sum (const int number, const double* values) {
}

double average (const int number, const double* values) {
}

double median (const int number, double* values) {
}

double min (const int number, const double* values) {
}

double max (const int number, const double* values) {
}

int read_from_line(char* c_buf, double *values, char** texts, int* text_counter) 
{
	
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
			break;
		default:
			printf("Nothing to do for n = %d\n", to_do);
			break;
	}

	return EXIT_SUCCESS;
}

