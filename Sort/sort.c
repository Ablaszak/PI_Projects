#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int day;
	int month;
	int year;
} Date;

// 1 bsearch2

#define NAME_MAX  20   // max. length of name + 1
#define FOOD_MAX  30   // max. number of goods
#define RECORD_MAX 64  // max. line length

typedef struct {
	char name[NAME_MAX];
	float price;
	int amount;
	Date exp_date;
} Food;

typedef int (*CompareFp)(const void *, const void *);

int cmp_date(Food* f1, Food* f2) 
{

	Date d1 = f1->exp_date;
	Date d2 = f2->exp_date;

	if(d1.year < d2.year)
		return -1;

	if(d1.year > d2.year)
		return 1;

	if(d1.month < d2.month)
		return -1;

	if(d1.month > d2.month)
		return 1;

	if(d1.day < d2.day)
		return -1;

	if(d1.day > d2.day)
		return 1;

	return 0;
}

int cmp(const void *a, const void *b) 
{
	Food* af = (Food*)a;
	Food* bf = (Food*)b;

	// 1. Compare names:
	if(strcmp(af->name, bf->name) != 0)
		return strcmp(af->name, bf->name);

	// 2. Compare price:
	if(af->price < bf->price)
		return -1;

	if(af->price > bf->price)
		return 1;

	// 3.Compare dates:
	return cmp_date(af, bf);
}

void* bsearch2 (const void *key, const void *base, const size_t n_items,
		const size_t size, const CompareFp compare, int* result) 
{
	// Init:
	size_t low = 0;
	size_t high = n_items; // 1 element too much, but is is ok
	size_t mid = (high + low) / 2;
 
	Food* base_elem = (Food*)base;
	Food* mid_elem;
	int relation;

	// Main loop:
	while(low < high)
	{
		mid = (high + low) / 2;
		mid_elem = (Food*)(base_elem + mid);
		relation = compare(key, mid_elem);

		if(relation == 0) // We've found the element
		{
			*result = 1;
			return mid_elem;
		}
		if(relation < 0) // key < mid
		{
			high = mid;
			continue;
		}
		// key > mid
		low = mid+1;
	}

	*result = 0;

	mid_elem = (Food*)(base_elem + low);
	return mid_elem; 
}

Food* add_record(Food *tab, int *np, const CompareFp compare, const Food *product) 
{
	int result;
	Food* place = bsearch2(product, tab, *np, sizeof(Food), compare, &result);

	if(result == 1) // Product exists
		place->amount += product->amount;
	else // Otherwise, we have to insert the product product
	{
		// Firstly, find id of place
		int id = 0;
		while(cmp(&tab[id], place) != 0)
			id++;

		// Second, move other elements
		for(int i=*np; i>id; i--) // We assume we can fit in tab
			tab[i] = tab[i-1];
		
		// At last, insert the product
		tab[id] = *product;
		
		(*np)++;
	}
	return place;
}

int read_goods(Food *tab, FILE *stream, const int sorted)
{
	CompareFp comparison;
	if(sorted == 1)
		comparison = (CompareFp)cmp;
	else
		comparison = (CompareFp)cmp_date;

	int no;
	int np = 0;
	scanf("%d", &no);

	Food product;

	for(int i=0; i<no; i++)
	{
		fscanf(stream, "%s %f %d ", product.name, &product.price, &product.amount);
		fscanf(stream, "%d.%d.%d\n", &product.exp_date.day, &product.exp_date.month, &product.exp_date.year); // Same input, seperated for visibility
		
		add_record(tab, &np, comparison, &product);
	}
	return np;
}

// Separete function for visibility:
void print_date(Date* date)
{
	printf("%d.%d.%d\n", date->day, date->month, date->year);
}

void print_art(Food* tab, int n, char buff[])
{
	for(int i=0; i<n; i++)
	{
		if(strcmp(tab[i].name, buff) == 0)
		{
			printf("%.2f %d ", tab[i].price, tab[i].amount);
			print_date(&tab[i].exp_date);
		}
	}
}

Date add_days(Date date, int days) {
	// Fill in the tm structure with the given date
	struct tm tm_date = {
		.tm_mday = date.day,
		.tm_mon = date.month - 1,     // tm_mon is 0-based (0 = January)
		.tm_year = date.year - 1900,  // tm_year is years since 1900
		.tm_hour = 0,
		.tm_min = 0,
		.tm_sec = 1                   // use non-zero second to avoid DST issues
	};

	// Convert struct tm to time_t (seconds since epoch)
	time_t time_val = mktime(&tm_date);
	if (time_val == -1) {
		// mktime failed — return the original date as fallback
		return date;
	}

	// Add the number of days in seconds
	time_val += days * 24 * 60 * 60;

	// Convert back from time_t to struct tm
	struct tm *new_tm = localtime(&time_val);

	// Create the new Date struct from updated tm
	Date new_date = {
		.day = new_tm->tm_mday,
		.month = new_tm->tm_mon + 1,
		.year = new_tm->tm_year + 1900
	};

	return new_date;
}

float value(const size_t n, const Date curr_date, const int days) 
{
	Food dummy;
	dummy.exp_date = add_days(curr_date, days);

	float val = 0;

	Food product;

	for(size_t i=0; i<n; i++)
	{
		scanf("%s %f %d ", product.name, &product.price, &product.amount);
		scanf("%d.%d.%d\n", &product.exp_date.day, &product.exp_date.month, &product.exp_date.year); // Same input, seperated for visibility
		
		if(cmp_date(&dummy, &product) == 0)
			val += (product.price * product.amount);
	}
	printf("\n\n");
	return val;
}

int read_int() {
	char buff[RECORD_MAX];
	int value;
	fgets(buff, RECORD_MAX, stdin);
	sscanf(buff, "%d", &value);
	return value;
}

int main(void) {

	int n;
	Food food_tab[FOOD_MAX];
	char buff[RECORD_MAX];
	const int to_do = read_int();

	switch (to_do) {
		case 1:  // bsearch2
			n = read_goods(food_tab, stdin, 1);
			scanf("%s", buff);
			print_art(food_tab, n, buff);
			break;
		case 2: // qsort (not realy but ok)
			scanf("%d", &n);
			Date curr_date;
			int days;
			scanf("%d %d %d", &curr_date.day, &curr_date.month, &curr_date.year);
			scanf("%d", &days);
			printf("%.2f\n", value((size_t)n, curr_date, days));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
	}
	return 0;
}
