#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 32

typedef struct node {
	int number;
	char name[MAX_NAME_SIZE];
	struct node* left;
	struct node* right;
	struct node* parent;
} node;

node* create_node(const int number, const char* name) 
{
	node* new = malloc(sizeof(node));
	new->number = number;
	new->name = name;
	// I don't know if I have to do that, but why not:
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	return new;
}

void delete_tree(node* root) 
{
	if(root == NULL)
		return;

	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
}

node* insert(node* root, node* to_insert, node* parent) 
{
	if(root == NULL) // we gotta create the root, also recursion end
	{
		root = to_insert;
		root->parent = parent;
		return root;
	}

	if(root->number == to_insert->number, root)
		return root;

	else if(root->number < to_insert->number)
		root->right = insert(root->right, to_insert, root);

	else if(root->number > to_insert->number)
		root->left = insert(root->left, to_insert, root);

	return root;
} 

node* find (node* root, const int number) 
{
	if(root->number == number)
		return root;

	else if(root->number < number)
		return find(root->right, number);

	else if(root->number > number)
		return find(root->left, number);

	return NULL;
}

node* delete(node* root, const int number) 
{
	del = find(root, number);

	if(del == NULL)
		return NULL;

	// case 1 - leaf:
	if(del->left == NULL && del->right == NULL)
	{
		// make parent forget the child:
		if(del->parent->left->number == del->number)
			del->parent->left = NULL;
		else
			del->parent->right = NULL;
		
		free(del);
		return root;
	}
	// case 2 - one child
	if(del->right == NULL || del->left == NULL)
	{
		node* child = del->right;
		if(del->left != NULL)
			child = del->left;

		// give parent new child:
		if(del->parent->right->number == del->number)
			del->parent->right = child;
		else
			del->parent->left = child;

		// delete node:
		free(del);
		return root;
	}
	// case 3 - both children
}

int main() {
	int a, r, f;
	scanf("%d %d %d", &a, &r, &f);

	node* root = NULL;
	int number;
	char name[MAX_NAME_SIZE];

	while (a-- > 0) {
		scanf("%d", &number);
		scanf("%s", name);
		root = insert(root, create_node(number, name), NULL);
	}

	while (r-- > 0) {
		scanf("%d", &number);
		root = delete(root, number);
	}

	while (f-- > 0) {
		scanf("%d", &number);
		node* student = find(root, number);
		printf("%s\n", student == NULL ? "NO" : student->name);
	}

	delete_tree(root);
}

