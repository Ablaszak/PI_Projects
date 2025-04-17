#include <stdio.h>
#include <stdlib.h>
#define N 20

typedef struct Ant {
    int pi, pj;
    int direction; // [N, E, S, W] = [0, 1, 2, 3] = [00, 01, 10, 11]
    // ant.direction is a binary mask
} Ant;

int rnd(const int min, const int max) {
    return (rand() % (max - min)) + min;
}

void init_board(int*** board, const int n) 
{
    // Allocating memory for the main board:
    *board = malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++)
        (*board)[i] = malloc(n * sizeof(int));

    // Filling board spaces with integers:
    for(int w = 0; w < n; w++)
        for(int k = 0; k < n; k++)
            (*board)[w][k] = rnd(1, 9);
}

void free_board(int** board, const int n) 
{
    for(int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

void print_board(int** board, const int n) 
{
    for(int w = 0; w < n; w++) {
        for(int k = 0; k < n; k++)
            printf("%d ", board[w][k]);
        printf("\n");
    }
}

void ant_move(int** board, const int n, Ant* ant) 
{
    int *pole = &board[ant->pi][ant->pj]; // Address of the cell the ant is on
    switch(*pole)
    {
        case 1: // Step forward
            *pole = 7;
            ant->pi = (n /*preventing negatives*/ + ant->pi + (1 - (ant->direction % 2)) /* =0 if facing horizontally */ * ((-1) + (2 * (ant->direction / 2))) /* =-1 if facing up; =1 if facing down */) % n;
            ant->pj = (n /*preventing negatives*/ + ant->pj + (((ant->direction % 2) /* =0 if facing vertically */ * (1 - (2 * (ant->direction / 2))) /* =1 if facing right; =-1 if facing left */))) % n;
            break;

        case 2: // Turn right
            *pole = 4;
            ant->direction = (ant->direction + 1) % 4;
            break;

        case 3: // Turn left
            *pole = 2;
            ant->direction = (ant->direction + 3) % 4;
            break;

        case 4: // Step right
            *pole = 6;
            ant->pi = (n /*preventing negatives*/ + ant->pi + ((ant->direction % 2 /* =0 if facing vertically */) * (1 - (2 * (ant->direction / 2)) /* =1 if facing up; =-1 if facing down */))) % n;
            ant->pj = (n /*preventing negatives*/ + ant->pj + ((1 - (ant->direction % 2)) /* =0 if facing horizontally */ * (1 - (2 * (ant->direction / 2)) /* =1 if facing right; =-1 if facing left */))) % n;
            break;

        case 5: // Step left
            *pole = 3;
            ant->pi = (n /*preventing negatives*/ + ant->pi - ((ant->direction % 2 /* =0 if facing vertically */) * (1 - (2 * (ant->direction / 2)) /* =1 if facing up; =-1 if facing down */))) % n;
            ant->pj = (n /*preventing negatives*/ + ant->pj - ((1 - (ant->direction % 2)) /* =0 if facing horizontally */ * (1 - (2 * (ant->direction / 2)) /* =1 if facing right; =-1 if facing left */))) % n;
            break;

        case 6: // Step backward
            *pole = 5;
            ant->pi = (n /*preventing negatives*/ + ant->pi - (1 - (ant->direction % 2)) /* =0 if facing horizontally */ * ((-1) + (2 * (ant->direction / 2))) /* =-1 if facing up; =1 if facing down */) % n;
            ant->pj = (n /*preventing negatives*/ + ant->pj - (((ant->direction % 2) /* =0 if facing vertically */ * (1 - (2 * (ant->direction / 2))) /* =1 if facing right; =-1 if facing left */))) % n;
            break;

        case 7: // Rotate 180 degrees
            *pole = 8;
            ant->direction = (ant->direction + 2) % 4;
            break;

        case 8: // Wait patiently
            *pole = 1;
            break;
    }
}

void print_ant(const Ant ant) 
{
    printf("%d %d ", ant.pi, ant.pj);
    switch(ant.direction)
    {
        case 0:
            printf("%c\n", 'N');
            break;

        case 1:
            printf("%c\n", 'E');
            break;
            
        case 2:
            printf("%c\n", 'S');
            break;
            
        case 3:
            printf("%c\n", 'W');
            break;
    }
}

void ant_simulation(int** board, const int n, Ant* ant, const int steps) 
{
    ant->pi = 0;
    ant->pj = 0;
    ant->direction = 1;
    for(int i = 0; i < steps; i++)
        ant_move(board, n, ant);
}

int main(void) 
{
    int** board;
    int n, steps;
    unsigned seed;
    Ant ant;

    scanf("%d %u %d", &n, &seed, &steps);
    srand(seed);
    init_board(&board, n);
    ant_simulation(board, n, &ant, steps);
    print_board(board, n);
    print_ant(ant);

    free_board(board, n);

    return 0;
}
