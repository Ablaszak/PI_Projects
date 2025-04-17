#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTS 20

int guess_a_letter(char* text, const char* original_text) 
{
    // Guessed letter:
    char letter = (rand() % 26) + 65;
    // Is the letter in the original phrase?:
    if(strchr(original_text, letter) == NULL)
    {
        return 0;
    }

    // The letter is in the phrase.
    // Has it already been revealed?:
    if(strchr(text, letter) != NULL)
    {
        return 0;
    }
    
    // The letter is guessed and revealed:
    for(unsigned i=0; i < strlen(original_text); i++)
    {
        if(original_text[i] == letter)
        {
            text[i] = letter;
        }
    }
    return 1;
}

char* play(const char* original_text, const int number_of_players, const int turns, int* p_player) 
{
    *p_player = -1; // Will be incremented at the beginning of the game
    // Preparing the text to be guessed by the players:
    char *text = malloc(strlen(original_text) + 1);
    strcpy(text, original_text);
    for (unsigned i = 0; i < strlen(text); i++) 
    {
        if (text[i] != ' ') 
        {
            text[i] = '_';
        }
    }

    // GAME LOOP:
    for(int i=0; i < turns; i++)
    {
        *p_player = (*p_player + 1) % number_of_players;
        while(1)
        {
            if(guess_a_letter(text, original_text) == 0) // Letter not guessed
            {
                break;
            }
        }
        // Has the phrase been fully guessed?:
        if(strcmp(text, original_text) == 0)
        {
            return text;
        }
    }
    return text;
}

int main() {

    const char* texts[MAX_TEXTS] = {
        "PAN TADEUSZ",
        "HENRYK SIENKIEWICZ",
        "MORZE KASPIJSKIE",
        "POGODA DLA BOGACZY",
        "CZERWONE GITARY",
        "KAZANIE PIOTRA SKARGI",
        "QUO VADIS",
        "ADAM MICKIEWICZ",
        "ALBERT EINSTEIN",
        "DENNIS RITCHIE",
        "FIZYKA KWANTOWA",
        "PROGRAMOWANIE IMPERATYWNE",
        "ALGORYTMY I STRUKTURY DANYCH",
        "BRIAN KERNIGHAN",
        "CZERWONY KAPTUREK",
        "MARIA KONOPNICKA",
        "WILLIAM SHAKESPEARE",
        "ZBIGNIEW ZAPASIEWICZ",
        "MAGDALENA SAMOZWANIEC",
        "JEZIORO ONTARIO"
    };

    int number_of_players, turns, player;
    unsigned seed;

    scanf("%d %u %d", &number_of_players, &seed, &turns);
    srand(seed);
    const int number = rand() % MAX_TEXTS;
    // DEBUG:
    /*
    char t1[] = "123s3";
    char t2[] = "QWERTYUIOPASDFGHJKL;ZXCVBNM";
    printf("%s\n",play(t2, 1, 1, &player));
    */
    char* text = play(texts[number], number_of_players, turns, &player);
    printf("%s\n", text);
    printf("%d\n", player);
    free(text);

    return 0;
}
