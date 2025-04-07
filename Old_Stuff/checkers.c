/*
--> Treść zadania:

1. Funkcja start(char board[][N], int n) ustawia bierki w ich początkowych położeniach. Bierki powinny być ustawione wyłącznie na ciemnych polach. Zakładamy, że pole o
współrzędnych board[0][0] jest ciemne. Bierki gracza pierwszego są oznaczane na planszy znakiem ’1’ i zajmują rzędy począwszy od ineksu 0 (rosnąco), a bierki gracza drugiego
oznaczamy znakiem ’2’ i początkowo zajmują rzędy od n - 1 (malejąco). Bierki każdego
z graczy zajmują kolejne 4 rzędy (czyli każdy gracz ma początkowo 2n bierek).

2. Funkcja int move(char board[][N], int n, int i, int j)) sprawdza, czy bierka na
pozycji board[i][j] może wykonać ruch (czyli czy pole docelowe jest puste) i jeżeli tak,
to wykonuje ten ruch. Jeżeli możliwy jest ruch w obie strony (po skosie w lewo i po skosie
w prawo) to wykonywany jest ruch w stronę indeksu [j+1]. Bierki mogą wykonywać
ruchy wyłącznie po skosie do przodu (czyli bierka na polu [i][j] może przejść na pole
[i+1][j+1] lub [i+1][j-1] (dla gracza ’1’) i na pole [i-1][j+1] lub [i-1][j-1] (dla
gracza ’2’). Funkcja zwraca wartość 1 jeżeli ruch został wykonany i 0 jeżeli wyznaczona
bierka nie mogła wykonać ruchu.

3. Funkcja int capture(char board[][N], int n, int i, int j)) sprawdza, czy bierka na pozycji board[i][j] może zbić bierkę przeciwnika (czyli czy jakaś bierka przeciwnika zajmuje sąsiednie pole po skosie do przodu i czy za tą bierką w tym samym kierunku
jest pole puste). Jeżeli tak, to wykonuje bicie, czyli przeskakuje o 2 pozycje do przodu
i dwie pozycje w prawo lub w lewo, a przeskoczona bierka przeciwnika jest usuwana z
planszy. Jeżeli możliwe jest bicie w obie strony (po skosie w lewo i po skosie w prawo) to
wykonywane jest bicie w stronę indeksu [j+2]. Podobnie jak w przypadku ruchu, bierki
mogą zbijać bierki przeciwnika wyłącznie po skosie do przodu (czyli bierka na polu [i][j]
może przejść na pole [i+2][j+2] lub [i+2][j-2] (dla gracza ’1’) i na pole [i-2][j+2]
lub [i-2][j-2] (dla gracza ’2’). Funkcja zwraca wartość 1 jeżeli bicie zostało wykonane
i 0 jeżeli wyznaczona bierka nie mogła wykonać zbicia.

4. Funkcja void print board(char board[][N], int n) wypisuje stan planszy zgodnie z
rosnącą wartością indeksów. Puste pola mają zawierać znak podkreślnika ’ ’. Po każdym
znaku pola powinna znajdować się spacja.

--> Przebieg gry:

1. Losowaniu pola planszy, aż to momentu gdy wylosowane zostanie pole, na krórym znajduje
się bierka gracza aktualnie wykonującego ruch.

2. Gracz sprawdza czy może wykonać bicie i jeżeli tak, to je wykonuje (funkcja capture()).

3. Jeżeli nie jest możliwe bicie to gracz próbuje wykonać normaly ruch (funkcja move()).
Jeżeli ruch również nie jest możliwy, przechodzimy do następnego kroku.

--> Wejście:

Trzy liczby całkowite: rozmiar planszy – parzysta liczba 10 ¬ n ¬ 16, początkowa wartość
ziarna generacji dla funkcji srand() i liczba kroków do wykonania.

--> Wyjście:



*/

#include <stdio.h>
#include <stdlib.h>
#define N 20

int cnt[2];
char filler = '_';

int rnd(const int min, const int max) {
    return (rand() % (max - min)) + min;
}

void print(char board[][N], const int n) 
{
    for(int w = 0; w < n; w++)
    {
        for(int k = 0; k < n; k++)
            printf("%c ", board[w][k]);

        printf("\n");
    }
}

void start(char board[][N], const int n) 
{
    // stawianie czystej planszy (w zasadzie nie wiem czy faktycznie trzeba, ale dla bezpieczenstwa lepiej tak):
    for(int w = 0; w < n; w++)
        for(int k = 0; k < n; k++)
            board[w][k] = filler;
    // stawianie pionkow:
    // Wiersze parzyste:
    for(int w=0; w < 4; w += 2)
        for(int k=0; k < n; k += 2)
        {
            board[w][k] = '1';
            board[n-1 - w][n-1 - k] = '2';
        }
    // Wiersze nieparzyste:
    for(int w = 1; w < 4; w += 2)
        for(int k = 1; k < n; k += 2)
        {
            board[w][k] = '1';
            board[n-1 - w][n-1 - k] = '2';
        }
}

