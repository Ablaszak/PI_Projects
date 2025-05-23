#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define BUFFER_SIZE 1024

typedef void (*DataFp)(void*);
typedef void (*ConstDataFp)(const void*);
typedef int  (*CompareDataFp)(const void*, const void*);

typedef struct ListElement {
	struct ListElement *next;
	void *data;
} ListElement;

typedef struct {
	ListElement *head;
	ListElement *tail;
	ConstDataFp dump_data;
	DataFp free_data;
	CompareDataFp compare_data;
	DataFp modify_data;
} List;

void *safe_malloc(const size_t size) {
	void *ptr = malloc(size);
	if(ptr) return ptr;
	printf("malloc error\n");
	exit(EXIT_FAILURE);
}

void *safe_strdup(const char *string) {
	void *ptr = safe_malloc(strlen(string) + 1);
	strcpy(ptr, string);
	return ptr;
}

// generic functions for any data type

void init_list(List* p_list, const ConstDataFp dump_data, const DataFp free_data,
		const CompareDataFp compare_data, const DataFp modify_data) {
}

// Print elements of the list
void dump_list(const List* p_list) {
}

// Print elements of the list if comparable to data
void dump_list_if(const List* p_list, const void *data) {
}

// Free all elements of the list
void free_list(List* p_list) {
}

// Push element at the beginning of the list
void push_front(List* p_list, void *data) {
}

// Push element at the end of the list
void push_back(List* p_list, void *data) {
}

// Remove the first element
void pop_front(List* p_list) {
}

// Reverse the list
void reverse(List* p_list) {
}

// find an element in a sorted list after which to insert a given element
ListElement* find_insertion_point(const List* p_list, const ListElement* p_element) {
}

// Insert element after 'previous'
void push_after(List* p_list, void* data, ListElement* previous) {
}

// Insert element preserving order
void insert_in_order(List* p_list, void* p_data) {
}

// type-specific definitions

// int element

void dump_int(const void* d) {
}

void free_int(void* d) {
}

int cmp_int(const void* a, const void* b) {
}

int* create_data_int(const int v) {
}

// Word element

typedef struct DataWord {
	char* word;
	int counter;
} DataWord;

void dump_word (const void* d) {
}

void free_word(void* d) {
}

int cmp_word_alphabet(const void* a, const void* b) {
}

int cmp_word_counter(const void* a, const void* b) {
}

void modify_word(void* p) {
}

void* create_data_word(const char* string, const int counter) {
}

// Read text, parse it to words, and insert those words to the list.
// The order of insertions is given by the last parameter of type CompareDataFp.
// (comparator function address). If this address is not NULL, the element is
// inserted according to the comparator. Otherwise, read order is preserved.
void stream_to_list(List* p_list, FILE* stream) {
	const char delimits[] = " \r\t\n.,?!:;-";
}

// test an integer list
void list_test(List* p_list, const int n) {
	char op;
	int v;
	for (int i = 0; i < n; ++i) {
		scanf(" %c", &op);
		switch (op) {
			case 'f':
				scanf("%d", &v);
				push_front(p_list, create_data_int(v));
				break;
			case 'b':
				scanf("%d", &v);
				push_back(p_list, create_data_int(v));
				break;
			case 'd':
				pop_front(p_list);
				break;
			case 'r':
				reverse(p_list);
				break;
			case 'i':
				scanf("%d", &v);
				insert_in_order(p_list, create_data_int(v));
				break;
			default:
				printf("No such operation: %c\n", op);
				break;
		}
	}
}

int main(void) {
	int to_do, n;
	List list;

	scanf ("%d", &to_do);
	switch (to_do) {
		case 1: // test an integer list
			scanf("%d",&n);
			init_list(&list, dump_int, free_int, cmp_int, NULL);
			list_test(&list, n);
			dump_list(&list);
			free_list(&list);
			break;
		case 2: // read words from a text, insert into a list, and print
			init_list(&list, dump_word, free_word, NULL, NULL);
			stream_to_list(&list, stdin);
			dump_list(&list);
			free_list(&list);
			break;
		case 3: // read words, insert into a list alphabetically, print words encountered n times
			scanf("%d",&n);
			init_list(&list, dump_word_lowercase, free_word, cmp_word_alphabet, modify_word);
			stream_to_list(&list, stdin);
			list.compare_data = cmp_word_counter;
			const DataWord data = { NULL, n };
			dump_list_if(&list, &data);
			free_list(&list);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

