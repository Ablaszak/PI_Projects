#include<stdio.h>
#include<stdlib.h>
#define N 20

// c = column id
int can_be_placed(int* queens, const int c, const int ndx) // Bool
{
    for(int i=0; i<ndx; i++) // i = row above ndx
    {
        if(c == queens[i])
            return 0; // Column is occupied
        
        if(abs(i - ndx) == abs(queens[i] - c))
            return 0; // Diagonal
    }
    return 1; // True
}

void print_board(const int* queens, const int n) 
{
    for(int i=0; i<n; i++)
        printf("%d ", queens[i]);
}

int place_queens(int* queens, const int n, int k, const int ndx) 
{
    // We don't care about trash from other recursion loops,
    // because we care only about what is above ndx (lower indexes)
    // And they are always up to date

    //print_board(queens, n);

    if(ndx == n) // Max recursion depth
        return k-1;
    
    for(int i=0; i<n; i++)
    {
        if(can_be_placed(queens, i, ndx) == 1)
        {
            queens[ndx] = i;
            k = place_queens(queens, n, k, ndx+1);
            if(k == 0)
                return 0;
        }
    }
    return k;
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	int queens[N] = { 0 };
	if (place_queens(queens, n, k, 0) == 0) 
    {
		print_board(queens, n);
	} 
    else 
    {
		printf("-1\n");
	}

	return EXIT_SUCCESS;
}