int move(char board[][N], const int i, const int j, const int n) 
{
    // Ustalenie kierunku w ktorym porusza sie pionek (gora/dol)
    int zwrot = 0;
    if(board[i][j] == '2')
        zwrot = -1;
    else
        zwrot = 1;
    //printf("%d\n", zwrot);
    
    // Sprawdzanie ruchu w prawo:
    // Sprawdzanie, czy nie wychodzimy poza plansze:
    if(0 <= j + 1 && j + 1 < n && 0 <= (i + zwrot) && (i + zwrot) < n) // Ja wiem ze te warunki sa zepsute, nie oceniaj xD
        // Sprawdzanie, czy pole jest wolne:
        if(board[i + zwrot][j + 1] == filler)
        {
            // Wykonywanie ruchu:
            board[i + zwrot][j + 1] = board[i][j];
            board[i][j] = filler;
            return 1;
        }
    // Sprawdzanie ruchu w lewo (to samo co w prawo):
    if(0 <= (j - 1) && (j - 1) < n && 0 <= (i + zwrot) && (i + zwrot) < n)
        // Sprawdzanie, czy pole jest wolne:
        if(board[i + zwrot][j - 1] == filler)
        {
            // Wykonywanie ruchu:
            board[i + zwrot][j - 1] = board[i][j];
            board[i][j] = filler;
            return 1;
        }
    
    // Na tym etapie wiem juz ze ruch ani w jedna ani w druga strone nie jest mozliwy
    return 0;
}

int capture(char board[][N], const int i, const int j, const int n) 
{
    // Calosc doslownie przekopiowana z move(), pozmianiane tylko wartosci i dodane warunki

    // Ustalenie kierunku w ktorym porusza sie pionek (gora/dol) i okreslenie przeciwnika
    int zwrot = 0;
    char enemy = '0';
    if(board[i][j] == '2')
    {
        zwrot = -2;
        enemy = '1';
    }
    else
    {
        zwrot = 2;
        enemy = '2';
    }

    // Sprawdzanie bicia w prawo:
    // Sprawdzanie, czy nie wychodzimy poza plansze:
    if(0 <= (j + 2) && (j + 2) < n && 0 <= (i + zwrot) && (i + zwrot) < n)
        // Sprawdzanie, czy pole jest wolne:
        if(board[i + zwrot][j + 2] == filler)
            // Sprawdzanie czy jest co bic:
            if(board[i + (zwrot / 2)][j + 1] == enemy)
                //sprawdzanie, czy za przeciwnikiem jest pole na ktore mozna przeskoczyc:
                if(board[i + zwrot][j + 2] == filler)
                {
                    // Nareszcie bicie xD:
                    board[i + (zwrot / 2)][j + 1] = filler;
                    board[i + zwrot][j + 2] = board[i][j];
                    board[i][j] = filler;
                    cnt[(enemy - 1) % 2] --;
                    return 1;
                }
    // Sprawdzanie bicia w lewo (to samo co w prawo):
    // Sprawdzanie, czy nie wychodzimy poza plansze:
    if(0 <= (j - 2) && (j - 2) < n && 0 <= (i + zwrot) && (i + zwrot) < n)
        // Sprawdzanie, czy pole jest wolne:
        if(board[i + zwrot][j - 2] == filler)
            // Sprawdzanie czy jest co bic:
            if(board[i + (zwrot / 2)][j - 1] == enemy)
                //sprawdzanie, czy za przeciwnikiem jest pole na ktore mozna przeskoczyc:
                if(board[i + zwrot][j - 2] == filler)
                {
                    // Nareszcie bicie xD:
                    board[i + (zwrot / 2)][j - 1] = filler;
                    board[i + zwrot][j - 2] = board[i][j];
                    board[i][j] = filler;
                    cnt[(enemy - 1) % 2] --;
                    return 1;
                }
    // Na tym etapie wiem juz ze bicie ani w jedna ani w druga strone nie jest mozliwe
    return 0;

}


int main(void) {
    char board[N][N];
    int n, steps;
    unsigned seed;
    scanf("%d %u %d", &n, &seed, &steps);
    srand(seed);
    cnt[0] = cnt[1] = 2 * n;
    start(board, n);
    for (int i = 0; i < steps; i++) {
        int ix, iy;
        const char turn = (i % 2 == 0) ? '1' : '2';
        do {
            ix = rnd(0, n);
            iy = rnd(0, n);
        } while (board[ix][iy] != turn);
        if (!capture(board, ix, iy, n)) {
            move(board, ix, iy, n);
        }
    }
    print(board, n);
    printf("%d %d\n", cnt[0], cnt[1]);
    return 0;
    /*
    start(board, 10);
    //board[4][3] = '2';
    board[4][2] = '2';
    capture(board, 3, 3, 10);
    move(board, 6,2,10);
    print(board, 10);
    */
}