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

int cmp_date(const void *d1, const void *d2) {
}

int cmp(const void *a, const void *b) {
}

void* bsearch2 (const void *key, const void *base, const size_t n_items,
		const size_t size, const CompareFp compare, char *result) 
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
		size_t mid = (high + low) / 2;
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
	return mid_elem; // mid_elem should
}

Food* add_record(const Food *tab, int *np, const CompareFp compare, const Food *new) 
{
	int result;
	Food* place = bsearch2(new, tab, *np, sizeof(Food), compare, &result);

	if(result == 1) // Product exists
		place->amount += new->amount;
	else 			// Otherwise, we have to insert product
	{
		// Firstly, find id of place
		int id = 0;
		whlie(tab[id] != place)
			id++;

		// Second, insert new elemeny and move other elements
		Food temp = tab[id];
		tab[id] = new;
		for(int i=id+1; i<*np; i++)
		{
			
		}
	}
}

int read_goods(Food *tab, FILE *stream, const int sorted) {
}

float value(Food *food_tab, const size_t n, const Date curr_date, const int days) {
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
		case 2: // qsort
			n = read_goods(food_tab, stdin, 0);
			Date curr_date;
			int days;
			scanf("%d %d %d", &curr_date.day, &curr_date.month, &curr_date.year);
			scanf("%d", &days);
			printf("%.2f\n", value(food_tab, (size_t)n, curr_date, days));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
	}
	return 0;
}
