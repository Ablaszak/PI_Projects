#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ID_LEN 64
#define MAX_IDS 1024
#define MAX_LINE 128

void find_comments(int*, int*);
int find_idents(void);

char identifiers[MAX_IDS][MAX_ID_LEN];

const char *keywords[] = {
        "auto", "break", "case", "char",
        "const", "continue", "default", "do",
        "double", "else", "enum", "extern",
        "float", "for", "goto", "if",
        "int", "long", "register", "return",
        "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
};
int comment(char* line, char* fragment, int* in_comment, int* block)
{
    //printf("%s\n", fragment);
    switch(*in_comment)
    {
        case 0:
            if(strcmp(fragment, "/*") == 0)
            {
                *in_comment = 1;
                *block += 1;
                line[1] = '0'; // To prevent situation like "/*/"
            }
            else
            {
                //printf("%s %d\n", fragment, strcmp(fragment, "//"));
                if(strcmp(fragment, "//") == 0)
                    return 1;
            }
            return 0;

        case 1:
            if(strcmp(fragment, "*/") == 0)
            {
                *in_comment = 0;
                line[1] = '0'; // To prevent situation like "*//"
            }
            return 0;
    }
    return 0;
}
void find_comments(int *line_comment_counter, int *block_comment_counter) 
{
    int in_comment = 0; // bool
    size_t len;
    char line[MAX_LINE];
    char fragment[3]; // [char, char, \0]

    *line_comment_counter = 0;
    *block_comment_counter = 0;

    while(fgets(line, MAX_LINE, stdin) != NULL)
    {
        len = strlen(line);
        
        // Making copy of 2 firts digits in line:
        strncpy(fragment, line, 2);
        fragment[2] = '\0';

        // Checking beggining of the line
        if(comment(line, fragment, &in_comment, block_comment_counter) == 1)
            *line_comment_counter += 1;
        // Checking the rest of the line:
        else
        {
            for(size_t i=2; i<len; i++)
            {
                // Stepping forward:
                fragment[0] = fragment[1];
                fragment[1] = line[i];
                // Checking:
                *line_comment_counter += comment(line, fragment, &in_comment, block_comment_counter);
            }
        }
    }
}


//int find_idents(void) {
//}

int read_int() {
        char line[MAX_LINE];
        fgets(line, MAX_LINE, stdin); // to get the whole line
        return (int)strtol(line, NULL, 10);
}

int main(void) {
        int line_comment_counter, block_comment_counter;
        // DEBUG:
        find_comments(&line_comment_counter, &block_comment_counter);
        printf("%d %d\n", block_comment_counter, line_comment_counter);
        // PROPER CODE:
        /*
        const int to_do = read_int();
        switch (to_do) {
                case 1:
                        find_comments(&line_comment_counter, &block_comment_counter);
                        printf("%d %d\n", block_comment_counter, line_comment_counter);
                        break;
                case 2:
                        printf("%d\n", find_idents());
                        break;
                default:
                        printf("NOTHING TO DO FOR %d\n", to_do);
                        break;
        }
        */
        
        return 0;
}
